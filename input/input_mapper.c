/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2010-2014 - Hans-Kristian Arntzen
 *  Copyright (C) 2011-2017 - Daniel De Matteis
 *  Copyright (C) 2016-2017 - Andrés Suárez
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


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#else
#include <unistd.h>
#endif

#include <compat/strl.h>
#include <compat/posix_string.h>
#include <retro_miscellaneous.h>
#include <libretro.h>

#ifdef HAVE_MENU
#include "../menu/menu_driver.h"
#endif

#ifdef HAVE_CONFIG_H
#include "../config.h"
#endif

#include "input_mapper.h"

#include "../configuration.h"
#include "../msg_hash.h"
#include "../verbosity.h"

#define MAPPER_GET_KEY(state, key) (((state)->keys[(key) / 32] >> ((key) % 32)) & 1)
#define MAPPER_SET_KEY(state, key) (state)->keys[(key) / 32] |= 1 << ((key) % 32)
#define MAPPER_UNSET_KEY(state, key) (state)->keys[(key) / 32] |= 0 << ((key) % 32)

struct input_mapper
{
   /* The controller port that will be polled*/
   uint8_t port;
   /* Left X, Left Y, Right X, Right Y */
   int16_t analog[4];
   /* the whole keyboard state */
   uint32_t keys[RETROK_LAST / 32 + 1];
   /* This is a bitmask of (1 << key_bind_id). */
   retro_bits_t buttons;
};

input_mapper_t *input_mapper_new(uint16_t port)
{
   input_mapper_t* handle = (input_mapper_t*)
      calloc(1, sizeof(*handle));

   if (!handle)
      return NULL;

   handle->port = port;

   return handle;
}

void input_mapper_free(input_mapper_t *handle)
{
   if (!handle)
      return;
   free (handle);
}

bool flag = false;

bool input_mapper_button_pressed(input_mapper_t *handle, int id)
{
   return BIT256_GET(handle->buttons, id);
}

void input_mapper_poll(input_mapper_t *handle)
{
   int i, j;
   settings_t *settings = config_get_ptr();
   unsigned device      = settings->uints.input_libretro_device[handle->port];
   bool key_event[RARCH_CUSTOM_BIND_LIST_END];
#ifdef HAVE_MENU
   bool menu_is_alive   = menu_driver_is_alive();
#endif

   device              &= RETRO_DEVICE_MASK;

#ifdef HAVE_MENU
   if (menu_is_alive)
      return;
#endif

   memset(handle->keys, 0, sizeof(handle->keys));
   i = 0;
   if (device == RETRO_DEVICE_KEYBOARD)
   {
      for (i = 0; i < MAX_USERS; i++)
      {
         for (j = 0; j < RARCH_CUSTOM_BIND_LIST_END; j++)
         {
            if (j < RETROK_LAST)
            {
               if (input_state(i, RETRO_DEVICE_JOYPAD, 0, j) && 
                  settings->uints.input_keymapper_ids[i][j] != RETROK_UNKNOWN)
               {
                  MAPPER_SET_KEY (handle,
                     settings->uints.input_keymapper_ids[i][j]);
                  input_keyboard_event(true,
                        settings->uints.input_keymapper_ids[i][j],
                        0, 0, RETRO_DEVICE_KEYBOARD);
                  key_event[j] = true;
               }
               else
               {
                  if (key_event[j] == false && 
                     settings->uints.input_keymapper_ids[i][j] != RETROK_UNKNOWN)
                  {
                     input_keyboard_event(false,
                           settings->uints.input_keymapper_ids[i][j],
                           0, 0, RETRO_DEVICE_KEYBOARD);
                  }
               }
            }
         }
      }
   }
   if (device == RETRO_DEVICE_JOYPAD)
   {
      retro_bits_t current_input;
      input_keys_pressed(settings, &current_input);
      BIT256_CLEAR_ALL(handle->buttons);
      for (i = 0; i < MAX_USERS; i++)
      {
         for (j = 0; j < RARCH_CUSTOM_BIND_LIST_END; j++)
         {
            int aux = BIT256_GET(current_input, j);
            int remap = settings->uints.input_remap_ids[i][j];
            if (aux == 1 && j != remap)
               BIT256_SET(handle->buttons, remap);
         }
      }
   }
}

void input_mapper_state(
      input_mapper_t *handle,
      int16_t *ret,
      unsigned port,
      unsigned device,
      unsigned idx,
      unsigned id,
      bool clear)
{
   if (!handle)
      return;

   switch (device)
   {
      case RETRO_DEVICE_JOYPAD:
         /* we should get the new buttons here via input_remapper_button_pressed but it doesn't work because the old state is still there
            so both actions trigger */
         if (input_mapper_button_pressed(handle, id))
            *ret = 1;
         break;
      case RETRO_DEVICE_KEYBOARD:
         if (id < RETROK_LAST)
         {
            if (MAPPER_GET_KEY(handle, id))
               *ret |= 1;
         }
         break;
      default:
         break;
   }
   return;
}
