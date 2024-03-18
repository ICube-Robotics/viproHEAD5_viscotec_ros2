cmake_minimum_required(VERSION 3.16)
project(viprohead5_viscotec_ros2 LANGUAGES CXX)

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
  viprohead5_viscotec_ros2
  SHARED
  extruder_hardware/extruder.cpp
  extruder_controllers/gpio_controller.cpp
)
target_compile_features(viprohead5_viscotec_ros2 PUBLIC cxx_std_17)
target_include_directories(viprohead5_viscotec_ros2 PUBLIC
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/extruder_hardware/include>
$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/extruder_controllers/include>
$<INSTALL_INTERFACE:include/viprohead5_viscotec_ros2>
)
ament_target_dependencies(
  viprohead5_viscotec_ros2 PUBLIC
  ${THIS_PACKAGE_INCLUDE_DEPENDS}
)

# Causes the visibility macros to use dllexport rather than dllimport,
# which is appropriate when building the dll but not consuming it.
target_compile_definitions(${PROJECT_NAME} PRIVATE "VIPROHEAD5_VISCOTEC_ROS2_BUILDING_DLL")

# Export hardware plugins
pluginlib_export_plugin_description_file(hardware_interface viprohead5_viscotec_ros2.xml)
# Export controllers
pluginlib_export_plugin_description_file(controller_interface viprohead5_viscotec_ros2.xml)

# INSTALL
install(
  DIRECTORY extruder_hardware/include/
  DESTINATION include/viprohead5_viscotec_ros2
)
install(
  DIRECTORY extruder_controllers/include/
  DESTINATION include/viprohead5_viscotec_ros2
)
install(
  DIRECTORY extruder_description/launch extruder_description/ros2_control 
  DESTINATION share/viprohead5_viscotec_ros2
)
install(
  DIRECTORY extruder_bringup/launch extruder_bringup/config
  DESTINATION share/viprohead5_viscotec_ros2
)
install(TARGETS viprohead5_viscotec_ros2
  EXPORT viprohead5_viscotec_ros2
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

if(BUILD_TESTING)
  find_package(ament_cmake_pytest REQUIRED)

 # ament_add_pytest_test(example_10_urdf_xacro extruder_test/test_urdf_xacro.py)
 # ament_add_pytest_test(view_example_10_launch extruder_test/test_extruder_launch.py)
endif()

## EXPORTS
ament_export_targets(viprohead5_viscotec_ros2 HAS_LIBRARY_TARGET)
ament_export_dependencies(${THIS_PACKAGE_INCLUDE_DEPENDS})
ament_package()
