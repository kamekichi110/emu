﻿/*  RetroArch - A frontend for libretro.
 *  Copyright (C) 2011-2017 - Daniel De Matteis
 *  Copyright (C) 2016-2019 - Brad Parker
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
#include <stdint.h>
#include <stddef.h>

#include <compat/strl.h>
#include <string/stdstring.h>

#include "../msg_hash.h"
#include "../verbosity.h"

#ifdef RARCH_INTERNAL
#include "../configuration.h"

int menu_hash_get_help_tr_enum(enum msg_hash_enums msg, char *s, size_t len)
{
    settings_t *settings = config_get_ptr();

    if (msg == MENU_ENUM_LABEL_CONNECT_NETPLAY_ROOM)
    {
       snprintf(s, len,
             "TODO/FIXME - Fill in message here."
             );
       return 0;
    }
    if (msg <= MENU_ENUM_LABEL_INPUT_HOTKEY_BIND_END &&
        msg >= MENU_ENUM_LABEL_INPUT_HOTKEY_BIND_BEGIN)
    {
       unsigned idx = msg - MENU_ENUM_LABEL_INPUT_HOTKEY_BIND_BEGIN;

       switch (idx)
       {
          case RARCH_FAST_FORWARD_KEY:
             snprintf(s, len,
                   "Normal hız ve Hızlı-sarma arasında \n"
                   "geçiş yapar."
                   );
             break;
          case RARCH_FAST_FORWARD_HOLD_KEY:
             snprintf(s, len,
                   "Hızlı sarma için basılı tutun. \n"
                   " \n"
                   "Tuşu salmak hızlı-sarmayı iptal eder."
                   );
             break;
          case RARCH_SLOWMOTION_KEY:
             snprintf(s, len,
                   "Slowmotion arasında geçiş yapar.");
             break;
          case RARCH_SLOWMOTION_HOLD_KEY:
             snprintf(s, len,
                   "Slowmotion için basılı tutun.");
             break;
          case RARCH_PAUSE_TOGGLE:
             snprintf(s, len,
                   "Duraklatılmış ve duraklatılmamış durum arasında geçiş yap.");
             break;
          case RARCH_FRAMEADVANCE:
             snprintf(s, len,
                   "İçerik duraklatıldığında kare ilerlemesi.");
             break;
          case RARCH_SHADER_NEXT:
             snprintf(s, len,
                   "Dizindeki bir sonraki gölgelendiriciyi uygular.");
             break;
          case RARCH_SHADER_PREV:
             snprintf(s, len,
                   "Dizine önceki gölgelendiriciyi uygular.");
             break;
          case RARCH_CHEAT_INDEX_PLUS:
          case RARCH_CHEAT_INDEX_MINUS:
          case RARCH_CHEAT_TOGGLE:
             snprintf(s, len,
                   "Hileler.");
             break;
          case RARCH_RESET:
             snprintf(s, len,
                   "İçeriği sıfırla.");
             break;
          case RARCH_SCREENSHOT:
             snprintf(s, len,
                   "Ekran görüntüsü almak.");
             break;
          case RARCH_MUTE:
             snprintf(s, len,
                   "Sesi kapat/aç.");
             break;
          case RARCH_OSK:
             snprintf(s, len,
                   "Ekran klavyesini aç/kapat");
             break;
          case RARCH_FPS_TOGGLE:
             snprintf(s, len,
                   "Saniye sayacındaki kareleri değiştirir.");
             break;
          case RARCH_SEND_DEBUG_INFO:
             snprintf(s, len,
                   "Analiz için cihazınızın ve RetroArch yapılandırmasına ilişkin tanılama bilgilerini sunucularımıza gönderin.");
             break;
          case RARCH_NETPLAY_HOST_TOGGLE:
             snprintf(s, len,
                   "Netplay barındırma özelliğini açar/kapatır.");
             break;
          case RARCH_NETPLAY_GAME_WATCH:
             snprintf(s, len,
                   "Netplay toggle play/spectate mode.");
             break;
          case RARCH_ENABLE_HOTKEY:
             snprintf(s, len,
                   "Diğer kısayol tuşlarını etkinleştirin. \n"
                   " \n"
                   "If this hotkey is bound to either\n"
                   "a keyboard, joybutton or joyaxis, \n"
                   "all other hotkeys will be enabled only \n"
                   "if this one is held at the same time. \n"
                   " \n"
                   "Alternatively, all hotkeys for keyboard \n"
                   "could be disabled by the user.");
             break;
          case RARCH_VOLUME_UP:
             snprintf(s, len,
                   "Ses seviyesini arttırır.");
             break;
          case RARCH_VOLUME_DOWN:
             snprintf(s, len,
                   "Ses seviyesini azaltır.");
             break;
          case RARCH_OVERLAY_NEXT:
             snprintf(s, len,
                   "Switches to next overlay. Wraps around.");
             break;
          case RARCH_DISK_EJECT_TOGGLE:
             snprintf(s, len,
                   "Diskler için çıkarmayı değiştirir. \n"
                   " \n"
                   "Birden fazla disk içeriği için kullanılır. ");
             break;
          case RARCH_DISK_NEXT:
          case RARCH_DISK_PREV:
             snprintf(s, len,
                   "Disk görüntüleri arasında geçiş yapar. Çıkardıktan sonra kullanın. \n"
                   " \n"
                   "Çıkartmayı tekrar açarak tamamlayın.");
             break;
          case RARCH_GRAB_MOUSE_TOGGLE:
             snprintf(s, len,
                   "Fare tutmayı değiştirir. \n"
                   " \n"
                   "When mouse is grabbed, RetroArch hides the \n"
                   "mouse, and keeps the mouse pointer inside \n"
                   "the window to allow relative mouse input to \n"
                   "work better.");
             break;
          case RARCH_GAME_FOCUS_TOGGLE:
             snprintf(s, len,
                   "Oyun odağını değiştirir.\n"
                   " \n"
                   "When a game has focus, RetroArch will both disable \n"
                   "hotkeys and keep/warp the mouse pointer inside the window.");
             break;
          case RARCH_MENU_TOGGLE:
             snprintf(s, len, "Toggles menu.");
             break;
          case RARCH_LOAD_STATE_KEY:
             snprintf(s, len,
                   "Loads state.");
             break;
          case RARCH_FULLSCREEN_TOGGLE_KEY:
             snprintf(s, len,
                   "Tam ekrana geçer.");
             break;
          case RARCH_QUIT_KEY:
             snprintf(s, len,
                   "RetroArch'tan temiz bir şekilde çıkmak için basın. \n"
                   " \n"
                   "Killing it in any hard way (SIGKILL, etc.) will \n"
                   "terminate RetroArch without saving RAM, etc."
#ifdef __unix__
                   "\nOn Unix-likes, SIGINT/SIGTERM allows a clean \n"
                   "deinitialization."
#endif
                   "");
             break;
          case RARCH_STATE_SLOT_PLUS:
          case RARCH_STATE_SLOT_MINUS:
             snprintf(s, len,
                   "State slots. \n"
                   " \n"
                   "With slot set to 0, save state name is \n"
                   "*.state (or whatever defined on commandline). \n"
                   " \n"
                   "When slot is not 0, path will be <path><d>, \n"
                   "where <d> is slot number.");
             break;
          case RARCH_SAVE_STATE_KEY:
             snprintf(s, len,
                   "Saves state.");
             break;
          case RARCH_REWIND:
             snprintf(s, len,
                   "Geri sarmak için düğmeyi basılı tutun. \n"
                   " \n"
                   "Geri sarma etkin olmalı.");
             break;
          case RARCH_BSV_RECORD_TOGGLE:
             snprintf(s, len,
                   "Toggle between recording and not.");
             break;
          default:
             if (string_is_empty(s))
                strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NO_INFORMATION_AVAILABLE), len);
             break;
       }

       return 0;
    }

    switch (msg)
    {
        case MENU_ENUM_LABEL_ACCOUNTS_RETRO_ACHIEVEMENTS:
            snprintf(s, len, "Retro Achievements hesabı için \n"
                    "giriş bilgileri \n"
                    " \n"
                    "Retroachievements.org adresini ziyaret edin ve \n"
                    "ücretsiz bir hesap için kaydolun. \n"
                    " \n"
                    "Kayıt işlemini tamamladıktan sonra,  \n"
                    "kullanıcı adınızı ve şifrenizi RetroArch'a \n"
                    "girmeniz gerekir.");
            break;
        case MENU_ENUM_LABEL_CHEEVOS_USERNAME:
            snprintf(s, len, "RetroAchievements hesabınızın kullanıcı adı.");
            break;
        case MENU_ENUM_LABEL_CHEEVOS_PASSWORD:
            snprintf(s, len, "RetroAchievements hesabınızın şifresi.");
            break;
        case MENU_ENUM_LABEL_USER_LANGUAGE:
            snprintf(s, len, "LMenüyü ve ekrandaki tüm mesajları burada \n"
                    "seçtiğiniz dile göre yerelleştirir. \n"
                    " \n"
                    "Değişikliklerin etkili olması için \n"
                    "yeniden başlatmayı gerektirir.  \n"
                    " \n"
                    "Not: Tüm diller şu anda uygulanamayabilir \n"
                    "Dilin uygulanmaması durumunda \n"
                    "İngilizce'ye geri dönülür.");
            break;
        case MENU_ENUM_LABEL_VIDEO_FONT_PATH:
            snprintf(s, len, "Ekran Görününen metin için \n"
                    "kullanılan yazı tipini değiştirin.");
            break;
        case MENU_ENUM_LABEL_GAME_SPECIFIC_OPTIONS:
            snprintf(s, len, "İçeriğe özgü Core seçeneklerini otomatik olarak yükle.");
            break;
        case MENU_ENUM_LABEL_AUTO_OVERRIDES_ENABLE:
            snprintf(s, len, "Üzerine yazma yapılandırmalarını otomatik olarak yükle.");
            break;
        case MENU_ENUM_LABEL_AUTO_REMAPS_ENABLE:
            snprintf(s, len, "Yeniden düzenleme dosyalarını otomatik olarak yükle.");
            break;
        case MENU_ENUM_LABEL_SORT_SAVESTATES_ENABLE:
            snprintf(s, len, "Sort save states in folders \n"
                    "named after the libretro core used.");
            break;
        case MENU_ENUM_LABEL_SORT_SAVEFILES_ENABLE:
            snprintf(s, len, "Sort save files in folders \n"
                    "named after the libretro core used.");
            break;
        case MENU_ENUM_LABEL_RESUME_CONTENT:
            snprintf(s, len, "Menüden çıkar ve içeriğe geri döner.");
            break;
        case MENU_ENUM_LABEL_RESTART_CONTENT:
            snprintf(s, len, "İçeriği yeniden başlatır.");
            break;
        case MENU_ENUM_LABEL_CLOSE_CONTENT:
            snprintf(s, len, "İçeriği kapatır ve bellekten kaldırır.");
            break;
        case MENU_ENUM_LABEL_UNDO_LOAD_STATE:
            snprintf(s, len, "If a state was loaded, content will \n"
                    "go back to the state prior to loading.");
            break;
        case MENU_ENUM_LABEL_UNDO_SAVE_STATE:
            snprintf(s, len, "If a state was overwritten, it will \n"
                    "roll back to the previous save state.");
            break;
        case MENU_ENUM_LABEL_TAKE_SCREENSHOT:
            snprintf(s, len, "Bir ekran görüntüsü oluşturun. \n"
                    " \n"
                    "Ekran görüntüsü dizininde saklanacak.");
            break;
        case MENU_ENUM_LABEL_ADD_TO_FAVORITES:
            snprintf(s, len, "Girdinizi Favorilerinize ekleyin.");
            break;
        case MENU_ENUM_LABEL_RUN:
            snprintf(s, len, "İçeriği başlat.");
            break;
        case MENU_ENUM_LABEL_INFORMATION:
            snprintf(s, len, "İçerik hakkında ek meta veri \n"
                    "bilgilerini göster.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_CONFIG:
            snprintf(s, len, "Konfigürasyon dosyası.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_COMPRESSED_ARCHIVE:
            snprintf(s, len, "Sıkıştırılmış arşiv dosyası.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_RECORD_CONFIG:
            snprintf(s, len, "Kayıt yapılandırma dosyası.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_CURSOR:
            snprintf(s, len, "Veritabanı imleci dosyası.");
            break;
        case MENU_ENUM_LABEL_FILE_CONFIG:
            snprintf(s, len, "Konfigürasyon dosyası.");
            break;
        case MENU_ENUM_LABEL_SCAN_THIS_DIRECTORY:
            snprintf(s, len,
                     "Geçerli dizinde içerik taramak bunu seçin.");
            break;
        case MENU_ENUM_LABEL_USE_THIS_DIRECTORY:
            snprintf(s, len,
                     "Burayı dizin olarak ayarlamak seçin.");
            break;
        case MENU_ENUM_LABEL_CONTENT_DATABASE_DIRECTORY:
            snprintf(s, len,
                     "İçerik Veritabanı Dizini. \n"
                             " \n"
                             "Path to content database \n"
                             "directory.");
            break;
        case MENU_ENUM_LABEL_THUMBNAILS_DIRECTORY:
            snprintf(s, len,
                     "Küçük Resimler Dizini. \n"
                             " \n"
                             "To store thumbnail files.");
            break;
        case MENU_ENUM_LABEL_LIBRETRO_INFO_PATH:
            snprintf(s, len,
                     "Core Bilgi Dizini. \n"
                             " \n"
                             "A directory for where to search \n"
                             "for libretro core information.");
            break;
        case MENU_ENUM_LABEL_PLAYLIST_DIRECTORY:
            snprintf(s, len,
                     "Playlist Dizini. \n"
                             " \n"
                             "Save all playlist files to this \n"
                             "directory.");
            break;
        case MENU_ENUM_LABEL_DUMMY_ON_CORE_SHUTDOWN:
            snprintf(s, len,
                     "Some cores might have \n"
                             "a shutdown feature. \n"
                             " \n"
                             "If this option is left disabled, \n"
                             "selecting the shutdown procedure \n"
                             "would trigger RetroArch being shut \n"
                             "down. \n"
                             " \n"
                             "Enabling this option will load a \n"
                             "dummy core instead so that we remain \n"
                             "inside the menu and RetroArch won't \n"
                             "shutdown.");
            break;
        case MENU_ENUM_LABEL_CHECK_FOR_MISSING_FIRMWARE:
            snprintf(s, len,
                     "Bazı Core'lar için firmware \n"
                             "veya bios dosyasına ihtiyaç duyulabilir. \n"
                             " \n"
                             "Eğer bu seçenek etkisizleştirilirse, \n"
                             "firmware olmasa bile yüklemeyi \n"
                             "deneyecektir. \n");
            break;
        case MENU_ENUM_LABEL_PARENT_DIRECTORY:
            snprintf(s, len,
                     "Üst dizine geri dönün.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_OPEN_UWP_PERMISSIONS:
            snprintf(s, len,
                     "BroadFileSystemAccess özelliğini etkinleştirmek \n"
                     "için Windows izin ayarlarını açın. ");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_OPEN_PICKER:
           snprintf(s, len,
                     "Ek dizinlere erişmek için \n"
                     "sistem dosyası seçiciyi açın.");
           break;
        case MENU_ENUM_LABEL_FILE_BROWSER_SHADER_PRESET:
            snprintf(s, len,
                     "Hazır Shader dosyası.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_SHADER:
            snprintf(s, len,
                     "Shader dosyası.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_REMAP:
            snprintf(s, len,
                     "Remap kontrolleri dosyası.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_CHEAT:
            snprintf(s, len,
                     "Hile dosyası.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_OVERLAY:
            snprintf(s, len,
                     "Overlay dosyası.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_RDB:
            snprintf(s, len,
                     "Veritabanı dosyası.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_FONT:
            snprintf(s, len,
                     "TrueType font dosyası.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_PLAIN_FILE:
            snprintf(s, len,
                     "Plain file.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_MOVIE_OPEN:
            snprintf(s, len,
                     "Video. \n"
                             " \n"
                             "Video oynatıcısını açmak için  \n"
                             "kullanılır.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_MUSIC_OPEN:
            snprintf(s, len,
                     "Müzik. \n"
                             " \n"
                             "Müzik oynatıcısını açmak için  \n"
                             "kullanılır.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_IMAGE:
            snprintf(s, len,
                     "Resim dosyası.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_IMAGE_OPEN_WITH_VIEWER:
            snprintf(s, len,
                     "Resim. \n"
                             " \n"
                             "Resim görüntüleyecisini açmak için  \n"
                             "kullanılır.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_CORE_SELECT_FROM_COLLECTION:
            snprintf(s, len,
                     "Libretro core. \n"
                             " \n"
                             "Selecting this will associate this core \n"
                             "to the game.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_CORE:
            snprintf(s, len,
                     "Libretro core. \n"
                             " \n"
                             "Select this file to have RetroArch load this core.");
            break;
        case MENU_ENUM_LABEL_FILE_BROWSER_DIRECTORY:
            snprintf(s, len,
                     "Dizin. \n"
                             " \n"
                             "Dizin açmak için seçin.");
            break;
        case MENU_ENUM_LABEL_CACHE_DIRECTORY:
            snprintf(s, len,
                     "Önbellek Dizini. \n"
                             " \n"
                             "RetroArch tarafından sıkıştırılmış içerik \n"
                             "geçici olarak bu dizine çıkarılır.");
            break;
        case MENU_ENUM_LABEL_HISTORY_LIST_ENABLE:
            snprintf(s, len,
                     "If enabled, every content loaded \n"
                             "in RetroArch will be automatically \n"
                             "added to the recent history list.");
            break;
        case MENU_ENUM_LABEL_RGUI_BROWSER_DIRECTORY:
            snprintf(s, len,
                     "Dosya Tarayıcı Dizini. \n"
                             " \n"
                             "Menü dosyası tarayıcısı için başlangıç dizinini ayarlar.");
            break;
        case MENU_ENUM_LABEL_INPUT_POLL_TYPE_BEHAVIOR:
            snprintf(s, len,
                     "Influence how input polling is done inside \n"
                             "RetroArch. \n"
                             " \n"
                             "Early  - Input polling is performed before \n"
                             "the frame is processed. \n"
                             "Normal - Input polling is performed when \n"
                             "polling is requested. \n"
                             "Late   - Input polling is performed on \n"
                             "first input state request per frame.\n"
                             " \n"
                             "Setting it to 'Early' or 'Late' can result \n"
                             "in less latency, \n"
                             "depending on your configuration.\n\n"
                             "Will be ignored when using netplay."
            );
            break;
        case MENU_ENUM_LABEL_INPUT_DESCRIPTOR_HIDE_UNBOUND:
            snprintf(s, len,
                     "Hide input descriptors that were not set \n"
                             "by the core.");
            break;
        case MENU_ENUM_LABEL_VIDEO_REFRESH_RATE:
            snprintf(s, len,
                     "Video refresh rate of your monitor. \n"
                             "Used to calculate a suitable audio input rate.");
            break;
        case MENU_ENUM_LABEL_VIDEO_FORCE_SRGB_DISABLE:
            snprintf(s, len,
                     "Forcibly disable sRGB FBO support. Some Intel \n"
                             "OpenGL drivers on Windows have video problems \n"
                             "with sRGB FBO support enabled.");
            break;
        case MENU_ENUM_LABEL_AUDIO_ENABLE:
            snprintf(s, len,
                     "Ses çıkışını etkinleştir.");
            break;
        case MENU_ENUM_LABEL_AUDIO_SYNC:
            snprintf(s, len,
                     "Sesi senkronize et (önerilir).");
            break;
        case MENU_ENUM_LABEL_AUDIO_LATENCY:
            snprintf(s, len,
                     "Desired audio latency in milliseconds. \n"
                             "Might not be honored if the audio driver \n"
                             "can't provide given latency.");
            break;
        case MENU_ENUM_LABEL_VIDEO_ALLOW_ROTATE:
            snprintf(s, len,
                     "Allow cores to set rotation. If false, \n"
                             "rotation requests are honored, but ignored.\n\n"
                             "Used for setups where one manually rotates \n"
                             "the monitor.");
            break;
        case MENU_ENUM_LABEL_INPUT_DESCRIPTOR_LABEL_SHOW:
            snprintf(s, len,
                     "Show the input descriptors set by the core \n"
                             "instead of the default ones.");
            break;
        case MENU_ENUM_LABEL_CONTENT_HISTORY_SIZE:
            snprintf(s, len,
                     "Number of entries that will be kept in \n"
                             "content history playlist.");
            break;
        case MENU_ENUM_LABEL_VIDEO_WINDOWED_FULLSCREEN:
            snprintf(s, len,
                     "To use windowed mode or not when going \n"
                             "fullscreen.");
            break;
        case MENU_ENUM_LABEL_VIDEO_FONT_SIZE:
            snprintf(s, len,
                     "Ekrandaki mesajlar için yazı tipi boyutu.");
            break;
        case MENU_ENUM_LABEL_SAVESTATE_AUTO_INDEX:
            snprintf(s, len,
                     "Automatically increment slot index on each save, \n"
                             "generating multiple savestate files. \n"
                             "When the content is loaded, state slot will be \n"
                             "set to the highest existing value (last savestate).");
            break;
        case MENU_ENUM_LABEL_FPS_SHOW:
            snprintf(s, len,
                     "Enables displaying the current frames \n"
                             "per second.");
            break;
        case MENU_ENUM_LABEL_MEMORY_SHOW:
            snprintf(s, len,
                     "Geçerli bellek kullanımı/toplamının FPS/Kareler \n"
                             "ile görüntülenmesini içerir.");
            break;
        case MENU_ENUM_LABEL_VIDEO_FONT_ENABLE:
            snprintf(s, len,
                     "Ekrandaki mesajları göster veya gizle.");
            break;
        case MENU_ENUM_LABEL_VIDEO_MESSAGE_POS_X:
        case MENU_ENUM_LABEL_VIDEO_MESSAGE_POS_Y:
            snprintf(s, len,
                     "Offset for where messages will be placed \n"
                             "onscreen. Values are in range [0.0, 1.0].");
            break;
        case MENU_ENUM_LABEL_INPUT_OVERLAY_ENABLE:
            snprintf(s, len,
                     "Geçerli kaplamayı etkinleştirin veya devre dışı bırakın.");
            break;
        case MENU_ENUM_LABEL_INPUT_OVERLAY_HIDE_IN_MENU:
            snprintf(s, len,
                     "Geçerli kaplamayı menü içinde \n"
                             "görünmesini engelleyin.");
            break;
        case MENU_ENUM_LABEL_INPUT_OVERLAY_SHOW_PHYSICAL_INPUTS:
            snprintf(s, len,
                      "Ekran kaplaması üzerindeki klavye/denetleyici \n"
                            "düğmesine basıldığında gösterir.");
            break;
        case MENU_ENUM_LABEL_INPUT_OVERLAY_SHOW_PHYSICAL_INPUTS_PORT:
            snprintf(s, len,
                      "Select the port to listen for controller input \n"
                            "to display on the onscreen overlay.");
            break;
        case MENU_ENUM_LABEL_OVERLAY_PRESET:
            snprintf(s, len,
                     "Kaplamanın girdi yolu.");
            break;
        case MENU_ENUM_LABEL_OVERLAY_OPACITY:
            snprintf(s, len,
                     "Kaplama opaklığı.");
            break;
        case MENU_ENUM_LABEL_INPUT_BIND_TIMEOUT:
            snprintf(s, len,
                     "Input bind timer timeout (in seconds). \n"
                             "Amount of seconds to wait until proceeding \n"
                             "to the next bind.");
            break;
        case MENU_ENUM_LABEL_INPUT_BIND_HOLD:
            snprintf(s, len,
               "Giriş tuşunun basılı tutma süresi (saniye cinsinden). \n"
               "Basılı tutma için geçerli olan saniye miktarı.");
            break;
        case MENU_ENUM_LABEL_OVERLAY_SCALE:
            snprintf(s, len,
                     "Kaplama ölçeği.");
            break;
        case MENU_ENUM_LABEL_AUDIO_OUTPUT_RATE:
            snprintf(s, len,
                     "Ses çıkışı örneklemesi.");
            break;
        case MENU_ENUM_LABEL_VIDEO_SHARED_CONTEXT:
            snprintf(s, len,
                     "Donanım tarafından oluşturulan Core'un \n"
                             "kendi özel bağlamlarını alması gerekiyorsa 'true' \n"
                             "olarak ayarlayın. Donanım durumlarının çerçeveler \n"
                             "arasında değişiklik yapması gerektiğini unutmayın."
            );
            break;
        case MENU_ENUM_LABEL_CORE_LIST:
            snprintf(s, len,
                     "Core yükle. \n"
                             " \n"
                             "Libretro Core uygulaması \n"
                             "için göz atın. Tarayıcının başladığı yer \n"
                             "Core Dizin yolunuza bağlıdır \n"
                             "Boşsa, root'ta başlayacaktır. \n"
                             " \n"
                             "Core Dizini bir dizinse, menü bunu üst klasör olarak kullanır. \n"
                             "Core Dizini tam yol ise, \n"
                             "dosyanın bulunduğu klasörde \n"
                             "başlayacaktır.");
            break;
        case MENU_ENUM_LABEL_VALUE_MENU_ENUM_CONTROLS_PROLOG:
            snprintf(s, len,
                     "Menüyü kontrol etmek için \n"
                             "gamepad'inizde veya klavyenizde aşağıdaki\n"
                             "kontrolleri kullanabilirsiniz: \n"
                             " \n"
            );
            break;
        case MENU_ENUM_LABEL_WELCOME_TO_RETROARCH:
            snprintf(s, len,
                     "RetroArch'a Hoşgeldiniz\n"
            );
            break;
        case MENU_ENUM_LABEL_VALUE_HELP_AUDIO_VIDEO_TROUBLESHOOTING_DESC: {
            /* Work around C89 limitations */
            char u[501];
            const char *t =
                    "RetroArch, en iyi performans sonuçları için\n"
                            "ekranınızın yenileme hızına göre kalibre edilmesi gereken\n"
                            "benzersiz bir ses/video senkronizasyonu şekline dayanır.\n"
                            "Herhangi bir ses çatlaması veya video yırtılması yaşarsanız,\n"                   
                            " \n"
                            "genellikle ayarları yapmanız anlamına gelir.\n"
                            "Aşağıdaki seçenekler gibi:\n"
                            " \n";
            snprintf(u, sizeof(u), /* can't inline this due to the printf arguments */
                     "a) '%s' -> '%s' gidin, ve 'Threaded Video'\n"
                             "etkinleştirin. Yenileme hızı bu modda\n"
                             "önemli olmayacaktır, kare hızı daha yüksek\n"
                             "olacaktır ancak video daha az düzgün olabilir.\n"
                             "b) '%s' -> '%s' gidin, ve '%s' bakın\n"
                             "2048 karede çalışmasına izin verin,\n"
                             "ardından 'Tamam'a basın.",
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SETTINGS),
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_VIDEO_SETTINGS),
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SETTINGS),
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_VIDEO_SETTINGS),
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_VIDEO_REFRESH_RATE_AUTO));
            strlcpy(s, t, len);
            strlcat(s, u, len);
        }
            break;
        case MENU_ENUM_LABEL_VALUE_HELP_SCANNING_CONTENT_DESC:
            snprintf(s, len,
                     "İçerik taramak için, '%s' gidin ve \n"
                             "'%s' veya %s' seçin.\n"
                             " \n"
                             "Dosyalar veritabanı girişleriyle karşılaştırılacak.\n"
                             "Bir eşleşme varsa, koleksiyona bir giriş ekler.\n"
                             " \n"
                             "Bu içeriğe daha sonra kolayca erişebilmek için\n"
                             "'%s' gidin. ->\n"
                             "'%s'\n"
                             "Her seferinde dosya tarayıcısına\n"
                             "gitmek zorunda kalmazsınız.\n"
                             " \n"
                             "NOTE: Bazı içerikler Corelar tarafından\n"
                             "taranmayabilir.",
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ADD_CONTENT_LIST),
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SCAN_DIRECTORY),
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SCAN_FILE),
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_LOAD_CONTENT_LIST),
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_PLAYLISTS_TAB)
            );
            break;
        case MENU_ENUM_LABEL_VALUE_EXTRACTING_PLEASE_WAIT:
            snprintf(s, len,
                     "RetroArch'a Hoşgeldiniz\n"
                             "\n"
                             "Varlıklar ayıklanıyor, lütfen bekleyin.\n"
                             "İşlem biraz zaman alabilir...\n"
            );
            break;
        case MENU_ENUM_LABEL_INPUT_DRIVER:
            {
               const char *lbl = settings ? settings->arrays.input_driver : NULL;

               if (string_is_equal(lbl, msg_hash_to_str(MENU_ENUM_LABEL_INPUT_DRIVER_UDEV)))
                     snprintf(s, len,
                           "udev sürücüsü. \n"
                           " \n"
                           "Joystick desteği için en son evdev \n"
                           "joypad API'sini kullanır. Hotplugging \n"
                           "özelliğini destekler ve geribildirimi zorlar. \n"
                           " \n"
                           "The driver reads evdev events for keyboard \n"
                           "support. It also supports keyboard callback, \n"
                           "mice and touchpads. \n"
                           " \n"
                           "By default in most distros, /dev/input nodes \n"
                           "are root-only (mode 600). You can set up a udev \n"
                           "rule which makes these accessible to non-root."
                           );
               else if (string_is_equal(lbl,
                        msg_hash_to_str(MENU_ENUM_LABEL_INPUT_DRIVER_LINUXRAW)))
                     snprintf(s, len,
                           "linuxraw sürücüsü. \n"
                           " \n"
                           "Bu sürücü aktif bir TTY gerektiriyor. \n"
                           "Klavye olayları doğrudan TTY'den okunur; \n"
                           "bu da onu basitleştirir, ancak udev kadar esnek değildir. \n" "Mice, vb, desteklenmiyor. \n"
                           " \n"
                           "Bu sürücü eski joystick API'sini kullanır \n"
                           "(/dev/input/js*).");
               else
                     snprintf(s, len,
                           "Giriş sürücüsü.\n"
                           " \n"
                           "Video sürücüsüne bağlı olarak, \n"
                           "farklı bir giriş sürücüsünü zorlayabilir. ");
            }
            break;
        case MENU_ENUM_LABEL_LOAD_CONTENT_LIST:
            snprintf(s, len,
                     "İçeriği Yükle. \n"
                             "İçeriğe göz at. \n"
                             " \n"
                             "İçeriği yüklemek için, 'Core' ve \n"
                             "içerik dosyasına ihtiyacınız vardır.  \n"
                             " \n"
                             "Menünün, içeriğe göz atmaya başlayacağı yeri \n"
                             "kontrol etmek için 'Dosya Tarayıcı Dizini'ni  \n"
                             "ayarlayın. Ayarlanmazsa, \n"
                             "kök dizininden başlayacaktır. \n"
                             " \n"
                             "Tarayıcı, 'Core Yükle'den ayarlanan son Core \n"
                             "için uzantıları filtreleyecek ve içerik \n"
                             "yüklendiğinde bu çekirdeği kullanacaktır."
            );
            break;
        case MENU_ENUM_LABEL_LOAD_CONTENT_HISTORY:
            snprintf(s, len,
                     "Geçmişten içerik yükleniyor. \n"
                             " \n"
                             "İçerik yüklendikçe, içerik ve libretro \n"
                             "Core kombinasyonları geçmişe kaydedilir. \n"
                             " \n"
                             "Geçmiş, RetroArch yapılandırma dosyasıyla aynı \n"
                             "dizindeki bir dosyaya kaydedilir. Başlangıçta hiçbir \n"
                             "yapılandırma dosyası yüklenmemişse, geçmiş kaydedilmeyecek \n"
                             "veya yüklenmeyecek ve ana menüde bulunmayacaktır. "
            );
            break;
        case MENU_ENUM_LABEL_VIDEO_DRIVER:
            snprintf(s, len,
                     "Geçerli Video sürücüsü.");

            if (string_is_equal(settings->arrays.video_driver, "gl"))
            {
                snprintf(s, len,
                         "OpenGL Video sürücüsü. \n"
                                 " \n"
                                 "Bu sürücü, yazılım tarafından oluşturulan \n"
                                 "Core uygulamalarına ek olarak libretro GL \n"
                                 "çekirdeklerinin kullanılmasına izin verir.\n"
                                 " \n"
                                 "Yazılım tarafından oluşturulan ve libretro GL \n"
                                 "Core uygulamaları için performans, \n"
                                 "grafik kartınızın temelindeki GL sürücüsüne bağlıdır.");
            }
            else if (string_is_equal(settings->arrays.video_driver, "sdl2"))
            {
                snprintf(s, len,
                         "SDL 2 Video sürücüsü.\n"
                                 " \n"
                                 "Bu bir SDL 2 yazılımı tarafından oluşturulan \n"
                                 "video sürücüsüdür.\n"
                                 " \n"
                                 "Yazılım tarafından oluşturulan libretro Core uygulamaları \n"
                                 "için performans, SDL uygulamanıza bağlıdır.");
            }
            else if (string_is_equal(settings->arrays.video_driver, "sdl1"))
            {
                snprintf(s, len,
                         "SDL Video sürücüsü.\n"
                                 " \n"
                                 "Bu bir SDL 1.2 yazılımı tarafından üretilmiş \n"
                                 "video sürücüsüdür.\n"
                                 " \n"
                                 "Performansın yetersiz olduğu kabul edilir. \n"
                                 "Sadece son çare olarak kullanmayı düşünün.");
            }
            else if (string_is_equal(settings->arrays.video_driver, "d3d"))
            {
                snprintf(s, len,
                         "Direct3D Video sürücüsü. \n"
                                 " \n"
                                 "Yazılım tarafından oluşturulan Core performansı,\n"
                                 "grafik kartınızın temelindeki D3D \n"
                                 "sürücüsüne bağlıdır.");
            }
            else if (string_is_equal(settings->arrays.video_driver, "exynos"))
            {
                snprintf(s, len,
                         "Exynos-G2D Video sürücüsü. \n"
                                 " \n"
                                 "Bu, düşük seviye bir Exynos video sürücüsüdür. \n"
                                 "Karışım işlemleri için Samsung Exynos SoC'daki \n"
                                 " G2D bloğunu kullanır. \n"
                                 " \n"
                                 "Yazılım tarafından oluşturulan Core performansı \n"
                                 "optimum olmalıdır.");
            }
            else if (string_is_equal(settings->arrays.video_driver, "drm"))
            {
                snprintf(s, len,
                         "Plain DRM Video sürücüsü. \n"
                                 " \n"
                                 "Bu düşük bir seviye video sürücüsüdür. \n"
                                 "GPU kaplamalarını için libdrm donanım ölçeklendirmesi kullanır.");
            }
            else if (string_is_equal(settings->arrays.video_driver, "sunxi"))
            {
                snprintf(s, len,
                         "Sunxi-G2D Video sürücüsü. \n"
                                 " \n"
                                 "Bu düşük seviye bir Sunxi video sürücüsü. \n"
                                 "Allwinner SoC'lerde G2D bloğunu kullanır.");
            }
            break;
        case MENU_ENUM_LABEL_AUDIO_DSP_PLUGIN:
            snprintf(s, len,
                     "Audio DSP ektesi.\n"
                             "Sesi sürücüye göndermeden \n"
                             "önce işler."
            );
            break;
        case MENU_ENUM_LABEL_AUDIO_RESAMPLER_DRIVER:
            {
               const char *lbl = settings ? settings->arrays.audio_resampler : NULL;

               if (string_is_equal(lbl, msg_hash_to_str(
                           MENU_ENUM_LABEL_AUDIO_RESAMPLER_DRIVER_SINC)))
                  strlcpy(s,
                        "Pencereli SINC uygulaması.", len);
               else if (string_is_equal(lbl, msg_hash_to_str(
                           MENU_ENUM_LABEL_AUDIO_RESAMPLER_DRIVER_CC)))
                  strlcpy(s,
                        "Kıvrımlı kosinüs uygulaması.", len);
               else if (string_is_empty(s))
                  strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NO_INFORMATION_AVAILABLE), len);
            }
            break;

    case MENU_ENUM_LABEL_CRT_SWITCH_RESOLUTION: snprintf(s, len, "SET CRT");
      break;

    case MENU_ENUM_LABEL_CRT_SWITCH_RESOLUTION_SUPER: snprintf(s, len, "SET CRT SUPER");
      break;

        case MENU_ENUM_LABEL_VIDEO_SHADER_PRESET:
            snprintf(s, len,
                     "Shader Öne Ayarı yükleyin. \n"
                             " \n"
                             "Doğrudan bir gölgelendirici önayarı yükleyin. \n"
                             "Menü gölgelendirici menüsü buna göre güncellenir. \n"
                             " \n"
                             "CGP basit olmayan ölçeklendirme yöntemleri kullanıyorsa, \n"
                             "(yani kaynak ölçeklendirme, X / Y için aynı ölçeklendirme faktörü), \n"
                             "menüde görüntülenen ölçeklendirme faktörü doğru olmayabilir. \n"
            );
            break;
        case MENU_ENUM_LABEL_VIDEO_SHADER_SCALE_PASS:
            snprintf(s, len,
                     "Bu geçişteki ölçek. \n"
                             " \n"
                             "Ölçek faktörü birikir, yani ilk geçiş \n"
                             "için 2x ve ikinci geçiş için 2x \n"
                             "size toplam 4x ölçek verir. \n"
                             " \n"
                             "Son geçiş için bir ölçek faktörü varsa, \n"
                             "sonuç 'Varsayılan Filtre'de belirtilen \n"
                             "filtre ile ekrana uzatılır. \n"
                             " \n"
                             "'Umurumda Değil' olarak ayarlanmışsa, 1x ölçeği \n"
                             "veya tam ekrana uzat ya da son geçiş \n"
                             "yapılmadığına bağlı olarak tam ekrana geçilir. \n"
            );
            break;
        case MENU_ENUM_LABEL_VIDEO_SHADER_NUM_PASSES:
            snprintf(s, len,
                     "Gölgelendirici Geçişleri. \n"
                             " \n"
                             "RetroArch, çeşitli gölgelendiricileri isteğe \n"
                             "bağlı gölgelendirici geçişleri ileözel donanım filtreleri \n"
                             "özel donanım filtreleri ve ölçek faktörleriyle karıştırmanıza ve eşleştirmenize olanak sağlar. \n"
                             " \n"
                             "Bu seçenek kullanılacak gölgelendirici geçiş \n"
                             "sayısını belirtir. Bunu 0'a ayarlarsanız ve Gölgelendirici Değişiklikleri Uygula'yı \n"
                             "kullanırsanız, 'boş' bir gölgelendirici kullanırsınız. \n"
            );
            break;
        case MENU_ENUM_LABEL_VIDEO_SHADER_PARAMETERS:
            snprintf(s, len,
                     "Gölgelendirici Parametreleri. \n"
                             " \n"
                             "Geçerli gölgelendiriciyi doğrudan değiştirir.\n"
                             "CGP/GLSLP ön ayar dosyasına kaydedilmeyecek");
            break;
        case MENU_ENUM_LABEL_VIDEO_SHADER_PRESET_PARAMETERS:
            snprintf(s, len,
                     "Gölgelendirici Ön Ayar Parametreleri. \n"
                             " \n"
                             "Şu anda menüde gölgelendirici hazır ayarını değiştirir."
            );
            break;
        case MENU_ENUM_LABEL_VIDEO_SHADER_PASS:
            snprintf(s, len,
                     "Gölgelendiricilere giden veri yolu. \n"
                             " \n"
                             "Tüm gölgelendiriciler aynı tipte \n"
                             "olmalıdır (yani CG, GLSL veya HLSL). \n"
                             " \n"
                             "Tarayıcının gölgelendiricileri aramaya \n"
                             "başlayacağı yeri ayarlamak için \n"
                             "Gölgelendirici Dizini'ni ayarlayın. "
            );
            break;
        case MENU_ENUM_LABEL_CONFIGURATION_SETTINGS:
            snprintf(s, len,
                     "Yapılandırma dosyalarının nasıl yüklendiğini \n"
                             "ve önceliklendirildiğini belirler.");
            break;
        case MENU_ENUM_LABEL_CONFIG_SAVE_ON_EXIT:
            snprintf(s, len,
                     "Çıkışta Konfigürasyon dosyasını diske kaydeder.\n"
                             "Useful for menu as settings can be\n"
                             "modified. Overwrites the config.\n"
                             " \n"
                             "#include's and comments are not \n"
                             "preserved. \n"
                             " \n"
                             "By design, the config file is \n"
                             "considered immutable as it is \n"
                             "likely maintained by the user, \n"
                             "and should not be overwritten \n"
                             "behind the user's back."
#if defined(RARCH_CONSOLE) || defined(RARCH_MOBILE)
            "\nThis is not not the case on \n"
            "consoles however, where \n"
            "looking at the config file \n"
            "manually isn't really an option."
#endif
            );
            break;
        case MENU_ENUM_LABEL_CONFIRM_ON_EXIT:
            snprintf(s, len, "Çıkmak istediğinden emin misin?");
            break;
        case MENU_ENUM_LABEL_SHOW_HIDDEN_FILES:
            snprintf(s, len, "Gizli dosya ve \n"
                    "klasörleri göster.");
            break;
        case MENU_ENUM_LABEL_VIDEO_SHADER_FILTER_PASS:
            snprintf(s, len,
                     "Bu geçiş için donanım filtresi. \n"
                             " \n"
                             "'Umurumda Değil' olarak ayarlanmışsa, \n"
                             "'Varsayılan Filtre' kullanılacaktır. "
            );
            break;
        case MENU_ENUM_LABEL_AUTOSAVE_INTERVAL:
            snprintf(s, len,
                     "Autosaves the non-volatile SRAM \n"
                             "at a regular interval.\n"
                             " \n"
                             "This is disabled by default unless set \n"
                             "otherwise. The interval is measured in \n"
                             "seconds. \n"
                             " \n"
                             "A value of 0 disables autosave.");
            break;
        case MENU_ENUM_LABEL_INPUT_BIND_DEVICE_TYPE:
            snprintf(s, len,
                     "Input Device Type. \n"
                             " \n"
                             "Picks which device type to use. This is \n"
                             "relevant for the libretro core itself."
            );
            break;
        case MENU_ENUM_LABEL_LIBRETRO_LOG_LEVEL:
            snprintf(s, len,
                     "Sets log level for libretro cores \n"
                             "(GET_LOG_INTERFACE). \n"
                             " \n"
                             " If a log level issued by a libretro \n"
                             " core is below libretro_log level, it \n"
                             " is ignored.\n"
                             " \n"
                             " DEBUG logs are always ignored unless \n"
                             " verbose mode is activated (--verbose).\n"
                             " \n"
                             " DEBUG = 0\n"
                             " INFO  = 1\n"
                             " WARN  = 2\n"
                             " ERROR = 3"
            );
            break;
        case MENU_ENUM_LABEL_STATE_SLOT_INCREASE:
        case MENU_ENUM_LABEL_STATE_SLOT_DECREASE:
            snprintf(s, len,
                     "Konum slotları.\n"
                             " \n"
                             " With slot set to 0, save state name is *.state \n"
                             " (or whatever defined on commandline).\n"
                             "When slot is != 0, path will be (path)(d), \n"
                             "where (d) is slot number.");
            break;
        case MENU_ENUM_LABEL_SHADER_APPLY_CHANGES:
            snprintf(s, len,
                     "Gölgelendirici Değişikliklerini Uygular. \n"
                             " \n"
                             "Gölgelendirici ayarlarını değiştirdikten sonra, \n"
                             "değişiklikleri uygulamak için bunu kullanın. \n"
                             " \n"
                             "Gölgelendirici ayarlarının değiştirilmesi biraz pahalı bir işlemdir, \n"
                             "bu nedenle açıkça yapılması gerekir. \n"
                             " \n"
                             "Gölgelendirici uyguladığınızda, menü gölgelendirici \n"
                             "ayarları geçici bir dosyaya kaydedilir (menu.cgp veya menu.glslp) \n"
                             "ve yüklenir. RetroArch çıktıktan sonra işlem devam eder. \n"
                             "Dosya Gölgelendirici Dizinine kaydedilir."
            );
            break;
        case MENU_ENUM_LABEL_SHADER_WATCH_FOR_CHANGES:
            snprintf(s, len,
                     "Watch shader files for new changes. \n"
                     " \n"
                     "After saving changes to a shader on disk, \n"
                     "it will automatically be recompiled \n"
                     "and applied to the running content."
            );
            break;
        case MENU_ENUM_LABEL_MENU_TOGGLE:
            snprintf(s, len,
                     "Toggles menu.");
            break;
        case MENU_ENUM_LABEL_GRAB_MOUSE_TOGGLE:
            snprintf(s, len,
                     "Toggles mouse grab.\n"
                             " \n"
                             "When mouse is grabbed, RetroArch hides the \n"
                             "mouse, and keeps the mouse pointer inside \n"
                             "the window to allow relative mouse input to \n"
                             "work better.");
            break;
        case MENU_ENUM_LABEL_GAME_FOCUS_TOGGLE:
            snprintf(s, len,
                     "Toggles game focus.\n"
                             " \n"
                             "When a game has focus, RetroArch will both disable \n"
                             "hotkeys and keep/warp the mouse pointer inside the window.");
            break;
        case MENU_ENUM_LABEL_DISK_NEXT:
            snprintf(s, len,
                     "Disk görüntüleri arasında geçiş yapar.\n"
                             "Diski çıkardıktan sonra kullanın. \n"
                             " \n"
                             "Çıkarmayı tekrar değiştirerek tamamlayın.");
            break;
        case MENU_ENUM_LABEL_VIDEO_FILTER:
