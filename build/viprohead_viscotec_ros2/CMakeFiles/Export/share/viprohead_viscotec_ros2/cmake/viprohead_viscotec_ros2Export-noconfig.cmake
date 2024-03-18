#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "viprohead_viscotec_ros2::viprohead_viscotec_ros2" for configuration ""
set_property(TARGET viprohead_viscotec_ros2::viprohead_viscotec_ros2 APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(viprohead_viscotec_ros2::viprohead_viscotec_ros2 PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libviprohead_viscotec_ros2.so"
  IMPORTED_SONAME_NOCONFIG "libviprohead_viscotec_ros2.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS viprohead_viscotec_ros2::viprohead_viscotec_ros2 )
list(APPEND _IMPORT_CHECK_FILES_FOR_viprohead_viscotec_ros2::viprohead_viscotec_ros2 "${_IMPORT_PREFIX}/lib/libviprohead_viscotec_ros2.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
