// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from traj_planning_msg:msg/TrajectoryList.idl
// generated code does not contain a copyright notice

#ifndef TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY_LIST__BUILDER_HPP_
#define TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY_LIST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "traj_planning_msg/msg/detail/trajectory_list__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace traj_planning_msg
{

namespace msg
{

namespace builder
{

class Init_TrajectoryList_paths
{
public:
  Init_TrajectoryList_paths()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::traj_planning_msg::msg::TrajectoryList paths(::traj_planning_msg::msg::TrajectoryList::_paths_type arg)
  {
    msg_.paths = std::move(arg);
    return std::move(msg_);
  }

private:
  ::traj_planning_msg::msg::TrajectoryList msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::traj_planning_msg::msg::TrajectoryList>()
{
  return traj_planning_msg::msg::builder::Init_TrajectoryList_paths();
}

}  // namespace traj_planning_msg

#endif  // TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY_LIST__BUILDER_HPP_
