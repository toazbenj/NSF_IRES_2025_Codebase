// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from local_planner_msgs:msg/Trajectory.idl
// generated code does not contain a copyright notice

#ifndef LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY__BUILDER_HPP_
#define LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "local_planner_msgs/msg/detail/trajectory__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace local_planner_msgs
{

namespace msg
{

namespace builder
{

class Init_Trajectory_speed
{
public:
  explicit Init_Trajectory_speed(::local_planner_msgs::msg::Trajectory & msg)
  : msg_(msg)
  {}
  ::local_planner_msgs::msg::Trajectory speed(::local_planner_msgs::msg::Trajectory::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::local_planner_msgs::msg::Trajectory msg_;
};

class Init_Trajectory_path
{
public:
  explicit Init_Trajectory_path(::local_planner_msgs::msg::Trajectory & msg)
  : msg_(msg)
  {}
  Init_Trajectory_speed path(::local_planner_msgs::msg::Trajectory::_path_type arg)
  {
    msg_.path = std::move(arg);
    return Init_Trajectory_speed(msg_);
  }

private:
  ::local_planner_msgs::msg::Trajectory msg_;
};

class Init_Trajectory_header
{
public:
  Init_Trajectory_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Trajectory_path header(::local_planner_msgs::msg::Trajectory::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_Trajectory_path(msg_);
  }

private:
  ::local_planner_msgs::msg::Trajectory msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::local_planner_msgs::msg::Trajectory>()
{
  return local_planner_msgs::msg::builder::Init_Trajectory_header();
}

}  // namespace local_planner_msgs

#endif  // LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY__BUILDER_HPP_
