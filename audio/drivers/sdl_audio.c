/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2010-2014 - Hans-Kristian Arntzen
 *  Copyright (C) 2011-2017 - Daniel De Matteis
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

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include <boolean.h>
#include <rthreads/rthreads.h>
#include <queues/fifo_queue.h>
#include <retro_inline.h>
#include <retro_math.h>

#include "SDL.h"
#include "SDL_audio.h"

#include "../audio_driver.h"
#include "../../verbosity.h"

/**
 * We need the SDL_{operation}AudioDevice functions for microphone support,
 * but those were introduced in SDL 2.0.0
 * (according to their docs).
 * Some legacy build platforms are stuck on 1.x.x,
 * so we have to accommodate them.
 * That comes in the form of stub implementations of the missing functions
 * that delegate to the non-Device versions.
 *
 * Only three platforms (as of this writing) are stuck on SDL 1.x.x,
 * so it's not a big deal to exclude mic support from them.
 **/
#if HAVE_SDL2
#define SDL_DRIVER_MIC_SUPPORT 1
#define SDL_DRIVER_DEVICE_FUNCTIONS 1
#else
typedef Uint32 SDL_AudioDeviceID;

/** Compatibility stub that defers to SDL_PauseAudio. */
#define SDL_PauseAudioDevice(dev, pause_on) SDL_PauseAudio(pause_on)

/** Compatibility stub that defers to SDL_LockAudio. */
#define SDL_LockAudioDevice(dev) SDL_LockAudio()

/** Compatibility stub that defers to SDL_UnlockAudio. */
#define SDL_UnlockAudioDevice(dev) SDL_UnlockAudio()

/** Compatibility stub that defers to SDL_CloseAudio. */
#define SDL_CloseAudioDevice(dev) SDL_CloseAudio()
#endif

typedef struct sdl_audio
{
#ifdef HAVE_THREADS
   slock_t *lock;
   scond_t *cond;
#endif
   fifo_buffer_t *speaker_buffer;
   bool nonblock;
   bool is_paused;
   SDL_AudioDeviceID speaker_device;

#ifdef SDL_DRIVER_MIC_SUPPORT
   fifo_buffer_t *microphone_buffer;
   SDL_AudioDeviceID microphone_device;
#endif
} sdl_audio_t;

static void sdl_audio_playback_cb(void *data, Uint8 *stream, int len)
{
   sdl_audio_t  *sdl = (sdl_audio_t*)data;
   size_t      avail = FIFO_READ_AVAIL(sdl->speaker_buffer);
   size_t write_size = len > (int)avail ? avail : len;

   fifo_read(sdl->speaker_buffer, stream, write_size);
#ifdef HAVE_THREADS
   scond_signal(sdl->cond);
#endif

   /* If underrun, fill rest with silence. */
   memset(stream + write_size, 0, len - write_size);
}

#ifdef SDL_DRIVER_MIC_SUPPORT
static void sdl_audio_record_cb(void *data, Uint8 *stream, int len)
{
   sdl_audio_t  *sdl = (sdl_audio_t*)data;
   size_t      avail = FIFO_WRITE_AVAIL(sdl->microphone_buffer);
   size_t read_size = len > (int)avail ? avail : len;

   fifo_write(sdl->microphone_buffer, stream, read_size);
#ifdef HAVE_THREADS
   scond_signal(sdl->cond);
#endif
}
#endif

static INLINE int find_num_frames(int rate, int latency)
{
   int frames = (rate * latency) / 1000;

   /* SDL only likes 2^n sized buffers. */

   return next_pow2(frames);
}

