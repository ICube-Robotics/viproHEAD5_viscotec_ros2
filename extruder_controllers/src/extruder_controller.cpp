// Copyright (c) 2024, ICube University of STrasbourg
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
/// \authors: Laurent Barbé

#include "extruder_controller/chained_controller.hpp"

controller_interface::CallbackReturn extruder_controller::ExtruderController::on_init()
{
  std::string param_name = "joints";

  // Receiving Joint Names from Config file
  if (!get_node()->get_parameter(param_name, joint_names_))
  {
    RCLCPP_ERROR_STREAM(get_node()->get_logger(), "Failed to get parameter: " << param_name);
    return controller_interface::CallbackReturn::ERROR;
  }

  // Joint size
  n_joints_ = joint_names_.size();

  if (n_joints_ == 0)
  {
    RCLCPP_ERROR_STREAM(get_node()->get_logger(), "List of joint names is empty.");
    return controller_interface::CallbackReturn::ERROR;
  }

  // Resize this value depending on reference interfaces to be sent
  reference_interfaces_.resize(n_joints_, std::numeric_limits<double>::quiet_NaN());
  joint_effort_command_.resize(n_joints_, std::numeric_limits<double>::quiet_NaN());

  return controller_interface::CallbackReturn::SUCCESS;
}

controller_interface::InterfaceConfiguration
extruder_controller::ExtruderController::command_interface_configuration() const
{
  RCLCPP_INFO(
    get_node()->get_logger(),
    "Command Interface ChainedController. Command Interface Required: Effort");

  controller_interface::InterfaceConfiguration command_interfaces_config;
  command_interfaces_config.type = controller_interface::interface_configuration_type::INDIVIDUAL;

  // Sending Command Interface value to Resource manager after Clipping it
  std::for_each(
    joint_names_.begin(), joint_names_.end(),
    [&command_interfaces_config](auto & joint_name)
    {
      command_interfaces_config.names.push_back(
        joint_name + "/" + hardware_interface::HW_IF_EFFORT);
    });

  return command_interfaces_config;
}

controller_interface::InterfaceConfiguration
extruder_controller::ExtruderController::state_interface_configuration() const
{
  RCLCPP_INFO(get_node()->get_logger(), "State Interface ChainedController.");

  // No State Interfaces
  controller_interface::InterfaceConfiguration state_interfaces_config;
  state_interfaces_config.type = controller_interface::interface_configuration_type::NONE;

  return state_interfaces_config;
}

std::vector<hardware_interface::CommandInterface>
extruder_controller::ExtruderController::on_export_reference_interfaces()
{
  RCLCPP_INFO(get_node()->get_logger(), "export_reference_interfaces");

  std::vector<hardware_interface::CommandInterface> reference_interfaces;

  std::string reference_interface_name = "effort";

  // Exporting reference interfaces to Higher Level Controller
  // Note: Name (or prefix name) of the controller should be name of the controller itself.
  // In our case it's "chaining_controller"
  for (size_t i = 0; i < n_joints_; i++)
  {
    reference_interfaces.push_back(hardware_interface::CommandInterface(
      std::string(get_node()->get_name()), reference_interface_name, &reference_interfaces_[i]));
  }

  return reference_interfaces;
}

bool extruder_controller::ExtruderController::on_set_chained_mode(bool chained_mode)
{
  RCLCPP_INFO(get_node()->get_logger(), "CHAINED MODE ACTIVE");

  chained_mode = true;
  return chained_mode;
}

controller_interface::return_type
extruder_controller::ExtruderController::update_reference_from_subscribers()
{
  RCLCPP_INFO_ONCE(get_node()->get_logger(), "update_reference_from_subscribers");
  return update() ? controller_interface::return_type::OK
                  : controller_interface::return_type::ERROR;
}

controller_interface::return_type extruder_controller::ExtruderController::update_and_write_commands(
  const rclcpp::Time & /*time*/, const rclcpp::Duration & /*period*/)
{
  RCLCPP_INFO_ONCE(get_node()->get_logger(), "update_and_write_commands");
  return update() ? controller_interface::return_type::OK
                  : controller_interface::return_type::ERROR;
}

bool extruder_controller::ExtruderController::update()
{
  // Clipping Value
  for (size_t i = 0; i < n_joints_; i++)
  {
    reference_interfaces_[i] = clip(reference_interfaces_[i], EFFORT_MIN, EFFORT_MAX);
  }
  // Registering the Command Interfaces
  registerJointCommand(reference_interfaces_);
  return true;
}
void extruder_controller::ExtruderController::registerJointCommand(
  const std::vector<double> & effort)
{
  for (size_t i = 0; i < n_joints_; i++)
  {
    std::string joint_name(joint_names_[i]);

    auto effort_command = std::find_if(
      command_interfaces_.begin(), command_interfaces_.end(),
      [&joint_name](const hardware_interface::LoanedCommandInterface & interface)
      {
        return interface.get_prefix_name() == joint_name &&
               interface.get_interface_name() == hardware_interface::HW_IF_EFFORT;
      });

    effort_command->set_value(effort[i]);
  }
}

PLUGINLIB_EXPORT_CLASS(
  extruder_controller::ExtruderController, controller_interface::ChainableControllerInterface)