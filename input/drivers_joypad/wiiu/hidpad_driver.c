/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2014-2017 - Ali Bouhlel
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

#include "../../include/wiiu/input.h"

/* TODO/FIXME - static global variables */
static bool hidpad_ready = false;

static bool init_hid_driver(void)
{
   return hid_init(&hid_instance, &wiiu_hid, &hidpad_driver, MAX_USERS);
}

static void hidpad_poll(void)
{
   if (hidpad_ready)
      HID_POLL();
}

static void *hidpad_init(void *data)
{
   if(!init_hid_driver())
   {
      RARCH_ERR("Failed to initialize HID driver.\n");
      return NULL;
   }

   hidpad_poll();
   hidpad_ready = true;

   return (void*)-1;
}

static bool hidpad_query_pad(unsigned port)
{
   return hidpad_ready && port < MAX_USERS;
}

static void hidpad_destroy(void)
{
   hidpad_ready = false;

   hid_deinit(&hid_instance);
}

static int32_t hidpad_button(unsigned port, uint16_t joykey)
{
   if (!hidpad_query_pad(port))
      return 0;
   return (HID_BUTTON(port, joykey));
}

static void hidpad_get_buttons(unsigned port, input_bits_t *state)
{
  if (!hidpad_query_pad(port))
    BIT256_CLEAR_ALL_PTR(state);

  HID_GET_BUTTONS(port, state);
}

static int16_t hidpad_axis(unsigned port, uint32_t axis)
{
   if (!hidpad_query_pad(port))
      return 0;
   return HID_AXIS(port, axis);
}

static int16_t hidpad_state(
      rarch_joypad_info_t *joypad_info,
      const struct retro_keybind *binds,
      unsigned port)
{
   unsigned i;
   int16_t ret                          = 0;
   uint16_t port_idx                    = joypad_info->joy_idx;

   if (!hidpad_query_pad(port_idx))
      return 0;

   for (i = 0; i < RARCH_FIRST_CUSTOM_BIND; i++)
   {
      /* Auto-binds are per joypad, not per user. */
      const uint64_t joykey  = (binds[i].joykey != NO_BTN)
         ? binds[i].joykey  : joypad_info->auto_binds[i].joykey;
      const uint32_t joyaxis = (binds[i].joyaxis != AXIS_NONE)
         ? binds[i].joyaxis : joypad_info->auto_binds[i].joyaxis;
      if (
               (uint16_t)joykey != NO_BTN
            && HID_BUTTON(port_idx, (uint16_t)joykey)
         )
         ret |= ( 1 << i);
      else if (joyaxis != AXIS_NONE &&
            ((float)abs(HID_AXIS(port_idx, joyaxis)) 
             / 0x8000) > joypad_info->axis_threshold)
         ret |= (1 << i);
   }

   return ret;
}

static const char *hidpad_name(unsigned port)
{
   if (!hidpad_query_pad(port))
      return "N/A";

   return HID_PAD_NAME(port);
}

input_device_driver_t hidpad_driver =
{
  hidpad_init,
  hidpad_query_pad,
  hidpad_destroy,
  hidpad_button,
  hidpad_state,
  hidpad_get_buttons,
  hidpad_axis,
  hidpad_poll,
  NULL,
  NULL,
  hidpad_name,
  "hid"
};