static void *sdl_audio_init(const char *device,
      unsigned rate, unsigned latency,
      unsigned block_frames,
      unsigned *new_rate)
{
   int frames;
   size_t bufsize;
   SDL_AudioSpec out;
   SDL_AudioSpec spec           = {0};
   void *tmp                    = NULL;
   sdl_audio_t *sdl             = NULL;
   uint32_t sdl_subsystem_flags = SDL_WasInit(0);

   (void)device;

   /* Initialise audio subsystem, if required */
   if (sdl_subsystem_flags == 0)
   {
      if (SDL_Init(SDL_INIT_AUDIO) < 0)
         return NULL;
   }
   else if ((sdl_subsystem_flags & SDL_INIT_AUDIO) == 0)
   {
      if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
         return NULL;
   }

   sdl = (sdl_audio_t*)calloc(1, sizeof(*sdl));
   if (!sdl)
      return NULL;

   /* We have to buffer up some data ourselves, so we let SDL
    * carry approximately half of the latency.
    *
    * SDL double buffers audio and we do as well. */
   frames        = find_num_frames(rate, latency / 4);

   /* First, let's initialize the output device. */
   spec.freq     = rate;
   spec.format   = AUDIO_S16SYS;
   spec.channels = 2;
   spec.samples  = frames; /* This is in audio frames, not samples ... :( */
   spec.callback = sdl_audio_playback_cb;
   spec.userdata = sdl;

   /* No compatibility stub for SDL_OpenAudioDevice because its return value
    * is different from that of SDL_OpenAudio. */
#if SDL_DRIVER_DEVICE_FUNCTIONS
   sdl->speaker_device = SDL_OpenAudioDevice(NULL, false, &spec, &out, 0);

   if (sdl->speaker_device == 0)
#else
   sdl->speaker_device = SDL_OpenAudio(&spec, &out);

   if (sdl->speaker_device < 0)
#endif
   {
      RARCH_ERR("[SDL audio]: Failed to open SDL audio output device: %s\n", SDL_GetError());
      goto error;
   }

   *new_rate                = out.freq;

#ifdef HAVE_THREADS
   sdl->lock                = slock_new();
   sdl->cond                = scond_new();
#endif

   RARCH_LOG("[SDL audio]: Requested %u ms latency for output device, got %d ms\n",
         latency, (int)(out.samples * 4 * 1000 / (*new_rate)));

   /* Create a buffer twice as big as needed and prefill the buffer. */
   bufsize     = out.samples * 4 * sizeof(int16_t);
   tmp         = calloc(1, bufsize);
   sdl->speaker_buffer = fifo_new(bufsize);

   if (tmp)
   {
      fifo_write(sdl->speaker_buffer, tmp, bufsize);
      free(tmp);
   }

   SDL_PauseAudioDevice(sdl->speaker_device, false);

#if SDL_DRIVER_MIC_SUPPORT
   /* Now let's init the microphone */
   spec.callback = sdl_audio_record_cb; /* Microphone should have the same params as speaker */

   sdl->microphone_device = SDL_OpenAudioDevice(NULL, true, &spec, &out, 0);
   if (sdl->microphone_device == 0)
   {
      RARCH_WARN("[SDL audio]: Failed to open SDL audio input device: %s\n", SDL_GetError());
      RARCH_WARN("[SDL audio]: Either there's no microphone, or it couldn't be found.\n");
      /* Speakers are more common than microphones, so the absence of a microphone
       * will not be an error. */
   }
   else
   {
      RARCH_LOG("[SDL audio]: Requested %u ms latency for input device, got %d ms\n",
                latency, (int)(out.samples * 4 * 1000 / (out.freq)));

      /* Create a buffer twice as big as needed and prefill the buffer. */
      bufsize     = out.samples * 4 * sizeof(int16_t);
      tmp         = calloc(1, bufsize);
      sdl->microphone_buffer = fifo_new(bufsize);

      if (tmp)
      {
         fifo_write(sdl->microphone_buffer, tmp, bufsize);
         free(tmp);
      }

      SDL_PauseAudioDevice(sdl->microphone_device, false);
   }
#endif

   return sdl;

error:
   free(sdl);
   return NULL;
}

static ssize_t sdl_audio_write(void *data, const void *buf, size_t size)
{
   ssize_t ret      = 0;
   sdl_audio_t *sdl = (sdl_audio_t*)data;

   if (sdl->nonblock)
   {
      size_t avail, write_amt;

      SDL_LockAudioDevice(sdl->speaker_device);
      avail = FIFO_WRITE_AVAIL(sdl->speaker_buffer);
      write_amt = avail > size ? size : avail;
      fifo_write(sdl->speaker_buffer, buf, write_amt);
      SDL_UnlockAudioDevice(sdl->speaker_device);
      ret = write_amt;
   }
   else
   {
      size_t written = 0;

      while (written < size)
      {
         size_t avail;

         SDL_LockAudioDevice(sdl->speaker_device);
         avail = FIFO_WRITE_AVAIL(sdl->speaker_buffer);

         if (avail == 0)
         {
            SDL_UnlockAudioDevice(sdl->speaker_device);
#ifdef HAVE_THREADS
            slock_lock(sdl->lock);
            scond_wait(sdl->cond, sdl->lock);
            slock_unlock(sdl->lock);
#endif
         }
         else
         {
            size_t write_amt = size - written > avail ? avail : size - written;
            fifo_write(sdl->speaker_buffer, (const char*)buf + written, write_amt);
            SDL_UnlockAudioDevice(sdl->speaker_device);
            written += write_amt;
         }
      }
      ret = written;
   }

   return ret;
}