#ifdef HAVE_FILTERS_BUILTIN
            snprintf(s, len,
                  "CPU tabanlı video filtresi.");
#else
            snprintf(s, len,
                     "CPU tabanlı video filtresi\n"
                             " \n"
                             "Path to a dynamic library.");
#endif
            break;
        case MENU_ENUM_LABEL_AUDIO_DEVICE:
            snprintf(s, len,
                     "Override the default audio device \n"
                             "the audio driver uses.\n"
                             "This is driver dependent. E.g.\n"
#ifdef HAVE_ALSA
            " \n"
            "ALSA için PCM cihazı gerek."
#endif
#ifdef HAVE_OSS
            " \n"
            "OSS wants a path (e.g. /dev/dsp)."
#endif
#ifdef HAVE_JACK
            " \n"
            "JACK wants portnames (e.g. system:playback1\n"
            ",system:playback_2)."
#endif
#ifdef HAVE_RSOUND
            " \n"
            "RSound wants an IP address to an RSound \n"
            "server."
#endif
            );
            break;
        case MENU_ENUM_LABEL_DISK_EJECT_TOGGLE:
            snprintf(s, len,
                     "Diskler için çıkarmayı değiştirir.\n"
                             " \n"
                             "Birden fazla disk içeriği için kullanılır.");
            break;
        case MENU_ENUM_LABEL_ENABLE_HOTKEY:
            snprintf(s, len,
                     "Diğer kısayol tuşlarını etkinleştirin.\n"
                             " \n"
                             " If this hotkey is bound to either keyboard, \n"
                             "joybutton or joyaxis, all other hotkeys will \n"
                             "be disabled unless this hotkey is also held \n"
                             "at the same time. \n"
                             " \n"
                             "This is useful for RETRO_KEYBOARD centric \n"
                             "implementations which query a large area of \n"
                             "the keyboard, where it is not desirable that \n"
                             "hotkeys get in the way.");
            break;
        case MENU_ENUM_LABEL_REWIND_ENABLE:
            snprintf(s, len,
                     "Geri sarmayı etkinleştir.\n"
                             " \n"
                             "Performans düşmesi olacaktır, \n"
                             "bu nedenle varsayılan olarak devre dışıdır.");
            break;
        case MENU_ENUM_LABEL_CHEAT_APPLY_AFTER_TOGGLE:
            snprintf(s, len,
                     "Geçiş yaptıktan hemen sonra hileyi uygulayın.");
            break;
        case MENU_ENUM_LABEL_CHEAT_APPLY_AFTER_LOAD:
            snprintf(s, len,
                     "Oyun yüklendiğinde hileleri otomatik uygulayın.");
            break;
        case MENU_ENUM_LABEL_LIBRETRO_DIR_PATH:
            snprintf(s, len,
                     "Core Dizini. \n"
                             " \n"
                             "Libretro Core uygulamalarının \n"
                             "aranacağı dizin. ");
            break;
        case MENU_ENUM_LABEL_VIDEO_REFRESH_RATE_AUTO:
            snprintf(s, len,
                     "Otomatik Yenileme Hızı\n"
                             " \n"
                             "Monitörünüzün doğru yenileme hızı (Hz).\n"
                             "Bu formül, ses giriş hızını hesaplamak \n"
                             "için kullanılır: \n"
                             " \n"
                             "audio_input_rate = oyun giriş hızı * \n"
                             "ekran yenileme hızı/oyun yenileme hızı \n"
                             " \n"
                             "Uygulamada herhangi bir değer rapor edilmezse, \n"
                             "uyumluluk için NTSC varsayılanları kabul edilir. \n"
                             " \n"
                             "Geniş görüntü değişikliklerinden kaçınmak için bu değer 60Hz'ye yakın olmalıdır. \n"
                             "Monitörünüz 60Hz'de çalışmıyorsa, VSync'yi devre dışı bırakın \n");
            break;
        case MENU_ENUM_LABEL_VIDEO_REFRESH_RATE_POLLED:
            snprintf(s, len,
                     "Set Polled Refresh Rate\n"
                             " \n"
                            "Sets the refresh rate to the actual value\n"
                            "polled from the display driver.");
            break;
        case MENU_ENUM_LABEL_VIDEO_ROTATION:
            snprintf(s, len,
                     "Forces a certain rotation \n"
                             "of the screen.\n"
                             " \n"
                             "The rotation is added to rotations which\n"
                             "the libretro core sets (see Video Allow\n"
                             "Rotate).");
            break;
        case MENU_ENUM_LABEL_VIDEO_SCALE:
            snprintf(s, len,
                     "Tam ekran çözünürlüğü.\n"
                             " \n"
                             "0 çözünürlüğü, \n"
                             "ortamın çözünürlüğünü kullanır.\n");
            break;
        case MENU_ENUM_LABEL_FASTFORWARD_RATIO:
            snprintf(s, len,
                     "İleri Sarma Oranı.\n"
                             " \n"
                             "The maximum rate at which content will\n"
                             "be run when using fast forward.\n"
                             " \n"
                             " (E.g. 5.0 for 60 fps content => 300 fps \n"
                             "cap).\n"
                             " \n"
                             "RetroArch will go to sleep to ensure that \n"
                             "the maximum rate will not be exceeded.\n"
                             "Do not rely on this cap to be perfectly \n"
                             "accurate.");
            break;
        case MENU_ENUM_LABEL_VRR_RUNLOOP_ENABLE:
            snprintf(s, len,
                     "Sync to Exact Content Framerate.\n"
                             " \n"
                             "This option is the equivalent of forcing x1 speed\n"
                             "while still allowing fast forward.\n"
                             "No deviation from the core requested refresh rate,\n"
                             "no sound Dynamic Rate Control).");
            break;
        case MENU_ENUM_LABEL_VIDEO_MONITOR_INDEX:
            snprintf(s, len,
                     "Tercih edilecek monitor.\n"
                             " \n"
                             "0 (varsayılan), belirli bir monitörün \n"
                             "tercih edilmediği anlamına gelir; 1 ve \n"
                             "üstü (1, ilk monitördür), RetroArch'ın \n"
                             "belirli monitörü kullanmasını önerir.");
            break;
        case MENU_ENUM_LABEL_VIDEO_CROP_OVERSCAN:
            snprintf(s, len,
                     "Forces cropping of overscanned \n"
                             "frames.\n"
                             " \n"
                             "Exact behavior of this option is \n"
                             "core-implementation specific.");
            break;
        case MENU_ENUM_LABEL_VIDEO_SCALE_INTEGER:
            snprintf(s, len,
                     "Only scales video in integer \n"
                             "steps.\n"
                             " \n"
                             "The base size depends on system-reported \n"
                             "geometry and aspect ratio.\n"
                             " \n"
                             "If Force Aspect is not set, X/Y will be \n"
                             "integer scaled independently.");
            break;
        case MENU_ENUM_LABEL_AUDIO_VOLUME:
            snprintf(s, len,
                     "Audio volume, expressed in dB.\n"
                             " \n"
                             " 0 dB is normal volume. No gain will be applied.\n"
                             "Gain can be controlled in runtime with Input\n"
                             "Volume Up / Input Volume Down.");
            break;
        case MENU_ENUM_LABEL_AUDIO_RATE_CONTROL_DELTA:
            snprintf(s, len,
                     "Ses hızı kontrolü.\n"
                             " \n"
                             "Bunu 0'a ayarlamak hız kontrolünü devre dışı bırakır.\n"
                             "Any other value controls audio rate control \n"
                             "delta.\n"
                             " \n"
                             "Defines how much input rate can be adjusted \n"
                             "dynamically.\n"
                             " \n"
                             " Giriş hızı şöyle tanımlanır: \n"
                             " Giriş hızı * (1.0 +/- (rate control delta))");
            break;
        case MENU_ENUM_LABEL_AUDIO_MAX_TIMING_SKEW:
            snprintf(s, len,
                     "Maksimum ses çarpıklığı zamanlaması.\n"
                             " \n"
                             "Giriş hızındaki maksimum değişikliği tanımlar.\n"
                             "Yanlış zamanlamada, örneğin NTSC ekranlarda PAL Core'larını\n"
                             "çalıştırmak gibi, zamanlamada çok büyük \n"
                             "değişiklikler yapmak için bunu artırmak isteyebilirsiniz.\n"
                             " \n"
                             " Giriş hızı şöyle tanımlanır: \n"
                             " Giriş hızı * (1.0 +/- (maksimum zamanlama çarpıklığı))");
            break;
        case MENU_ENUM_LABEL_OVERLAY_NEXT:
            snprintf(s, len,
                     "Toggles to next overlay.\n"
                             " \n"
                             "Wraps around.");
            break;
        case MENU_ENUM_LABEL_LOG_VERBOSITY:
            snprintf(s, len,
                     "Enable or disable verbosity level \n"
                             "of frontend.");
            break;
        case MENU_ENUM_LABEL_VOLUME_UP:
            snprintf(s, len,
                     "Ses seviyesini arttırır.");
            break;
        case MENU_ENUM_LABEL_VOLUME_DOWN:
            snprintf(s, len,
                     "Ses seviyesini azaltır.");
            break;
        case MENU_ENUM_LABEL_VIDEO_DISABLE_COMPOSITION:
            snprintf(s, len,
                     "Forcibly disable composition.\n"
                             "Only valid on Windows Vista/7 for now.");
            break;
        case MENU_ENUM_LABEL_PERFCNT_ENABLE:
            snprintf(s, len,
                     "Enable or disable frontend \n"
                             "performance counters.");
            break;
        case MENU_ENUM_LABEL_SYSTEM_DIRECTORY:
            snprintf(s, len,
                     "Sistem Dizini. \n"
                             " \n"
                             "Sets the 'system' directory.\n"
                             "Cores can query for this\n"
                             "directory to load BIOSes, \n"
                             "system-specific configs, etc.");
            break;
        case MENU_ENUM_LABEL_SAVESTATE_AUTO_SAVE:
        case MENU_ENUM_LABEL_SAVESTATE_AUTO_LOAD:
            snprintf(s, len,
                     "Automatically saves a savestate at the \n"
                             "end of RetroArch's lifetime.\n"
                             " \n"
                             "RetroArch will automatically load any savestate\n"
                             "with this path on startup if 'Auto Load State\n"
                             "is enabled.");
            break;
        case MENU_ENUM_LABEL_VIDEO_THREADED:
            snprintf(s, len,
                     "Use threaded video driver.\n"
                             " \n"
                             "Using this might improve performance at the \n"
                             "possible cost of latency and more video \n"
                             "stuttering.");
            break;
        case MENU_ENUM_LABEL_VIDEO_VSYNC:
            snprintf(s, len,
                     "Video V-Sync.\n");
            break;
        case MENU_ENUM_LABEL_VIDEO_HARD_SYNC:
            snprintf(s, len,
                     "CPU ve GPU'yu sabit senkronize \n"
                             "etmeye çalışır. \n"
                             " \n"
                             "Performans karşılığında gecikmeyi \n"
                             "azaltır.");
            break;
        case MENU_ENUM_LABEL_REWIND_GRANULARITY:
            snprintf(s, len,
                     "Rewind granularity.\n"
                             " \n"
                             " When rewinding defined number of \n"
                             "frames, you can rewind several frames \n"
                             "at a time, increasing the rewinding \n"
                             "speed.");
            break;
        case MENU_ENUM_LABEL_REWIND_BUFFER_SIZE:
            snprintf(s, len,
                     "Rewind buffer size (MB).\n"
                             " \n"
                             " The amount of memory in MB to reserve \n"
                             "for rewinding.  Increasing this value \n"
                             "increases the rewind history length.\n");
            break;
        case MENU_ENUM_LABEL_REWIND_BUFFER_SIZE_STEP:
            snprintf(s, len,
                     "Rewind buffer size step (MB).\n"
                             " \n"
                             " Each time you increase or decrease \n"
                             "the rewind buffer size value via this \n"
                             "UI it will change by this amount.\n");
            break;
        case MENU_ENUM_LABEL_SCREENSHOT:
            snprintf(s, len,
                     "Ekran görüntüsü al.");
            break;
        case MENU_ENUM_LABEL_VIDEO_FRAME_DELAY:
            snprintf(s, len,
                     "Sets how many milliseconds to delay\n"
                             "after VSync before running the core.\n"
                             "\n"
                             "Can reduce latency at the cost of\n"
                             "higher risk of stuttering.\n"
                             " \n"
                             "Maximum is 15.");
            break;
        case MENU_ENUM_LABEL_VIDEO_HARD_SYNC_FRAMES:
            snprintf(s, len,
                     "Sets how many frames CPU can \n"
                             "run ahead of GPU when using 'GPU \n"
                             "Hard Sync'.\n"
                             " \n"
                             "Maximum is 3.\n"
                             " \n"
                             " 0: Syncs to GPU immediately.\n"
                             " 1: Syncs to previous frame.\n"
                             " 2: Etc ...");
            break;
        case MENU_ENUM_LABEL_VIDEO_BLACK_FRAME_INSERTION:
            snprintf(s, len,
                     "Inserts a black frame inbetween \n"
                             "frames.\n"
                             " \n"
                             "Useful for 120 Hz monitors who want to \n"
                             "play 60 Hz material with eliminated \n"
                             "ghosting.\n"
                             " \n"
                             "Video refresh rate should still be \n"
                             "configured as if it is a 60 Hz monitor \n"
                             "(divide refresh rate by 2).");
            break;
        case MENU_ENUM_LABEL_RGUI_SHOW_START_SCREEN:
            snprintf(s, len,
                     "Show startup screen in menu.\n"
                             "Is automatically set to false when seen\n"
                             "for the first time.\n"
                             " \n"
                             "This is only updated in config if\n"
                             "'Save Configuration on Exit' is enabled.\n");
            break;
        case MENU_ENUM_LABEL_VIDEO_FULLSCREEN:
            snprintf(s, len, "Toggles fullscreen.");
            break;
        case MENU_ENUM_LABEL_BLOCK_SRAM_OVERWRITE:
            snprintf(s, len,
                     "Block SRAM from being overwritten \n"
                             "when loading save states.\n"
                             " \n"
                             "Might potentially lead to buggy games.");
            break;
        case MENU_ENUM_LABEL_PAUSE_NONACTIVE:
            snprintf(s, len,
                     "Pause gameplay when window focus \n"
                             "is lost.");
            break;
        case MENU_ENUM_LABEL_VIDEO_GPU_SCREENSHOT:
            snprintf(s, len,
                     "Screenshots output of GPU shaded \n"
                             "material if available.");
            break;
        case MENU_ENUM_LABEL_SCREENSHOT_DIRECTORY:
            snprintf(s, len,
                     "Ekran görüntüsü Dizini. \n"
                             " \n"
                             "Ekran görüntülerinin bulunacağı dizin."
            );
            break;
        case MENU_ENUM_LABEL_VIDEO_SWAP_INTERVAL:
            snprintf(s, len,
                     "VSync Swap Interval.\n"
                             " \n"
                             "Uses a custom swap interval for VSync. Set this \n"
                             "to effectively halve monitor refresh rate.");
            break;
        case MENU_ENUM_LABEL_SAVEFILE_DIRECTORY:
            snprintf(s, len,
                     "Kayıt dosyaları Dizini. \n"
                             " \n"
                             "Save all save files (*.srm) to this \n"
                             "directory. This includes related files like \n"
                             ".bsv, .rt, .psrm, etc...\n"
                             " \n"
                             "This will be overridden by explicit command line\n"
                             "options.");
            break;
        case MENU_ENUM_LABEL_SAVESTATE_DIRECTORY:
            snprintf(s, len,
                     "Konum kayıtları Dizini. \n"
                             " \n"
                             "Save all save states (*.state) to this \n"
                             "directory.\n"
                             " \n"
                             "This will be overridden by explicit command line\n"
                             "options.");
            break;
        case MENU_ENUM_LABEL_ASSETS_DIRECTORY:
            snprintf(s, len,
                     "İçerikler Dizini. \n"
                             " \n"
                             " This location is queried by default when \n"
                             "menu interfaces try to look for loadable \n"
                             "assets, etc.");
            break;
        case MENU_ENUM_LABEL_DYNAMIC_WALLPAPERS_DIRECTORY:
            snprintf(s, len,
                     "Dinamik Duvar Kağıtları Dizini. \n"
                             " \n"
                             " The place to store backgrounds that will \n"
                             "be loaded dynamically by the menu depending \n"
                             "on context.");
            break;
        case MENU_ENUM_LABEL_SLOWMOTION_RATIO:
            snprintf(s, len,
                     "Slowmotion oranı."
                             " \n"
                             "When slowmotion, content will slow\n"
                             "down by factor.");
            break;
        case MENU_ENUM_LABEL_INPUT_BUTTON_AXIS_THRESHOLD:
            snprintf(s, len,
                     "Defines the axis threshold.\n"
                             " \n"
                             "How far an axis must be tilted to result\n"
                             "in a button press.\n"
                             " Possible values are [0.0, 1.0].");
            break;
        case MENU_ENUM_LABEL_INPUT_TURBO_PERIOD:
            snprintf(s, len,
                     "Turbo period.\n"
                             " \n"
                             "Describes the period of which turbo-enabled\n"
                             "buttons toggle.\n"
                             " \n"
                             "Numbers are described in frames."
            );
            break;
        case MENU_ENUM_LABEL_INPUT_DUTY_CYCLE:
            snprintf(s, len,
                     "Duty cycle.\n"
                             " \n"
                             "Describes how long the period of a turbo-enabled\n"
                             "should be.\n"
                             " \n"
                             "Numbers are described in frames."
            );
            break;
        case MENU_ENUM_LABEL_INPUT_TOUCH_ENABLE:
            snprintf(s, len, "Dokunma desteğini etkinleştirin.");
            break;
        case MENU_ENUM_LABEL_INPUT_PREFER_FRONT_TOUCH:
            snprintf(s, len, "Geri dokunma yerine önü kullanın.");
            break;
        case MENU_ENUM_LABEL_MOUSE_ENABLE:
            snprintf(s, len, "Menü içinde fare girişini etkinleştirin.");
            break;
        case MENU_ENUM_LABEL_POINTER_ENABLE:
            snprintf(s, len, "Menü içinde dokunmatik girişi etkinleştirin.");
            break;
        case MENU_ENUM_LABEL_MENU_WALLPAPER:
            snprintf(s, len, "Arka plan olarak ayarlamak için resmin yolu.");
            break;
        case MENU_ENUM_LABEL_NAVIGATION_WRAPAROUND:
            snprintf(s, len,
                     "Wrap-around to beginning and/or end \n"
                             "if boundary of list is reached \n"
                             "horizontally and/or vertically.");
            break;
        case MENU_ENUM_LABEL_PAUSE_LIBRETRO:
            snprintf(s, len,
                     "If disabled, the game will keep \n"
                             "running in the background when we are in the \n"
                             "menu.");
            break;
        case MENU_ENUM_LABEL_SUSPEND_SCREENSAVER_ENABLE:
            snprintf(s, len,
                     "Ekran koruyucuyu önler. Is a hint that \n"
                             "does not necessarily have to be \n"
                             "honored by the video driver.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_MODE:
            snprintf(s, len,
                     "Netplay client mode for the current user. \n"
                             "Will be 'Server' mode if disabled.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_DELAY_FRAMES:
            snprintf(s, len,
                     "The amount of delay frames to use for netplay. \n"
                             " \n"
                             "Increasing this value will increase \n"
                             "performance, but introduce more latency.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_PUBLIC_ANNOUNCE:
            snprintf(s, len,
                     "Netplay oyunlarının kamuya duyurulup duyulmayacağı. \n"
                             " \n"
                             "False olarak ayarlanırsa, istemciler genel \n"
                             "lobiyi kullanmak yerine manuel olarak bağlanmalıdır.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_START_AS_SPECTATOR:
            snprintf(s, len,
                     "Whether to start netplay in spectator mode. \n"
                             " \n"
                             "If set to true, netplay will be in spectator mode \n"
                             "on start. It's always possible to change mode \n"
                             "later.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_ALLOW_SLAVES:
            snprintf(s, len,
                     "Whether to allow connections in slave mode. \n"
                             " \n"
                             "Slave-mode clients require very little processing \n"
                             "power on either side, but will suffer \n"
                             "significantly from network latency.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_REQUIRE_SLAVES:
            snprintf(s, len,
                     "Whether to disallow connections not in slave mode. \n"
                             " \n"
                             "Not recommended except for very fast networks \n"
                             "with very weak machines. \n");
            break;
        case MENU_ENUM_LABEL_NETPLAY_STATELESS_MODE:
            snprintf(s, len,
                     "Whether to run netplay in a mode not requiring\n"
                             "save states. \n"
                             " \n"
                             "If set to true, a very fast network is required,\n"
                             "but no rewinding is performed, so there will be\n"
                             "no netplay jitter.\n");
            break;
        case MENU_ENUM_LABEL_NETPLAY_CHECK_FRAMES:
            snprintf(s, len,
                     "The frequency in frames with which netplay \n"
                             "will verify that the host and client are in \n"
                             "sync. \n"
                             " \n"
                             "With most cores, this value will have no \n"
                             "visible effect and can be ignored. With \n"
                             "nondeterminstic cores, this value determines \n"
                             "how often the netplay peers will be brought \n"
                             "into sync. With buggy cores, setting this \n"
                             "to any non-zero value will cause severe \n"
                             "performance issues. Set to zero to perform \n"
                             "no checks. This value is only used on the \n"
                             "netplay host. \n");
            break;
        case MENU_ENUM_LABEL_NETPLAY_INPUT_LATENCY_FRAMES_MIN:
            snprintf(s, len,
                     "The number of frames of input latency for \n"
                     "netplay to use to hide network latency. \n"
                     " \n"
                     "When in netplay, this option delays local \n"
                     "input, so that the frame being run is \n"
                     "closer to the frames being received from \n"
                     "the network. This reduces jitter and makes \n"
                     "netplay less CPU-intensive, but at the \n"
                     "price of noticeable input lag. \n");
            break;
        case MENU_ENUM_LABEL_NETPLAY_INPUT_LATENCY_FRAMES_RANGE:
            snprintf(s, len,
                     "The range of frames of input latency that \n"
                     "may be used by netplay to hide network \n"
                     "latency. \n"
                     "\n"
                     "If set, netplay will adjust the number of \n"
                     "frames of input latency dynamically to \n"
                     "balance CPU time, input latency and \n"
                     "network latency. This reduces jitter and \n"
                     "makes netplay less CPU-intensive, but at \n"
                     "the price of unpredictable input lag. \n");
            break;
        case MENU_ENUM_LABEL_NETPLAY_NAT_TRAVERSAL:
            snprintf(s, len,
                     "When hosting, attempt to listen for\n"
                             "connections from the public internet, using\n"
                             "UPnP or similar technologies to escape LANs. \n");
            break;
        case MENU_ENUM_LABEL_NETPLAY_USE_MITM_SERVER:
            snprintf(s, len,
                     "When hosting a netplay session, relay connection through a \n"
                             "man-in-the-middle server \n"
                             "to get around firewalls or NAT/UPnP issues. \n");
            break;
        case MENU_ENUM_LABEL_NETPLAY_MITM_SERVER:
            snprintf(s, len,
                     "Specifies the man-in-the-middle server \n"
                             "to use for netplay. A server that is \n"
                             "located closer to you may have less latency. \n");
            break;
        case MENU_ENUM_LABEL_VIDEO_MAX_SWAPCHAIN_IMAGES:
            snprintf(s, len,
                     "Maximum amount of swapchain images. This \n"
                             "can tell the video driver to use a specific \n"
                             "video buffering mode. \n"
                             " \n"
                             "Single buffering - 1\n"
                             "Double buffering - 2\n"
                             "Triple buffering - 3\n"
                             " \n"
                             "Setting the right buffering mode can have \n"
                             "a big impact on latency.");
            break;
        case MENU_ENUM_LABEL_VIDEO_SMOOTH:
            snprintf(s, len,
                     "Resmi bilinear filtreleme ile pürüzsüzleştirir. \n"
                             "Gölgelendiriciler kullanılıyorsa devre dışı bırakılmalıdır.");
            break;
        case MENU_ENUM_LABEL_TIMEDATE_ENABLE:
            snprintf(s, len,
                     "Menü içindeki geçerli tarihi ve/veya saati gösterir.");
            break;
        case MENU_ENUM_LABEL_TIMEDATE_STYLE:
           snprintf(s, len,
              "İçinde geçerli tarih ve/veya saati gösterecek stil.");
           break;
        case MENU_ENUM_LABEL_BATTERY_LEVEL_ENABLE:
            snprintf(s, len,
                     "Menü içindeki geçerli pil seviyesini gösterir.");
            break;
        case MENU_ENUM_LABEL_CORE_ENABLE:
            snprintf(s, len,
                     "Menü içindeki geçerli Core'u gösterir.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_ENABLE_HOST:
            snprintf(s, len,
                     "Netplay'i ana bilgisayar (sunucu) modunda etkinleştirir.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_ENABLE_CLIENT:
            snprintf(s, len,
                     "Netplay'ü istemci modunda etkinleştirir.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_DISCONNECT:
            snprintf(s, len,
                     "Aktif bir Netplay bağlantısını keser.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_LAN_SCAN_SETTINGS:
            snprintf(s, len,
                     "Yerel ağdaki Netplay ana bilgisayarlarını arayın ve bağlanın.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_SETTINGS:
            snprintf(s, len,
                     "Netplay ile ilgili ayar.");
            break;
        case MENU_ENUM_LABEL_DYNAMIC_WALLPAPER:
            snprintf(s, len,
                     "Dynamically load a new background \n"
                             "depending on context.");
            break;
        case MENU_ENUM_LABEL_CORE_UPDATER_BUILDBOT_URL:
            snprintf(s, len,
                     "URL to core updater directory on the \n"
                             "Libretro buildbot.");
            break;
        case MENU_ENUM_LABEL_BUILDBOT_ASSETS_URL:
            snprintf(s, len,
                     "URL to assets updater directory on the \n"
                             "Libretro buildbot.");
            break;
        case MENU_ENUM_LABEL_INPUT_REMAP_BINDS_ENABLE:
            snprintf(s, len,
                     "if enabled, overrides the input binds \n"
                             "with the remapped binds set for the \n"
                             "current core.");
            break;
        case MENU_ENUM_LABEL_OVERLAY_DIRECTORY:
            snprintf(s, len,
                     "Kaplama Dizini. \n"
                             " \n"
                             "Kolay erişim için kaplamaların \n"
                             "tutulduğu bir dizini tanımlar.");
            break;
        case MENU_ENUM_LABEL_INPUT_MAX_USERS:
            snprintf(s, len,
                     "RetroArch tarafından desteklenen maksimum \n"
                             "kullanıcı sayısı.");
            break;
        case MENU_ENUM_LABEL_CORE_UPDATER_AUTO_EXTRACT_ARCHIVE:
            snprintf(s, len,
                     "İndirdikten sonra, indirme işlemlerinin \n"
                             "içinde bulunduğu arşivleri otomatik \n"
                             "olarak çıkarır.");
            break;
        case MENU_ENUM_LABEL_NAVIGATION_BROWSER_FILTER_SUPPORTED_EXTENSIONS_ENABLE:
            snprintf(s, len,
                     "Filter files being shown by \n"
                             "supported extensions.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_NICKNAME:
            snprintf(s, len,
                     "The username of the person running RetroArch. \n"
                             "This will be used for playing online games.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_TCP_UDP_PORT:
            snprintf(s, len,
                     "The port of the host IP address. \n"
                             "Can be either a TCP or UDP port.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_SPECTATOR_MODE_ENABLE:
            snprintf(s, len,
                     "Enable or disable spectator mode for \n"
                             "the user during netplay.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_IP_ADDRESS:
            snprintf(s, len,
                     "The address of the host to connect to.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_PASSWORD:
            snprintf(s, len,
                     "The password for connecting to the netplay \n"
                             "host. Used only in host mode.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_SPECTATE_PASSWORD:
            snprintf(s, len,
                     "The password for connecting to the netplay \n"
                             "host with only spectator privileges. Used \n"
                             "only in host mode.");
            break;
        case MENU_ENUM_LABEL_STDIN_CMD_ENABLE:
            snprintf(s, len,
                     "Stdin komut arayüzünü etkinleştirin.");
            break;
        case MENU_ENUM_LABEL_UI_COMPANION_START_ON_BOOT:
            snprintf(s, len,
                     "Kullanıcı Arabirimi yardımcı sürücüsünü başlat \n"
                             "boot sırasında (varsa).");
            break;
        case MENU_ENUM_LABEL_MENU_DRIVER:
            snprintf(s, len, "Menu driver to use.");
            break;
        case MENU_ENUM_LABEL_INPUT_MENU_ENUM_TOGGLE_GAMEPAD_COMBO:
            snprintf(s, len,
                     "Geçiş menüsüne Gamepad düğme kombinasyonu. \n"
                             " \n"
                             "0 - Boş \n"
                             "1 - L + R + Y + D-Pad Down \n"
                             "aynı anda basın. \n"
                             "2 - L3 + R3 aynı anda basın. \n"
                             "3 - Start + Select aynı anda basın.");
            break;
        case MENU_ENUM_LABEL_INPUT_ALL_USERS_CONTROL_MENU:
            snprintf(s, len, "Herhangi bir kullanıcının menüyü kontrol etmesine izin verir. \n"
                    " \n"
                    "Devre dışı bırakıldığında, sadece kullanıcı 1 menüyü kontrol edebilir.");
            break;
        case MENU_ENUM_LABEL_INPUT_AUTODETECT_ENABLE:
            snprintf(s, len,
                     "Enable input auto-detection.\n"
                             " \n"
                             "Will attempt to auto-configure \n"
                             "joypads, Plug-and-Play style.");
            break;
        case MENU_ENUM_LABEL_CAMERA_ALLOW:
            snprintf(s, len,
                     "Kameranın Core tarafından erişimine izin ver \n"
                             "veya verme.");
            break;
        case MENU_ENUM_LABEL_LOCATION_ALLOW:
            snprintf(s, len,
                     "Konum servislerine izin ver veya verme \n"
                             "Corelar tarafından erişilir.");
            break;
        case MENU_ENUM_LABEL_TURBO:
            snprintf(s, len,
                     "Turbo enable.\n"
                             " \n"
                             "Holding the turbo while pressing another \n"
                             "button will let the button enter a turbo \n"
                             "mode where the button state is modulated \n"
                             "with a periodic signal. \n"
                             " \n"
                             "The modulation stops when the button \n"
                             "itself (not turbo button) is released.");
            break;
        case MENU_ENUM_LABEL_OSK_ENABLE:
            snprintf(s, len,
                     "Ekran klavyesini etkinleştir/devre dışı bırak.");
            break;
        case MENU_ENUM_LABEL_AUDIO_MUTE:
            snprintf(s, len,
                     "Sesi kapat/aç.");
            break;
        case MENU_ENUM_LABEL_REWIND:
            snprintf(s, len,
                     "Geri sarmak için düğmeyi basılı tutun.\n"
                             " \n"
                             "Geri sarma etkin olmalı.");
            break;
        case MENU_ENUM_LABEL_EXIT_EMULATOR:
            snprintf(s, len,
                     "RetroArch'tan temiz bir şekilde çıkmak için tuş."
#if !defined(RARCH_MOBILE) && !defined(RARCH_CONSOLE)
                            "\nKilling it in any hard way (SIGKILL, \n"
                            "etc) will terminate without saving\n"
                            "RAM, etc. On Unix-likes,\n"
                            "SIGINT/SIGTERM allows\n"
                            "a clean deinitialization."
#endif
            );
            break;
        case MENU_ENUM_LABEL_LOAD_STATE:
            snprintf(s, len,
                     "Konumu yükle.");
            break;
        case MENU_ENUM_LABEL_SAVE_STATE:
            snprintf(s, len,
                     "Konumu kaydet.");
            break;
        case MENU_ENUM_LABEL_NETPLAY_GAME_WATCH:
            snprintf(s, len,
                     "Netplay toggle play/spectate mode.");
            break;
        case MENU_ENUM_LABEL_CHEAT_INDEX_PLUS:
            snprintf(s, len,
                     "Increment cheat index.\n");
            break;
        case MENU_ENUM_LABEL_CHEAT_INDEX_MINUS:
            snprintf(s, len,
                     "Decrement cheat index.\n");
            break;
        case MENU_ENUM_LABEL_SHADER_PREV:
            snprintf(s, len,
                     "Applies previous shader in directory.");
            break;
        case MENU_ENUM_LABEL_SHADER_NEXT:
            snprintf(s, len,
                     "Dizindeki bir sonraki gölgelendiriciyi uygular.");
            break;
        case MENU_ENUM_LABEL_RESET:
            snprintf(s, len,
                     "İçeriği sıfırla.\n");
            break;
        case MENU_ENUM_LABEL_PAUSE_TOGGLE:
            snprintf(s, len,
                     "Toggle between paused and non-paused state.");
            break;
        case MENU_ENUM_LABEL_CHEAT_TOGGLE:
            snprintf(s, len,
                     "Toggle cheat index.\n");
            break;
        case MENU_ENUM_LABEL_CHEAT_IDX:
            snprintf(s, len,
                     "Index position in list.\n");
            break;
        case MENU_ENUM_LABEL_CHEAT_ADDRESS_BIT_POSITION:
            snprintf(s, len,
                     "Address bitmask when Memory Search Size < 8-bit.\n");
            break;
        case MENU_ENUM_LABEL_CHEAT_REPEAT_COUNT:
            snprintf(s, len,
                     "The number of times the cheat will be applied.\nUse with the other two Iteration options to affect large areas of memory.");
            break;
        case MENU_ENUM_LABEL_CHEAT_REPEAT_ADD_TO_ADDRESS:
            snprintf(s, len,
                     "Her “Yineleme Sayısı” ndan sonra Hafıza Adresi, bu sayı ile “Hafıza Arama Boyutu” ile artacaktır.");
            break;
        case MENU_ENUM_LABEL_CHEAT_REPEAT_ADD_TO_VALUE:
            snprintf(s, len,
                     "Her 'İterasyon Sayısı' ndan sonra, Değer bu miktar kadar artacaktır.");
            break;
        case MENU_ENUM_LABEL_CHEAT_MATCH_IDX:
            snprintf(s, len,
                     "Görüntülenecek eşleşmeyi seçin.");
            break;
        case MENU_ENUM_LABEL_CHEAT_START_OR_CONT:
            snprintf(s, len,
                     "Yeni hileler oluşturmak için belleği tarayın");
            break;
        case MENU_ENUM_LABEL_CHEAT_START_OR_RESTART:
            snprintf(s, len,
                     "Sol/Sağ ile bit-boyut arasında geçiş yapın\n");
            break;
        case MENU_ENUM_LABEL_CHEAT_SEARCH_EXACT:
            snprintf(s, len,
                     "Sol/Sağ ile değerleri değiştirinn");
            break;
        case MENU_ENUM_LABEL_CHEAT_SEARCH_LT:
            snprintf(s, len,
                     " ");
            break;
        case MENU_ENUM_LABEL_CHEAT_SEARCH_GT:
            snprintf(s, len,
                     " ");
            break;
        case MENU_ENUM_LABEL_CHEAT_SEARCH_EQ:
            snprintf(s, len,
                     " ");
            break;
        case MENU_ENUM_LABEL_CHEAT_SEARCH_NEQ:
            snprintf(s, len,
                     " ");
            break;
        case MENU_ENUM_LABEL_CHEAT_SEARCH_EQPLUS:
            snprintf(s, len,
                     "Sol/Sağ ile değerleri değiştirin\n");
            break;
        case MENU_ENUM_LABEL_CHEAT_SEARCH_EQMINUS:
            snprintf(s, len,
                     "Değeri değiştirmek için Sol/Sağ\n");
            break;
        case MENU_ENUM_LABEL_CHEAT_ADD_MATCHES:
            snprintf(s, len,
                     " ");
            break;
        case MENU_ENUM_LABEL_CHEAT_VIEW_MATCHES:
            snprintf(s, len,
                     " ");
            break;
        case MENU_ENUM_LABEL_CHEAT_CREATE_OPTION:
            snprintf(s, len,
                     " ");
            break;
        case MENU_ENUM_LABEL_CHEAT_DELETE_OPTION:
            snprintf(s, len,
                     " ");
            break;
        case MENU_ENUM_LABEL_CHEAT_ADD_NEW_TOP:
            snprintf(s, len,
                     " ");
            break;
        case MENU_ENUM_LABEL_CHEAT_RELOAD_CHEATS:
            snprintf(s, len,
                     " ");
            break;
        case MENU_ENUM_LABEL_CHEAT_ADD_NEW_BOTTOM:
            snprintf(s, len,
                     " ");
            break;
        case MENU_ENUM_LABEL_CHEAT_DELETE_ALL:
            snprintf(s, len,
                     " ");
            break;
        case MENU_ENUM_LABEL_CHEAT_BIG_ENDIAN:
            snprintf(s, len,
                     "Büyük endia   : 258 = 0x0102\n"
                     "Küçük endia : 258 = 0x0201");
            break;
        case MENU_ENUM_LABEL_HOLD_FAST_FORWARD:
            snprintf(s, len,
                     "Hold for fast-forward. Releasing button \n"
                             "disables fast-forward.");
            break;
        case MENU_ENUM_LABEL_SLOWMOTION_HOLD:
            snprintf(s, len,
                     "Slowmotion için basılı tutun");
            break;
        case MENU_ENUM_LABEL_FRAME_ADVANCE:
            snprintf(s, len,
                     "İçerik duraklatıldığında kare ilerlemesi.");
            break;
        case MENU_ENUM_LABEL_BSV_RECORD_TOGGLE:
            snprintf(s, len,
                     "Kayıt yapma arasında geçiş yapmak için");
            break;
        case MENU_ENUM_LABEL_L_X_PLUS:
        case MENU_ENUM_LABEL_L_X_MINUS:
        case MENU_ENUM_LABEL_L_Y_PLUS:
        case MENU_ENUM_LABEL_L_Y_MINUS:
        case MENU_ENUM_LABEL_R_X_PLUS:
        case MENU_ENUM_LABEL_R_X_MINUS:
        case MENU_ENUM_LABEL_R_Y_PLUS:
        case MENU_ENUM_LABEL_R_Y_MINUS:
            snprintf(s, len,
                     "Axis for analog stick (DualShock-esque).\n"
                             " \n"
                             "Bound as usual, however, if a real analog \n"
                             "axis is bound, it can be read as a true analog.\n"
                             " \n"
                             "Positive X axis is right. \n"
                             "Positive Y axis is down.");
            break;
        case MENU_ENUM_LABEL_VALUE_WHAT_IS_A_CORE_DESC:
            snprintf(s, len,
                     "RetroArch kendi başına hiçbir şey yapmaz. \n"
                            " \n"
                            "Bir şeyler yapması için programa \n"
                            "bir program yüklemeniz gerekir.. \n"
                            "\n"
                            "Böylelikle programa 'Libretro Core', \n"
                            "yada kısaca 'core' diyoruz. \n"
                            " \n"
                            "Core yüklemek için 'Core Yükle' \n"
                            "kısmından bir tane seçin.\n"
                            " \n"
#ifdef HAVE_NETWORKING
                    "Coreları birkaç yolla elde edebilirsiniz: \n"
                    "* İndirmek için şöyle\n"
                    "'%s' -> '%s'.\n"
                    "* El ile yapmak için 'Core' klasörüne taşıyın\n"
                    "'%s'.",
                    msg_hash_to_str(MENU_ENUM_LABEL_VALUE_ONLINE_UPDATER),
                    msg_hash_to_str(MENU_ENUM_LABEL_VALUE_CORE_UPDATER_LIST),
                    msg_hash_to_str(MENU_ENUM_LABEL_VALUE_LIBRETRO_DIR_PATH)
#else
                            "You can obtain cores by\n"
                            "manually moving them over to\n"
                            "'%s'.",
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_LIBRETRO_DIR_PATH)
#endif
            );
            break;
        case MENU_ENUM_LABEL_VALUE_HELP_CHANGE_VIRTUAL_GAMEPAD_DESC:
            snprintf(s, len,
                     "You can change the virtual gamepad overlay\n"
                             "by going to '%s' -> '%s'."
                             " \n"
                             "From there you can change the overlay,\n"
                             "change the size and opacity of the buttons, etc.\n"
                             " \n"
                             "NOTE: By default, virtual gamepad overlays are\n"
                             "hidden when in the menu.\n"
                             "If you'd like to change this behavior,\n"
                             "you can set '%s' to false.",
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_SETTINGS),
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_OVERLAY_SETTINGS),
                     msg_hash_to_str(MENU_ENUM_LABEL_VALUE_INPUT_OVERLAY_HIDE_IN_MENU)
            );
            break;
        case MENU_ENUM_LABEL_VALUE_VIDEO_MESSAGE_BGCOLOR_ENABLE:
            snprintf(s, len,
                     "OSD için arka plan rengini etkinleştirir.");
            break;
        case MENU_ENUM_LABEL_VALUE_VIDEO_MESSAGE_BGCOLOR_RED:
            snprintf(s, len,
                     "OSD arka plan renginin kırmızı değerini ayarlar. Geçerli değerler 0 ile 255 arasındadır.");
            break;
        case MENU_ENUM_LABEL_VALUE_VIDEO_MESSAGE_BGCOLOR_GREEN:
            snprintf(s, len,
                     "OSD arka plan renginin yeşil değerini ayarlar. Geçerli değerler 0 ile 255 arasındadır.");
            break;
        case MENU_ENUM_LABEL_VALUE_VIDEO_MESSAGE_BGCOLOR_BLUE:
            snprintf(s, len,
                     "OSD arka plan renginin mavi değerini ayarlar. Geçerli değerler 0 ile 255 arasındadır.");
            break;
        case MENU_ENUM_LABEL_VALUE_VIDEO_MESSAGE_BGCOLOR_OPACITY:
            snprintf(s, len,
                     "OSD arka plan renginin opaklığını ayarlar. Geçerli değerler 0,0 ile 1,0 arasındadır.");
            break;
        case MENU_ENUM_LABEL_VALUE_VIDEO_MESSAGE_COLOR_RED:
            snprintf(s, len,
                     "OSD metin renginin kırmızı değerini ayarlar. Geçerli değerler 0 ile 255 arasındadır.");
            break;
        case MENU_ENUM_LABEL_VALUE_VIDEO_MESSAGE_COLOR_GREEN:
            snprintf(s, len,
                     "OSD metin renginin yeşil değerini ayarlar. Geçerli değerler 0 ile 255 arasındadır.");
            break;
        case MENU_ENUM_LABEL_VALUE_VIDEO_MESSAGE_COLOR_BLUE:
            snprintf(s, len,
                     "OSD metin renginin mavi değerini ayarlar. Geçerli değerler 0 ile 255 arasındadır.");
            break;
        case MENU_ENUM_LABEL_MIDI_DRIVER:
            snprintf(s, len,
                     "Kullanılacak MIDI sürücüsü.");
            break;
        case MENU_ENUM_LABEL_MIDI_INPUT:
            snprintf(s, len,
                     "Sets the input device (driver specific).\n"
                     "When set to \"Off\", MIDI input will be disabled.\n"
                     "Device name can also be typed in.");
            break;
        case MENU_ENUM_LABEL_MIDI_OUTPUT:
            snprintf(s, len,
                     "Çıkış cihazını ayarlar (sürücüye özel).\n"
                     "\"Off\"olarak ayarlandığında, MIDI çıkışı devre dışı bırakılır.\n"
                     "Cihaz adı da yazılabilir.\n"
                     " \n"
                     "When MIDI output is enabled and core and game/app support MIDI output,\n"
                     "some or all sounds (depends on game/app) will be generated by MIDI device.\n"
                     "In case of \"null\" MIDI driver this means that those sounds won't be audible.");
            break;
        case MENU_ENUM_LABEL_MIDI_VOLUME:
            snprintf(s, len,
                     "Çıkış cihazının ana ses seviyesini ayarlar.");
            break;
        default:
            if (string_is_empty(s))
                strlcpy(s, msg_hash_to_str(MENU_ENUM_LABEL_VALUE_NO_INFORMATION_AVAILABLE), len);
            return -1;
    }

    return 0;
}
#endif

#ifdef HAVE_MENU
static const char *menu_hash_to_str_tr_label_enum(enum msg_hash_enums msg)
{
   if (msg <= MENU_ENUM_LABEL_INPUT_HOTKEY_BIND_END &&
         msg >= MENU_ENUM_LABEL_INPUT_HOTKEY_BIND_BEGIN)
   {
      static char hotkey_lbl[128] = {0};
      unsigned idx = msg - MENU_ENUM_LABEL_INPUT_HOTKEY_BIND_BEGIN;
      snprintf(hotkey_lbl, sizeof(hotkey_lbl), "input_hotkey_binds_%d", idx);
      return hotkey_lbl;
   }

   switch (msg)
   {
#include "msg_hash_lbl.h"
      default:
#if 0
         RARCH_LOG("Unimplemented: [%d]\n", msg);
#endif
         break;
   }

   return "null";
}
#endif

const char *msg_hash_to_str_tr(enum msg_hash_enums msg) {
#ifdef HAVE_MENU
    const char *ret = menu_hash_to_str_tr_label_enum(msg);

    if (ret && !string_is_equal(ret, "null"))
       return ret;
#endif

    switch (msg) {
#include "msg_hash_tr.h"
        default:
#if 0
            RARCH_LOG("Unimplemented: [%d]\n", msg);
            {
               RARCH_LOG("[%d] : %s\n", msg - 1, msg_hash_to_str(((enum msg_hash_enums)(msg - 1))));
            }
#endif
            break;
    }

    return "null";
}
