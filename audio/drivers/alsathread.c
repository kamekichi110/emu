/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2010-2014 - Hans-Kristian Arntzen
 *  Copyright (C) 2012-2015 - Michael Lelli
 *
 *  RetroArch is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  RetroArch is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with RetroArch.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdlib.h>

#include <lists/string_list.h>

#include <alsa/asoundlib.h>

#include <rthreads/rthreads.h>
#include <queues/fifo_queue.h>
#include <string/stdstring.h>
#include <asm-generic/errno.h>

#include "../audio_driver.h"
#include "alsa.h"
#include "../../verbosity.h"

typedef struct alsa_thread_info
{
   snd_pcm_t *pcm;
   fifo_buffer_t *buffer;
   sthread_t *worker_thread;
   slock_t *fifo_lock;
   scond_t *cond;
   slock_t *cond_lock;
   alsa_stream_info_t stream_info;
   volatile bool thread_dead;
} alsa_thread_info_t;

typedef struct alsa_thread_microphone
{
   alsa_thread_info_t info;
   bool is_paused;
} alsa_thread_microphone_t;

typedef struct alsa_thread
{
   alsa_thread_info_t info;
   /* Only one microphone is supported right now;
    * the driver state should track multiple microphone handles,
    * but the driver *context* should track multiple microphone contexts */
   alsa_thread_microphone_t *microphone;
   snd_pcm_uframes_t period_frames;
   size_t period_size;
   bool nonblock;
   bool is_paused;
} alsa_thread_t;

static void alsa_worker_thread(void *data)
{
   alsa_thread_t *alsa = (alsa_thread_t*)data;
   uint8_t        *buf = (uint8_t *)calloc(1, alsa->period_size);
   uintptr_t        id = sthread_get_current_thread_id();

   if (!buf)
   {
      RARCH_ERR("[ALSA] [playback thread %u]: Failed to allocate audio buffer\n", id);
      goto end;
   }

   while (!alsa->info.thread_dead)
   {
      size_t avail;
      size_t fifo_size;
      snd_pcm_sframes_t frames;
      slock_lock(alsa->info.fifo_lock);
      avail     = FIFO_READ_AVAIL(alsa->info.buffer);
      fifo_size = MIN(alsa->period_size, avail);
      fifo_read(alsa->info.buffer, buf, fifo_size);
      scond_signal(alsa->info.cond);
      slock_unlock(alsa->info.fifo_lock);

      /* If underrun, fill rest with silence. */
      memset(buf + fifo_size, 0, alsa->period_size - fifo_size);

      frames = snd_pcm_writei(alsa->info.pcm, buf, alsa->period_frames);

      if (frames == -EPIPE || frames == -EINTR ||
            frames == -ESTRPIPE)
      {
         if (snd_pcm_recover(alsa->info.pcm, frames, 1) < 0)
         {
            RARCH_ERR("[ALSA] [playback thread %u]: Failed to recover from error: %s\n",
               id,
               snd_strerror(frames));
            break;
         }

         continue;
      }
      else if (frames < 0)
      {
         RARCH_ERR("[ALSA] [playback thread %u]: Error writing audio to device: %s\n",
            id,
            snd_strerror(frames));
         break;
      }
   }

end:
   slock_lock(alsa->info.cond_lock);
   alsa->info.thread_dead = true;
   scond_signal(alsa->info.cond);
   slock_unlock(alsa->info.cond_lock);
   free(buf);
}

static void alsa_microphone_worker_thread(void *data)
{
   // TODO: Implement
   alsa_thread_t *microphone = (alsa_thread_t*)data;
   uint8_t              *buf = (uint8_t *)calloc(1, microphone->period_size);
   uintptr_t       thread_id = sthread_get_current_thread_id();

   if (!buf)
   {
      RARCH_ERR("[ALSA] [capture thread %p]: Failed to allocate audio buffer\n", thread_id);
      goto end;
   }

   while (!microphone->info.thread_dead)
   {
      size_t avail;
      size_t fifo_size;
      snd_pcm_sframes_t frames;

      slock_lock(microphone->info.fifo_lock);
      avail     = FIFO_READ_AVAIL(microphone->info.buffer);
      fifo_size = MIN(microphone->period_size, avail);
      fifo_read(microphone->info.buffer, buf, fifo_size);
      scond_signal(microphone->info.cond);
      slock_unlock(microphone->info.fifo_lock);

      /* If underrun, fill rest with silence. */
      memset(buf + fifo_size, 0, microphone->period_size - fifo_size);

      frames = snd_pcm_writei(microphone->info.pcm, buf, microphone->period_frames);

      if (frames == -EPIPE || frames == -EINTR || frames == -ESTRPIPE)
      {
         if (snd_pcm_recover(microphone->info.pcm, frames, 1) < 0)
         {
            RARCH_ERR("[ALSA] [capture thread %p]: (#2) Failed to recover from read error: %s\n",
                      thread_id,
                      snd_strerror(frames));
            break;
         }

         continue;
      }
      else if (frames < 0)
      {
         RARCH_ERR("[ALSA] [capture thread %p]: Read error: %s.\n",
               thread_id,
               snd_strerror(frames));
         break;
      }
   }

end:
   slock_lock(microphone->info.cond_lock);
   microphone->info.thread_dead = true;
   scond_signal(microphone->info.cond);
   slock_unlock(microphone->info.cond_lock);
   free(buf);
}

