#include "pluginman.h"

#include "imguidock.h"
#include "imguial_log.h"
#include "imguial_fonts.h"

#include <vector>

#include <string/stdstring.h>
#include "../core.h"
#include "../retroarch.h"
#include "../core.h"
#include "../gfx/video_driver.h"
#include "../managers/core_option_manager.h"
#include "../cheevos/cheevos.h"
#include "../content.h"

// Log functions for the plugins

static ImGuiAl::Log      s_debugger_logger;
static debugger_memory_t s_debugger_memory[64];

static void s_debugger_vprintf(enum retro_log_level level, const char* format, va_list args)
{
  ImGuiAl::Log::Level l;

  switch (level)
  {
  case RETRO_LOG_ERROR: l = ImGuiAl::Log::kError; break;
  case RETRO_LOG_WARN:  l = ImGuiAl::Log::kWarn; break;
  case RETRO_LOG_DEBUG: l = ImGuiAl::Log::kDebug; break;
  default:              l = ImGuiAl::Log::kInfo; break;
  }

  s_debugger_logger.VPrintf(l, format, args);
}

static void s_debugger_printf(enum retro_log_level level, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  s_debugger_vprintf(level, format, args);
  va_end(args);
}

static void s_debugger_debug(const char* format, ...)
{
  va_list args;
  va_start(args,format);
  s_debugger_vprintf(RETRO_LOG_DEBUG, format, args);
  va_end(args);
}

static void s_debugger_info(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  s_debugger_vprintf(RETRO_LOG_INFO, format, args);
  va_end(args);
}

static void s_debugger_warn(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  s_debugger_vprintf(RETRO_LOG_WARN, format, args);
  va_end(args);
}

static void s_debugger_error(const char* format, ...)
{
  va_list args;
  va_start(args, format);
  s_debugger_vprintf(RETRO_LOG_ERROR, format, args);
  va_end(args);
}

static const debugger_log_t s_debugger_log =
{
  s_debugger_vprintf,
  s_debugger_printf,
  s_debugger_debug,
  s_debugger_info,
  s_debugger_warn,
  s_debugger_error
};

// RetroArch info functions for the plugins

static int s_debugger_isCoreLoaded()
{
  return core_is_inited();
}

static int s_debugger_isGameLoaded()
{
  return core_is_game_loaded();
}

static const debugger_rarch_info_t s_debugger_rarchInfo =
{
  s_debugger_isCoreLoaded,
  s_debugger_isGameLoaded
};

// Core info functions for the plugins

static void s_debugger_getCoreName(char* name, size_t size)
{
  if (size > 0)
  {
    rarch_system_info_t *system = runloop_get_system_info();

    if (!string_is_empty(system->info.library_name))
    {
      strncpy(name, system->info.library_name, size);
    }
    else
    {
      name[0] = 0;
    }
  }
}

static unsigned s_debugger_getApiVersion()
{
  retro_ctx_api_info_t api;
  core_api_version(&api);
  return api.version;
}

static const struct retro_system_info* s_debugger_getSystemInfo()
{
  rarch_system_info_t* system = runloop_get_system_info();
  return &system->info;
}

static const struct retro_system_av_info* s_debugger_getSystemAVInfo()
{
  return video_viewport_get_system_av_info();
}

static unsigned s_debugger_getRegion()
{
  retro_ctx_region_info_t region;
  core_get_region(&region);
  return region.region;
}

static void* s_debugger_getMemoryData(unsigned id)
{
  retro_ctx_memory_info_t mem;
  mem.id = id;
  core_get_memory(&mem);
  return mem.data;
}

static size_t s_debugger_getMemorySize(unsigned id)
{
  retro_ctx_memory_info_t mem;
  mem.id = id;
  core_get_memory(&mem);
  return mem.size;
}

static unsigned s_debugger_getRotation()
{
  rarch_system_info_t* system = runloop_get_system_info();
  return system->rotation;
}

static unsigned s_debugger_getPerformanceLevel()
{
  rarch_system_info_t* system = runloop_get_system_info();
  return system->performance_level;
}

static enum retro_pixel_format s_debugger_getPixelFormat()
{
  return video_driver_get_pixel_format();
}

static int s_debugger_supportsNoGame()
{
  bool contentless, is_inited;

  content_get_status(&contentless, &is_inited);
  return contentless;
}

