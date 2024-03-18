cmake_minimum_required(VERSION 3.16)
project(viprohead_viscotec_ros2 LANGUAGES CXX)

if(CMAKE_CXX_COMPILER_ID MATCHES "(GNU|Clang)")
  add_compile_options(-Wall -Wextra)
endif()

# find dependencies
set(THIS_PACKAGE_INCLUDE_DEPENDS
  hardware_interface
  control_msgs
  std_msgs
  pluginlib
  rclcpp
  rclcpp_lifecycle
  controller_interface
)

# find dependencies
find_package(ament_cmake REQUIRED)
foreach(Dependency IN ITEMS ${THIS_PACKAGE_INCLUDE_DEPENDS})
  find_package(${Dependency} REQUIRED)
endforeach()


## COMPILE
add_library(
  viprohead_viscotec_ros2
  SHARED
  hardware/extruder.cpp
  controllers/gpio_controller.cpp
)
target_compile_features(viprohead_viscotec_ros2 PUBLIC cxx_std_17)
target_include_directories(viprohead_viscotec_ros2 PUBLIC
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/hardware/include>
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/controllers/include>
$<INSTALL_INTERFACE:include/viprohead_viscotec_ros2>
)
ament_target_dependencies(
  viprohead_viscotec_ros2 PUBLIC
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(${PROJECT_NAME} PRIVATE "VIPROHEAD_VISCOTEC_ROS2_BUILDING_DLL")

# Export hardware plugins
pluginlib_export_plugin_description_file(hardware_interface viprohead_viscotec_ros2.xml)
# Export controllers
pluginlib_export_plugin_description_file(controller_interface viprohead_viscotec_ros2.xml)

# INSTALL
install(
  DIRECTORY hardware/include/
  DESTINATION include/viprohead_viscotec_ros2
)
install(
  DIRECTORY controllers/include/
  DESTINATION include/viprohead_viscotec_ros2
)
install(
  DIRECTORY description/launch description/ros2_control description/urdf
  DESTINATION share/viprohead_viscotec_ros2
)
install(
  DIRECTORY bringup/launch bringup/config
  DESTINATION share/viprohead_viscotec_ros2
)
install(TARGETS viprohead_viscotec_ros2
  EXPORT viprohead_viscotec_ros2
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)

  ament_add_pytest_test(example_10_urdf_xacro test/test_urdf_xacro.py)
  ament_add_pytest_test(view_example_10_launch test/test_extruder_launch.py)
endif()

## EXPORTS
ament_export_targets(viprohead_viscotec_ros2 HAS_LIBRARY_TARGET)
ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})
ament_package()
