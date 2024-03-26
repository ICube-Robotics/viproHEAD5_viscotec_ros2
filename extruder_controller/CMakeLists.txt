cmake_minimum_required(VERSION 3.5.0)
project(extruder_controller)

# Default to C11
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 11)
endif()
# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(NOT WIN32)
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_action REQUIRED)
find_package(ros2_control REQUIRED)
find_package(controller_manager REQUIRED)

set(THIS_PACKAGE_INCLUDE_DEPENDS
  ament_cmake
  rclcpp
  ros2_control
)

# install(DIRECTORY
#   launch
#   config
#   urdf
#   DESTINATION share/${PROJECT_NAME}/
# )

## extruder_controller
add_library(
  extruder_controller
  SHARED
  src/extruder_controller.cpp
)
target_include_directories(
  extruder_controller
  PRIVATE
  include
)
ament_target_dependencies(
  extruder_controller
  controller_interface
  hardware_interface
  realtime_tools
  pluginlib
  rclcpp
  rclcpp_lifecycle
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)

pluginlib_export_plugin_description_file(controller_interface extruder_controller.xml)

install(
  TARGETS
  extruder_controller
  DESTINATION lib
)
install(
  DIRECTORY
    include
  DESTINATION include
)

ament_export_include_directories(
  include
)
ament_export_libraries(
    extruder_controller
)
ament_export_dependencies(
  controller_interface
  hardware_interface
  pluginlib
  rclcpp
  rclcpp_lifecycle
  interfaces
  lib
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)
ament_package()