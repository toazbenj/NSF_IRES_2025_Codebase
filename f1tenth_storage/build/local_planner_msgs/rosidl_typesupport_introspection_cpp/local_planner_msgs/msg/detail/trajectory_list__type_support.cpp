// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from local_planner_msgs:msg/TrajectoryList.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "local_planner_msgs/msg/detail/trajectory_list__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace local_planner_msgs
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void TrajectoryList_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) local_planner_msgs::msg::TrajectoryList(_init);
}

void TrajectoryList_fini_function(void * message_memory)
{
  auto typed_message = static_cast<local_planner_msgs::msg::TrajectoryList *>(message_memory);
  typed_message->~TrajectoryList();
}

size_t size_function__TrajectoryList__paths(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<local_planner_msgs::msg::Trajectory> *>(untyped_member);
  return member->size();
}

const void * get_const_function__TrajectoryList__paths(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<local_planner_msgs::msg::Trajectory> *>(untyped_member);
  return &member[index];
}

void * get_function__TrajectoryList__paths(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<local_planner_msgs::msg::Trajectory> *>(untyped_member);
  return &member[index];
}

void fetch_function__TrajectoryList__paths(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const local_planner_msgs::msg::Trajectory *>(
    get_const_function__TrajectoryList__paths(untyped_member, index));
  auto & value = *reinterpret_cast<local_planner_msgs::msg::Trajectory *>(untyped_value);
  value = item;
}

void assign_function__TrajectoryList__paths(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<local_planner_msgs::msg::Trajectory *>(
    get_function__TrajectoryList__paths(untyped_member, index));
  const auto & value = *reinterpret_cast<const local_planner_msgs::msg::Trajectory *>(untyped_value);
  item = value;
}

void resize_function__TrajectoryList__paths(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<local_planner_msgs::msg::Trajectory> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember TrajectoryList_message_member_array[1] = {
  {
    "paths",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<local_planner_msgs::msg::Trajectory>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(local_planner_msgs::msg::TrajectoryList, paths),  // bytes offset in struct
    nullptr,  // default value
    size_function__TrajectoryList__paths,  // size() function pointer
    get_const_function__TrajectoryList__paths,  // get_const(index) function pointer
    get_function__TrajectoryList__paths,  // get(index) function pointer
    fetch_function__TrajectoryList__paths,  // fetch(index, &value) function pointer
    assign_function__TrajectoryList__paths,  // assign(index, value) function pointer
    resize_function__TrajectoryList__paths  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers TrajectoryList_message_members = {
  "local_planner_msgs::msg",  // message namespace
  "TrajectoryList",  // message name
  1,  // number of fields
  sizeof(local_planner_msgs::msg::TrajectoryList),
  TrajectoryList_message_member_array,  // message members
  TrajectoryList_init_function,  // function to initialize message memory (memory has to be allocated)
  TrajectoryList_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t TrajectoryList_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &TrajectoryList_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace local_planner_msgs


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<local_planner_msgs::msg::TrajectoryList>()
{
  return &::local_planner_msgs::msg::rosidl_typesupport_introspection_cpp::TrajectoryList_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, local_planner_msgs, msg, TrajectoryList)() {
  return &::local_planner_msgs::msg::rosidl_typesupport_introspection_cpp::TrajectoryList_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
