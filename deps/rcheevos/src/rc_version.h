#ifndef RC_VERSION_H
#define RC_VERSION_H

#ifdef __cplusplus
extern "C" {
#endif

#define RCHEEVOS_VERSION_MAJOR 11
#define RCHEEVOS_VERSION_MINOR 0
#define RCHEEVOS_VERSION_PATCH 0

#define RCHEEVOS_MAKE_VERSION(major, minor, patch) (major * 1000000 + minor * 1000 + patch)
#define RCHEEVOS_VERSION RCHEEVOS_MAKE_VERSION(RCHEEVOS_VERSION_MAJOR, RCHEEVOS_VERSION_MINOR, RCHEEVOS_VERSION_PATCH)

#define RCHEEVOS_MAKE_STRING(num) #num
#define RCHEEVOS_MAKE_VERSION_STRING(major, minor, patch) RCHEEVOS_MAKE_STRING(major) "." RCHEEVOS_MAKE_STRING(minor) "." RCHEEVOS_MAKE_STRING(patch)
#define RCHEEVOS_MAKE_VERSION_STRING_SHORT(major, minor) RCHEEVOS_MAKE_STRING(major) "." RCHEEVOS_MAKE_STRING(minor)

#if RCHEEVOS_VERSION_PATCH > 0
 #define RCHEEVOS_VERSION_STRING RCHEEVOS_MAKE_VERSION_STRING(RCHEEVOS_VERSION_MAJOR, RCHEEVOS_VERSION_MINOR, RCHEEVOS_VERSION_PATCH)
#else
 #define RCHEEVOS_VERSION_STRING RCHEEVOS_MAKE_VERSION_STRING_SHORT(RCHEEVOS_VERSION_MAJOR, RCHEEVOS_VERSION_MINOR)
#endif

#ifdef __cplusplus
}
#endif

#endif /* RC_VERSION_H */
