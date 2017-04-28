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

#ifndef INPUT_CONFIG_H__
#define INPUT_CONFIG_H__

#include <stdint.h>

#include "input_driver.h"

extern struct retro_keybind input_config_binds[MAX_USERS][RARCH_BIND_LIST_END];
extern struct retro_keybind input_autoconf_binds[MAX_USERS][RARCH_BIND_LIST_END];
extern const struct retro_keybind *libretro_input_binds[MAX_USERS];
extern char input_device_names[MAX_USERS][64];

const char *input_config_bind_map_get_base(unsigned i);

unsigned input_config_bind_map_get_meta(unsigned i);

const char *input_config_bind_map_get_desc(unsigned i);

bool input_config_bind_map_get_valid(unsigned i);

/* auto_bind can be NULL. */
void input_config_get_bind_string(char *buf,
      const struct retro_keybind *bind,
      const struct retro_keybind *auto_bind, size_t size);

/**
 * input_config_translate_str_to_rk:
 * @str                            : String to translate to key ID.
 *
 * Translates tring representation to key identifier.
 *
 * Returns: key identifier.
 **/
enum retro_key input_config_translate_str_to_rk(const char *str);

const char *input_config_get_prefix(unsigned user, bool meta);

/**
 * input_config_translate_str_to_bind_id:
 * @str                            : String to translate to bind ID.
 *
 * Translate string representation to bind ID.
 *
 * Returns: Bind ID value on success, otherwise 
 * RARCH_BIND_LIST_END on not found.
 **/
unsigned input_config_translate_str_to_bind_id(const char *str);

void input_config_parse_key(void *data,
      const char *prefix, const char *btn,
      struct retro_keybind *bind);

void input_config_parse_joy_button(void *data, const char *prefix,
      const char *btn, struct retro_keybind *bind);

void input_config_parse_joy_axis(void *data, const char *prefix,
      const char *axis, struct retro_keybind *bind);

void input_config_set_device_name(unsigned port, const char *name);

void input_config_clear_device_name(unsigned port);

unsigned *input_config_get_device_ptr(unsigned port);

unsigned input_config_get_device(unsigned port);

void input_config_set_device(unsigned port, unsigned id);

const char *input_config_get_device_name(unsigned port);

const struct retro_keybind *input_config_get_bind_auto(unsigned port, unsigned id);

void input_config_set_pid(unsigned port, unsigned pid);

int32_t input_config_get_pid(unsigned port);

void input_config_set_vid(unsigned port, unsigned vid);

int32_t input_config_get_vid(unsigned port);

void input_config_reset(void);

#endif