#if SDL_DRIVER_MIC_SUPPORT
static ssize_t sdl_audio_read(void *data, void *buf, size_t size)
{
   ssize_t ret      = 0;
   sdl_audio_t *sdl = (sdl_audio_t*)data;

   if (sdl->nonblock)
   {
      size_t avail, read_amt;

      SDL_LockAudioDevice(sdl->microphone_device);
      avail = FIFO_READ_AVAIL(sdl->microphone_buffer);
      read_amt = avail > size ? size : avail;
      fifo_read(sdl->microphone_buffer, buf, read_amt);
      SDL_UnlockAudioDevice(sdl->microphone_device);
      ret = read_amt;
   }
   else
   {
      size_t read = 0;

      while (read < size)
      {
         size_t avail;

         SDL_LockAudioDevice(sdl->microphone_device);
         avail = FIFO_READ_AVAIL(sdl->microphone_buffer);

         if (avail == 0)
         {
            SDL_UnlockAudioDevice(sdl->microphone_device);
#ifdef HAVE_THREADS
            slock_lock(sdl->lock);
            scond_wait(sdl->cond, sdl->lock);
            slock_unlock(sdl->lock);
#endif
         }
         else
         {
            size_t read_amt = size - read > avail ? avail : size - read;
            fifo_read(sdl->microphone_buffer, buf + read, read_amt);
            SDL_UnlockAudioDevice(sdl->microphone_device);
            read += read_amt;
         }
      }
      ret = read;
   }

   return ret;
}
#endif

static bool sdl_audio_stop(void *data)
{
   sdl_audio_t *sdl = (sdl_audio_t*)data;
   sdl->is_paused = true;
   SDL_PauseAudioDevice(sdl->speaker_device, true);

#if SDL_DRIVER_MIC_SUPPORT
   if (sdl->microphone_device)
   {
      SDL_PauseAudioDevice(sdl->microphone_device, true);
   }
#endif

   return true;
}

static bool sdl_audio_alive(void *data)
{
   sdl_audio_t *sdl = (sdl_audio_t*)data;
   if (!sdl)
      return false;
   return !sdl->is_paused;
}

static bool sdl_audio_start(void *data, bool is_shutdown)
{
   sdl_audio_t *sdl = (sdl_audio_t*)data;
   sdl->is_paused = false;

   SDL_PauseAudioDevice(sdl->speaker_device, false);

#if SDL_DRIVER_MIC_SUPPORT
   if (sdl->microphone_device)
   {
      SDL_PauseAudioDevice(sdl->microphone_device, false);
   }
#endif

   return true;
}

static void sdl_audio_set_nonblock_state(void *data, bool state)
{
   sdl_audio_t *sdl = (sdl_audio_t*)data;
   if (sdl)
      sdl->nonblock = state;
}

static void sdl_audio_free(void *data)
{
   sdl_audio_t *sdl = (sdl_audio_t*)data;

   if (sdl)
   {
      if (sdl->speaker_device > 0)
      {
         SDL_CloseAudioDevice(sdl->speaker_device);
      }

      if (sdl->speaker_buffer)
      {
         fifo_free(sdl->speaker_buffer);
      }

#if SDL_DRIVER_MIC_SUPPORT
      if (sdl->microphone_device > 0)
      { /* If the microphone was originally initialized successfully... */
         SDL_CloseAudioDevice(sdl->microphone_device);
      }

      if (sdl->microphone_buffer)
      {
         fifo_free(sdl->microphone_buffer);
      }
#endif

#ifdef HAVE_THREADS
      slock_free(sdl->lock);
      scond_free(sdl->cond);
#endif
   }
   free(sdl);
}

static bool sdl_audio_use_float(void *data)
{
   (void)data;
   return false;
}

static size_t sdl_audio_write_avail(void *data)
{
   /* stub */
   (void)data;
   return 0;
}

static size_t sdl_audio_read_avail(void *data)
{
   /* stub */
   (void)data;
   return 0;
}

audio_driver_t audio_sdl = {
   sdl_audio_init,
   sdl_audio_write,
#if SDL_DRIVER_MIC_SUPPORT
   sdl_audio_read,
#else
   NULL, /* Microphone support for this driver request SDL 2 */
#endif
   sdl_audio_stop,
   sdl_audio_start,
   sdl_audio_alive,
   sdl_audio_set_nonblock_state,
   sdl_audio_free,
   sdl_audio_use_float,
#ifdef HAVE_SDL2
   "sdl2",
#else
   "sdl",
#endif
   NULL,
   NULL,
   sdl_audio_write_avail,
   sdl_audio_read_avail,
   NULL
};