static const struct retro_memory_descriptor* s_debugger_getMemoryMap(unsigned index)
{
  rarch_system_info_t* system = runloop_get_system_info();

  if (index < system->mmaps.num_descriptors)
  {
    return &system->mmaps.descriptors[index].core;
  }

  return NULL;
}

static int s_debugger_supportsCheevos(void)
{
#ifdef HAVE_CHEEVOS
  return cheevos_get_support_cheevos();
#else
  return 0;
#endif
}

static unsigned s_debugger_getConsoleId(void)
{
  return cheevos_get_console_id();
}

static uint32_t s_debugger_getCoreId(void)
{
  rarch_system_info_t* system = runloop_get_system_info();
  const char* libname = system->info.library_name;
  uint32_t hash = 5381;

  while (*libname)
  {
    hash = hash * 33 + (uint8_t)*libname++;
  }

  return hash;
}

static debugger_memory_t* s_debugger_getMemoryRegionsFceumm(size_t* count)
{
  rarch_system_info_t* system = runloop_get_system_info();
  unsigned ram_ndx = 0, wram_ndx = 0;
  size_t ram_size = 0, wram_size = 0;

  for (unsigned i = 0; i < system->mmaps.num_descriptors; i++)
  {
    const struct retro_memory_descriptor* desc = &system->mmaps.descriptors[i].core;

    if (desc->start >= 0x0000 && desc->start < 0x0800)
    {
      // RAM
      if (ram_ndx == sizeof(s_debugger_memory[0].parts) / sizeof(s_debugger_memory[0].parts[0]))
      {
        return NULL;
      }

      s_debugger_memory[0].parts[ram_ndx].pointer = (uint8_t*)desc->ptr + desc->offset;
      s_debugger_memory[0].parts[ram_ndx].size = desc->len;
      s_debugger_memory[0].parts[ram_ndx].offset = desc->start;
      ram_ndx++;
      ram_size += desc->len;
    }
    else if (desc->start >= 0x6000 && desc->start < 0x8000)
    {
      // WRAM
      if (wram_ndx == sizeof(s_debugger_memory[1].parts) / sizeof(s_debugger_memory[1].parts[0]))
      {
        return NULL;
      }
      
      s_debugger_memory[1].parts[wram_ndx].pointer = (uint8_t*)desc->ptr + desc->offset;
      s_debugger_memory[1].parts[wram_ndx].size = desc->len;
      s_debugger_memory[1].parts[wram_ndx].offset = desc->start;
      wram_ndx++;
      wram_size += desc->len;
    }
  }

  struct Compare
  {
    static int cmp(const void* e1, const void* e2)
    {
      auto p1 = (const debugger_memory_part_t*)e1;
      auto p2 = (const debugger_memory_part_t*)e2;

      return p1->offset < p2->offset ? -1 : p1->offset > p2->offset ? 1 : 0;
    }
  };

  qsort(s_debugger_memory[0].parts, ram_ndx, sizeof(debugger_memory_part_t), Compare::cmp);
  s_debugger_memory[0].name = "ram";
  s_debugger_memory[0].size = ram_size;
  s_debugger_memory[0].count = ram_ndx;
  s_debugger_memory[0].parts[0].offset = 0;

  for (unsigned i = 1; i < ram_ndx; i++)
  {
    debugger_memory_part_t* part = &s_debugger_memory[0].parts[i];
    part[0].offset = part[-1].offset + part[-1].size;
  }

  qsort(s_debugger_memory[1].parts, wram_ndx, sizeof(debugger_memory_part_t), Compare::cmp);
  s_debugger_memory[1].name = "wram";
  s_debugger_memory[1].size = wram_size;
  s_debugger_memory[1].count = wram_ndx;
  s_debugger_memory[1].parts[0].offset = 0;

  for (unsigned i = 1; i < wram_ndx; i++)
  {
    debugger_memory_part_t* part = &s_debugger_memory[1].parts[i];
    part[0].offset = part[-1].offset + part[-1].size;
  }

  *count = 2;
  return s_debugger_memory;
}

static debugger_memory_t* s_debugger_getMemoryRegions(size_t* count)
{
  *count = 0;

  switch (s_debugger_getCoreId())
  {
  case DEBUGGER_CORE_FCEUMM: return s_debugger_getMemoryRegionsFceumm(count);
  }

  return NULL;
}

