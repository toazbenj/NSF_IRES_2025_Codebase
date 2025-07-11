// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from local_planner_msgs:msg/TrajectoryList.idl
// generated code does not contain a copyright notice

#ifndef LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY_LIST__BUILDER_HPP_
#define LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY_LIST__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "local_planner_msgs/msg/detail/trajectory_list__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace local_planner_msgs
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
  ::local_planner_msgs::msg::TrajectoryList paths(::local_planner_msgs::msg::TrajectoryList::_paths_type arg)
  {
    msg_.paths = std::move(arg);
    return std::move(msg_);
  }

private:
  ::local_planner_msgs::msg::TrajectoryList msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::local_planner_msgs::msg::TrajectoryList>()
{
  return local_planner_msgs::msg::builder::Init_TrajectoryList_paths();
}

}  // namespace local_planner_msgs

#endif  // LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY_LIST__BUILDER_HPP_
