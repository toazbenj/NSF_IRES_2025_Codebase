// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from traj_planning_msg:msg/SpeedPath.idl
// generated code does not contain a copyright notice

#ifndef TRAJ_PLANNING_MSG__MSG__DETAIL__SPEED_PATH__BUILDER_HPP_
#define TRAJ_PLANNING_MSG__MSG__DETAIL__SPEED_PATH__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "traj_planning_msg/msg/detail/speed_path__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace traj_planning_msg
{

namespace msg
{

namespace builder
{

class Init_SpeedPath_speed
{
public:
  explicit Init_SpeedPath_speed(::traj_planning_msg::msg::SpeedPath & msg)
  : msg_(msg)
  {}
  ::traj_planning_msg::msg::SpeedPath speed(::traj_planning_msg::msg::SpeedPath::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::traj_planning_msg::msg::SpeedPath msg_;
};

class Init_SpeedPath_path
{
public:
  Init_SpeedPath_path()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SpeedPath_speed path(::traj_planning_msg::msg::SpeedPath::_path_type arg)
  {
    msg_.path = std::move(arg);
    return Init_SpeedPath_speed(msg_);
  }

private:
  ::traj_planning_msg::msg::SpeedPath msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::traj_planning_msg::msg::SpeedPath>()
{
  return traj_planning_msg::msg::builder::Init_SpeedPath_path();
}

}  // namespace traj_planning_msg

#endif  // TRAJ_PLANNING_MSG__MSG__DETAIL__SPEED_PATH__BUILDER_HPP_
