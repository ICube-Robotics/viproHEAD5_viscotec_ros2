#ifndef EXTRUDER_CONTROLLER__VISIBILITY_EXTRUDER_CONTROLLER_H_
#define EXTRUDER_CONTROLLER__VISIBILITY_EXTRUDER_CONTROLLER_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define EXTRUDER_CONTROLLER_EXPORT __attribute__((dllexport))
#define EXTRUDER_CONTROLLER_IMPORT __attribute__((dllimport))
#else
#define EXTRUDER_CONTROLLER_EXPORT __declspec(dllexport)
#define EXTRUDER_CONTROLLER_IMPORT __declspec(dllimport)
#endif
#ifdef EXTRUDER_CONTROLLER_BUILDING_DLL
#define EXTRUDER_CONTROLLER_PUBLIC EXTRUDER_CONTROLLER_EXPORT
#else
#define EXTRUDER_CONTROLLER_PUBLIC EXTRUDER_CONTROLLER_IMPORT
#endif
#define EXTRUDER_CONTROLLER_PUBLIC_TYPE EXTRUDER_CONTROLLER_PUBLIC
#define EXTRUDER_CONTROLLER_LOCAL
#else
#define EXTRUDER_CONTROLLER_EXPORT __attribute__((visibility("default")))
#define EXTRUDER_CONTROLLER_IMPORT
#if __GNUC__ >= 4
#define EXTRUDER_CONTROLLER_PUBLIC __attribute__((visibility("default")))
#define EXTRUDER_CONTROLLER_LOCAL __attribute__((visibility("hidden")))
#else
#define EXTRUDER_CONTROLLER_PUBLIC
#define EXTRUDER_CONTROLLER_LOCAL
#endif
#define EXTRUDER_CONTROLLER_PUBLIC_TYPE
#endif

#endif  // EXTRUDER_CONTROLLER__VISIBILITY_EXTRUDER_CONTROLLER_H_