static void alsa_thread_free_info_members(alsa_thread_info_t *info)
{
   if (info)
   {
      if (info->worker_thread)
      {
         slock_lock(info->cond_lock);
         info->thread_dead = true;
         slock_unlock(info->cond_lock);
         sthread_join(info->worker_thread);
      }
      if (info->buffer)
         fifo_free(info->buffer);
      if (info->cond)
         scond_free(info->cond);
      if (info->fifo_lock)
         slock_free(info->fifo_lock);
      if (info->cond_lock)
         slock_free(info->cond_lock);
      if (info->pcm)
      {
         alsa_free_pcm(info->pcm);
      }
   }
   /* Do NOT free() info itself; it's embedded within another struct
    * that will be freed. */
}

static bool alsa_thread_use_float(void *data)
{
   alsa_thread_t *alsa = (alsa_thread_t*)data;
   return alsa->info.stream_info.has_float;
}

static void alsa_thread_free_microphone(void *data, void *microphone_context);
static void alsa_thread_free(void *data)
{
   alsa_thread_t *alsa = (alsa_thread_t*)data;

   if (alsa)
   {
      if (alsa->microphone)
         alsa_thread_free_microphone(alsa, alsa->microphone);

      alsa_thread_free_info_members(&alsa->info);
      free(alsa);
   }
}

static void *alsa_thread_init(const char *device,
      unsigned rate, unsigned latency,
      unsigned block_frames,
      unsigned *new_rate)
{
   alsa_thread_t *alsa = (alsa_thread_t*)calloc(1, sizeof(alsa_thread_t));

   if (!alsa)
   {
      RARCH_ERR("[ALSA] Failed to allocate driver context\n");
      return NULL;
   }

   RARCH_LOG("[ALSA] Using ALSA version %s\n", snd_asoundlib_version());

   if (alsa_init_pcm(&alsa->info.pcm, device, SND_PCM_STREAM_PLAYBACK, rate, latency, 2, &alsa->info.stream_info, new_rate, 0) < 0)
   {
      goto error;
   }

   alsa->info.fifo_lock = slock_new();
   alsa->info.cond_lock = slock_new();
   alsa->info.cond = scond_new();
   alsa->info.buffer = fifo_new(alsa->info.stream_info.buffer_size);
   if (!alsa->info.fifo_lock || !alsa->info.cond_lock || !alsa->info.cond || !alsa->info.buffer)
      goto error;

   alsa->info.worker_thread = sthread_create(alsa_worker_thread, alsa);
   if (!alsa->info.worker_thread)
   {
      RARCH_ERR("[ALSA]: Failed to initialize worker thread\n");
      goto error;
   }

   return alsa;

error:
   RARCH_ERR("[ALSA]: Failed to initialize...\n");

   alsa_thread_free(alsa);

   return NULL;
}

static ssize_t alsa_thread_write(void *data, const void *buf, size_t size)
{
   alsa_thread_t *alsa = (alsa_thread_t*)data;

   if (alsa->info.thread_dead)
      return -1;

   if (alsa->nonblock)
   {
      size_t avail;
      size_t write_amt;

      slock_lock(alsa->info.fifo_lock);
      avail           = FIFO_WRITE_AVAIL(alsa->info.buffer);
      write_amt       = MIN(avail, size);

      fifo_write(alsa->info.buffer, buf, write_amt);
      slock_unlock(alsa->info.fifo_lock);

      return write_amt;
   }
   else
   {
      size_t written = 0;
      while (written < size && !alsa->info.thread_dead)
      {
         size_t avail;
         slock_lock(alsa->info.fifo_lock);
         avail = FIFO_WRITE_AVAIL(alsa->info.buffer);

         if (avail == 0)
         {
            slock_unlock(alsa->info.fifo_lock);
            slock_lock(alsa->info.cond_lock);
            if (!alsa->info.thread_dead)
               scond_wait(alsa->info.cond, alsa->info.cond_lock);
            slock_unlock(alsa->info.cond_lock);
         }
         else
         {
            size_t write_amt = MIN(size - written, avail);
            fifo_write(alsa->info.buffer,
                  (const char*)buf + written, write_amt);
            slock_unlock(alsa->info.fifo_lock);
            written += write_amt;
         }
      }
      return written;
   }
}

static bool alsa_thread_alive(void *data)
{
   alsa_thread_t *alsa = (alsa_thread_t*)data;
   if (!alsa)
      return false;
   return !alsa->is_paused;
}

static bool alsa_thread_stop(void *data)
{
   alsa_thread_t *alsa = (alsa_thread_t*)data;

   if (alsa)
      alsa->is_paused = true;
   return true;
}

