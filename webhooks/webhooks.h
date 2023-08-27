/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2015-2016 - Andre Leiradella
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

#ifndef __WEBHOOKS_H
#define __WEBHOOKS_H

#include <stdint.h>
#include <stdlib.h>
#include <libretro.h>
#include <lrc_hash.h>

#include "rc_api_request.h"

#include "webhooks_game.h"

const int HASH_LENGTH = 33;
const int MACRO_LENGTH = 2048;

typedef struct wb_locals_t
{
  char hash[HASH_LENGTH];
  char macro[MACRO_LENGTH];
  struct rc_runtime_t runtime;
  rc_libretro_memory_regions_t memory;
  uint console_id;
} wb_locals_t;

void wb_initialize();

void webhooks_game_loaded(const struct retro_game_info* info);
void webhooks_game_unloaded();

void webhooks_process_frame();


void webhooks_send_presence();

void wh_send_game_event(int game_id, game_event_t game_event);

#endif /* __WEBHOOKS_H */