static const debugger_core_info_t s_debugger_coreInfo =
{
  s_debugger_getCoreName,
  s_debugger_getApiVersion,
  s_debugger_getSystemInfo,
  s_debugger_getSystemAVInfo,
  s_debugger_getRegion,
  s_debugger_getMemoryData,
  s_debugger_getMemorySize,
  s_debugger_getRotation,
  s_debugger_getPerformanceLevel,
  s_debugger_getPixelFormat,
  s_debugger_supportsNoGame,
  s_debugger_getMemoryMap,
  s_debugger_supportsCheevos,
  s_debugger_getConsoleId,
  s_debugger_getCoreId,
  s_debugger_getMemoryRegions
};

// Plugin interface
const debugger_t s_debugger =
{
  &s_debugger_log,
  &s_debugger_rarchInfo,
  &s_debugger_coreInfo
};

static std::vector<const debugger_plugin_t*> s_debugger_plugins;
static std::vector<std::pair<void*, const debugger_plugin_t*>> s_debugger_running;

static void s_debugger_register_plugin(const debugger_plugin_t* plugin)
{
  s_debugger_plugins.push_back(plugin);
}

void debugger_pluginman_init()
{
  // Setup logger
  static const char* actions[] =
  {
    ICON_FA_FILES_O " Copy",
    ICON_FA_FILE_O " Clear",
    NULL
  };

  if (s_debugger_logger.Init(0, actions))
  {
    s_debugger_logger.SetLabel(ImGuiAl::Log::kDebug, ICON_FA_BUG " Debug");
    s_debugger_logger.SetLabel(ImGuiAl::Log::kInfo, ICON_FA_INFO " Info");
    s_debugger_logger.SetLabel(ImGuiAl::Log::kWarn, ICON_FA_EXCLAMATION_TRIANGLE " Warn");
    s_debugger_logger.SetLabel(ImGuiAl::Log::kError, ICON_FA_BOMB " Error");
    s_debugger_logger.SetCumulativeLabel(ICON_FA_SORT_AMOUNT_DESC " Cumulative");
    s_debugger_logger.SetFilterHeaderLabel(ICON_FA_FILTER " Filters");
    s_debugger_logger.SetFilterLabel(ICON_FA_SEARCH " Filter (inc,-exc)");
  }

  void init_info(debugger_register_plugin_t register_plugin, const debugger_t* info);
  void init_memeditor(debugger_register_plugin_t register_plugin, const debugger_t* info);
  void init_hunter(debugger_register_plugin_t register_plugin, const debugger_t* info);

  static const debugger_init_plugins_t plugins[] =
  {
    init_info,
    init_memeditor,
    init_hunter
  };

  for (int i = 0; i < sizeof(plugins) / sizeof(plugins[0]); i++)
  {
    plugins[i](s_debugger_register_plugin, &s_debugger);
  }
}

void debugger_pluginman_deinit()
{
  for (auto it = s_debugger_running.begin(); it != s_debugger_running.end(); ++it)
  {
    it->second->destroy(it->first, 1);
  }
}

void debugger_pluginman_draw()
{
  if (ImGui::BeginDock(ICON_FA_PLUG " Plugins"))
  {
    for (auto it = s_debugger_plugins.begin(); it != s_debugger_plugins.end(); ++it)
    {
      ImGui::PushID(*it);

      char label[1024];
      snprintf(label, sizeof(label), ICON_FA_PLUS " Create##%p", *it);

      if (ImGui::Button(label))
      {
        void* instance = (*it)->create();

        if (instance != NULL)
        {
          s_debugger_running.push_back(std::pair<void*, const debugger_plugin_t*>(instance, *it));
        }
      }

      ImGui::SameLine();
      ImGui::Text("%s", (*it)->name);
      ImGui::PopID();
    }
  }

  ImGui::EndDock();

  if (ImGui::BeginDock(ICON_FA_COMMENT " Log"))
  {
    s_debugger_logger.Draw();
  }

  ImGui::EndDock();

  for (auto it = s_debugger_running.begin(); it != s_debugger_running.end();)
  {
    ImGui::PushID(it->first);

    char label[1024];
    snprintf(label, sizeof(label), "%s##%p", it->second->name, it->first);

    bool keep = true;

    if (ImGui::BeginDock(label, &keep))
    {
      it->second->draw(it->first);
    }

    ImGui::EndDock();

    if (keep)
    {
      ++it;
    }
    else if (it->second->destroy(it->first, 0))
    {
      it = s_debugger_running.erase(it);
    }

    ImGui::PopID();
  }
}