static void alsa_thread_set_nonblock_state(void *data, bool state)
{
   alsa_thread_t *alsa = (alsa_thread_t*)data;
   alsa->nonblock = state;
}

static bool alsa_thread_start(void *data, bool is_shutdown)
{
   alsa_thread_t *alsa = (alsa_thread_t*)data;

   if (alsa)
      alsa->is_paused = false;
   return true;
}

static size_t alsa_thread_write_avail(void *data)
{
   alsa_thread_t *alsa = (alsa_thread_t*)data;
   size_t val;

   if (alsa->info.thread_dead)
      return 0;
   slock_lock(alsa->info.fifo_lock);
   val = FIFO_WRITE_AVAIL(alsa->info.buffer);
   slock_unlock(alsa->info.fifo_lock);
   return val;
}

static size_t alsa_thread_buffer_size(void *data)
{
   alsa_thread_t *alsa = (alsa_thread_t*)data;
   return alsa->info.stream_info.buffer_size;
}

static void *alsa_thread_init_microphone(void *data,
   const char *device,
   unsigned rate,
   unsigned latency,
   unsigned block_frames,
   unsigned *new_rate)
{
   alsa_thread_t *alsa                   = (alsa_thread_t*)data;
   alsa_thread_microphone_t  *microphone = NULL;

   if (!alsa) /* If we weren't given a valid ALSA context... */
      return NULL;

   microphone = calloc(1, sizeof(alsa_thread_microphone_t));

   if (!microphone)
   { /* If the microphone context couldn't be allocated... */
      RARCH_ERR("[ALSA] Failed to allocate microphone context\n");
      return NULL;
   }

   if (alsa_init_pcm(&alsa->info.pcm, device, SND_PCM_STREAM_CAPTURE, rate, latency, 1, &alsa->info.stream_info, new_rate, 0) < 0)
   {
      goto error;
   }

   microphone->info.fifo_lock = slock_new();
   microphone->info.cond_lock = slock_new();
   microphone->info.cond = scond_new();
   microphone->info.buffer = fifo_new(microphone->info.stream_info.buffer_size);
   if (!microphone->info.fifo_lock || !microphone->info.cond_lock || !microphone->info.cond || !microphone->info.buffer)
      goto error;

   microphone->info.worker_thread = sthread_create(alsa_microphone_worker_thread, microphone);
   if (!microphone->info.worker_thread)
   {
      RARCH_ERR("[ALSA]: Failed to initialize microphone worker thread\n");
      goto error;
   }

   alsa->microphone = microphone;
   return microphone;

error:
   RARCH_ERR("[ALSA]: Failed to initialize microphone...\n");

   if (microphone)
   {
      if (microphone->info.pcm)
      {
         snd_pcm_close(microphone->info.pcm);
      }

      alsa_thread_free_microphone(alsa, microphone);
   }
   alsa->microphone = NULL;
   return NULL;
}

static void alsa_thread_free_microphone(void *data, void *microphone_context)
{
   alsa_thread_t *alsa                   = (alsa_thread_t*)data;
   alsa_thread_microphone_t *microphone  = (alsa_thread_microphone_t*)microphone_context;

   if (alsa && microphone)
   {
      alsa_thread_free_info_members(&microphone->info);

      alsa->microphone = NULL;
      free(microphone);
   }
}

static bool alsa_thread_get_microphone_state(const void *data, const void *microphone_context)
{
   alsa_thread_t *alsa = (alsa_thread_t*)data;
   alsa_thread_microphone_t *microphone = (alsa_thread_microphone_t *)microphone_context;

   if (!alsa || !microphone)
      return false;

   return !microphone->is_paused;
}

static bool alsa_thread_set_microphone_state(void *data, void *microphone_context, bool enabled)
{
   alsa_thread_t *alsa                   = (alsa_thread_t*)data;
   alsa_thread_microphone_t  *microphone = (alsa_thread_microphone_t*)microphone_context;

   if (!alsa || !microphone)
      return false;
   /* Both params must be non-null */

   microphone->is_paused = !enabled;

   // TODO: Do I need to synchronize this?
   return true;
}

static ssize_t alsa_thread_read_microphone(void *driver_context, void *microphone_context, void *buf_, size_t size_)
{

}

audio_driver_t audio_alsathread = {
   alsa_thread_init,
   alsa_thread_write,
   alsa_thread_stop,
   alsa_thread_start,
   alsa_thread_alive,
   alsa_thread_set_nonblock_state,
   alsa_thread_free,
   alsa_thread_use_float,
   "alsathread",
   alsa_device_list_new, /* Reusing these functions from alsa.c */
   alsa_device_list_free, /* because they don't use the driver context */
   alsa_thread_write_avail,
   alsa_thread_buffer_size,
   alsa_thread_init_microphone,
   alsa_thread_free_microphone,
   alsa_thread_get_microphone_state,
   alsa_thread_set_microphone_state,
   alsa_thread_read_microphone,
};
