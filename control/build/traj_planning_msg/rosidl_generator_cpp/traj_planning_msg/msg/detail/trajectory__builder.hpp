// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from traj_planning_msg:msg/Trajectory.idl
// generated code does not contain a copyright notice

#ifndef TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY__BUILDER_HPP_
#define TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "traj_planning_msg/msg/detail/trajectory__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace traj_planning_msg
{

namespace msg
{

namespace builder
{

class Init_Trajectory_speed
{
public:
  explicit Init_Trajectory_speed(::traj_planning_msg::msg::Trajectory & msg)
  : msg_(msg)
  {}
  ::traj_planning_msg::msg::Trajectory speed(::traj_planning_msg::msg::Trajectory::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::traj_planning_msg::msg::Trajectory msg_;
};

class Init_Trajectory_path
{
public:
  explicit Init_Trajectory_path(::traj_planning_msg::msg::Trajectory & msg)
  : msg_(msg)
  {}
  Init_Trajectory_speed path(::traj_planning_msg::msg::Trajectory::_path_type arg)
  {
    msg_.path = std::move(arg);
    return Init_Trajectory_speed(msg_);
  }

private:
  ::traj_planning_msg::msg::Trajectory msg_;
};

class Init_Trajectory_header
{
public:
  Init_Trajectory_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Trajectory_path header(::traj_planning_msg::msg::Trajectory::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Trajectory_path(msg_);
  }

private:
  ::traj_planning_msg::msg::Trajectory msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::traj_planning_msg::msg::Trajectory>()
{
  return traj_planning_msg::msg::builder::Init_Trajectory_header();
}

}  // namespace traj_planning_msg

#endif  // TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY__BUILDER_HPP_
