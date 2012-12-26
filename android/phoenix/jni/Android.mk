RARCH_VERSION		= "0.9.8-beta3"
LOCAL_PATH := $(call my-dir)
PERF_TEST := 1
HAVE_OPENSL     := 1
HAVE_NEON := 1
HAVE_SINC := 1
HAVE_LOGGER := 1

include $(CLEAR_VARS)

ifeq ($(TARGET_ARCH),arm)
LOCAL_CFLAGS += -DANDROID_ARM -marm
LOCAL_ARM_MODE := arm
endif

ifeq ($(TARGET_ARCH),x86)
LOCAL_CFLAGS += -DANDROID_X86 -DHAVE_SSSE3
endif

ifeq ($(TARGET_ARCH_ABI),armeabi-v7a)

ifeq ($(HAVE_NEON),1)
LOCAL_CFLAGS += -DHAVE_NEON
LOCAL_SRC_FILES += ../../../audio/utils_neon.S.neon
endif

ifeq ($(HAVE_SINC),1)
ifeq ($(HAVE_NEON),1)
LOCAL_SRC_FILES += ../../../audio/sinc_neon.S.neon
endif
LOCAL_CFLAGS += -DHAVE_SINC
endif

LOCAL_CFLAGS += -DANDROID_ARM_V7
endif


ifeq ($(TARGET_ARCH),mips)
LOCAL_CFLAGS += -DANDROID_MIPS -D__mips__ -D__MIPSEL__
endif

LOCAL_MODULE    := retroarch-activity

RARCH_PATH  := ../../..
LIBXML_PATH := ../../../deps/libxml2
LOCAL_SRC_FILES  +=	$(RARCH_PATH)/console/griffin/griffin.c

ifeq ($(HAVE_LOGGER), 1)
LOCAL_CFLAGS += -DHAVE_LOGGER
LOGGER_LDLIBS := -llog
endif

ifeq ($(PERF_TEST), 1)
LOCAL_CFLAGS += -DPERF_TEST
endif

LOCAL_CFLAGS += -Wall -Wno-unused-function -O3 -fno-stack-protector -funroll-loops -DNDEBUG -DHAVE_GRIFFIN -DANDROID -DHAVE_DYNAMIC -DHAVE_OPENGL -DHAVE_OPENGLES -DHAVE_VID_CONTEXT -DHAVE_OPENGLES2 -DGLSL_DEBUG -DHAVE_GLSL -DHAVE_ZLIB -DWANT_RZLIB -DINLINE=inline -DLSB_FIRST -DHAVE_THREAD -D__LIBRETRO__ -DRARCH_PERFORMANCE_MODE -DRARCH_GPU_PERFORMANCE_MODE -DHAVE_OVERLAY -DPACKAGE_VERSION=\"$(RARCH_VERSION)\" -std=gnu99

LOCAL_LDLIBS	:= -L$(SYSROOT)/usr/lib -landroid -lEGL -lGLESv2 -llog -ldl
LOCAL_C_INCLUDES += $(LIBXML_PATH)

ifeq ($(HAVE_OPENSL), 1)
LOCAL_CFLAGS += -DHAVE_SL
LOCAL_LDLIBS += -lOpenSLES
endif

include $(BUILD_SHARED_LIBRARY)

# Include all present sub-modules
FOCAL_PATH := $(LOCAL_PATH)

define function
$(eval RETRO_MODULE_OBJECT := $(1))
$(eval include $(FOCAL_PATH)/modules/Android.mk)
endef

$(foreach m,$(wildcard $(FOCAL_PATH)/modules/*.so),$(eval $(call function,$(m))))
