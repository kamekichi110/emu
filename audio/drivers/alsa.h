/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2023 The RetroArch team
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


#ifndef _RETROARCH_ALSA
#define _RETROARCH_ALSA

/* Header file for common functions that are used by alsa and alsathread. */

/**
 * Used for info that's common to all pcm devices
 * that's relevant for our purposes.
 */
typedef struct alsa_stream_info {
   size_t buffer_size;
   unsigned int frame_bits;
   bool has_float;
   bool can_pause;
} alsa_stream_info_t;

int alsa_init_pcm(snd_pcm_t **pcm,
   const char* device,
   snd_pcm_stream_t stream,
   unsigned rate,
   unsigned latency,
   unsigned channels,
   alsa_stream_info_t *stream_info,
   unsigned *new_rate,
   int mode);
void alsa_free_pcm(snd_pcm_t *pcm);
void *alsa_device_list_new(void *data);
void alsa_device_list_free(void *data, void *array_list_data);

#endif /* _RETROARCH_ALSA */
