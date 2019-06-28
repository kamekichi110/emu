/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2010-2014 - Hans-Kristian Arntzen
 *  Copyright (C) 2011-2017 - Daniel De Matteis
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

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <boolean.h>
#include <retro_miscellaneous.h>

#include <libretro.h>

#include "../input_driver.h"

#ifndef MAX_PADS
#define MAX_PADS 4
#endif

/* TODO/FIXME -
 * fix game focus toggle */

typedef struct gx_input
{
   bool blocked;
   const input_device_driver_t *joypad;
} gx_input_t;

static int16_t gx_input_state(void *data,
      rarch_joypad_info_t joypad_info,
      const struct retro_keybind **binds,
      unsigned port, unsigned device,
      unsigned idx, unsigned id)
{
   gx_input_t *gx             = (gx_input_t*)data;
   int16_t ret                = 0;

   if (port >= MAX_PADS || !gx)
      return 0;

   switch (device)
   {
      case RETRO_DEVICE_JOYPAD:
         if (id == RETRO_DEVICE_ID_JOYPAD_MASK)
         {
            unsigned i;
            for (i = 0; i < RARCH_FIRST_CUSTOM_BIND; i++)
            {
               /* Auto-binds are per joypad, not per user. */
               const uint16_t joykey  = (binds[port][i].joykey != NO_BTN)
                  ? binds[port][i].joykey : joypad_info.auto_binds[i].joykey;
               const uint32_t joyaxis = (binds[port][i].joyaxis != AXIS_NONE)
                  ? binds[port][i].joyaxis : joypad_info.auto_binds[i].joyaxis;
               bool res               = false;

               if (joykey != NO_BTN && gx->joypad->button(joypad_info.joy_idx, joykey))
                  res = true;
               else if (((float)abs(gx->joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
                  res = true;

               if (res)
                  ret |= (1 << i);
            }
         }
         else
         {
            /* Auto-binds are per joypad, not per user. */
            const uint16_t joykey  = (binds[port][id].joykey != NO_BTN)
               ? binds[port][id].joykey : joypad_info.auto_binds[id].joykey;
            const uint32_t joyaxis = (binds[port][id].joyaxis != AXIS_NONE)
               ? binds[port][id].joyaxis : joypad_info.auto_binds[id].joyaxis;

            if (joykey != NO_BTN && gx->joypad->button(joypad_info.joy_idx, joykey))
               ret = 1;
            else if (((float)abs(gx->joypad->axis(joypad_info.joy_idx, joyaxis)) / 0x8000) > joypad_info.axis_threshold)
               ret = 1;
         }
         return ret;
      case RETRO_DEVICE_ANALOG:
         if (binds[port])
            return input_joypad_analog(gx->joypad,
                  joypad_info, port, idx, id, binds[port]);
         break;
   }

   return 0;
}

static void gx_input_free_input(void *data)
{
   gx_input_t *gx = (gx_input_t*)data;

   if (!gx)
      return;

   if (gx->joypad)
      gx->joypad->destroy();

   free(gx);
}

static void *gx_input_init(const char *joypad_driver)
{
   gx_input_t *gx = (gx_input_t*)calloc(1, sizeof(*gx));
   if (!gx)
      return NULL;

   gx->joypad = input_joypad_init_driver(joypad_driver, gx);

   return gx;
}

static void gx_input_poll(void *data)
{
   gx_input_t *gx = (gx_input_t*)data;

   if (gx && gx->joypad)
      gx->joypad->poll();
}

static uint64_t gx_input_get_capabilities(void *data)
{
   (void)data;

   return (1 << RETRO_DEVICE_JOYPAD) |  (1 << RETRO_DEVICE_ANALOG);
}

static const input_device_driver_t  *gx_input_get_joypad_driver(void *data)
{
   gx_input_t *gx = (gx_input_t*)data;
   if (!gx)
      return NULL;
   return gx->joypad;
}

static void gx_input_grab_mouse(void *data, bool state)
{
   (void)data;
   (void)state;
}

static bool gx_input_set_rumble(void *data, unsigned port,
      enum retro_rumble_effect effect, uint16_t strength)
{
   (void)data;
   (void)port;
   (void)effect;
   (void)strength;

   return false;
}

static bool gx_input_keyboard_mapping_is_blocked(void *data)
{
   gx_input_t *gx = (gx_input_t*)data;
   if (!gx)
      return false;
   return gx->blocked;
}

static void gx_input_keyboard_mapping_set_block(void *data, bool value)
{
   gx_input_t *gx = (gx_input_t*)data;
   if (!gx)
      return;
   gx->blocked = value;
}

input_driver_t input_gx = {
   gx_input_init,
   gx_input_poll,
   gx_input_state,
   gx_input_free_input,
   NULL,
   NULL,
   gx_input_get_capabilities,
   "gx",

   gx_input_grab_mouse,
   NULL,
   gx_input_set_rumble,
   gx_input_get_joypad_driver,
   NULL,
   gx_input_keyboard_mapping_is_blocked,
   gx_input_keyboard_mapping_set_block,
};
