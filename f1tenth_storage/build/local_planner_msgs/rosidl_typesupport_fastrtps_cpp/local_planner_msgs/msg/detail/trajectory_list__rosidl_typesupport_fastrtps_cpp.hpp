// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__rosidl_typesupport_fastrtps_cpp.hpp.em
// with input from local_planner_msgs:msg/TrajectoryList.idl
// generated code does not contain a copyright notice

#ifndef LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY_LIST__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
#define LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY_LIST__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_

#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "local_planner_msgs/msg/rosidl_typesupport_fastrtps_cpp__visibility_control.h"
#include "local_planner_msgs/msg/detail/trajectory_list__struct.hpp"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

#include "fastcdr/Cdr.h"

namespace local_planner_msgs
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_local_planner_msgs
cdr_serialize(
  const local_planner_msgs::msg::TrajectoryList & ros_message,
  eprosima::fastcdr::Cdr & cdr);

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_local_planner_msgs
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  local_planner_msgs::msg::TrajectoryList & ros_message);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_local_planner_msgs
get_serialized_size(
  const local_planner_msgs::msg::TrajectoryList & ros_message,
  size_t current_alignment);

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_local_planner_msgs
max_serialized_size_TrajectoryList(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace local_planner_msgs

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_local_planner_msgs
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, local_planner_msgs, msg, TrajectoryList)();

#ifdef __cplusplus
}
#endif

#endif  // LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY_LIST__ROSIDL_TYPESUPPORT_FASTRTPS_CPP_HPP_
