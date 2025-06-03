// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from traj_planning_msg:msg/PathList.idl
// generated code does not contain a copyright notice

#ifndef TRAJ_PLANNING_MSG__MSG__DETAIL__PATH_LIST__BUILDER_HPP_
#define TRAJ_PLANNING_MSG__MSG__DETAIL__PATH_LIST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "traj_planning_msg/msg/detail/path_list__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace traj_planning_msg
{

namespace msg
{

namespace builder
{

class Init_PathList_paths
{
public:
  Init_PathList_paths()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::traj_planning_msg::msg::PathList paths(::traj_planning_msg::msg::PathList::_paths_type arg)
  {
    msg_.paths = std::move(arg);
    return std::move(msg_);
  }

private:
  ::traj_planning_msg::msg::PathList msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::traj_planning_msg::msg::PathList>()
{
  return traj_planning_msg::msg::builder::Init_PathList_paths();
}

}  // namespace traj_planning_msg

#endif  // TRAJ_PLANNING_MSG__MSG__DETAIL__PATH_LIST__BUILDER_HPP_
