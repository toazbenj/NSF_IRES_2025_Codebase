// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from local_planner_msgs:msg/TrajectoryList.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "local_planner_msgs/msg/detail/trajectory_list__rosidl_typesupport_introspection_c.h"
#include "local_planner_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "local_planner_msgs/msg/detail/trajectory_list__functions.h"
#include "local_planner_msgs/msg/detail/trajectory_list__struct.h"


// Include directives for member types
// Member `paths`
#include "local_planner_msgs/msg/trajectory.h"
// Member `paths`
#include "local_planner_msgs/msg/detail/trajectory__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  local_planner_msgs__msg__TrajectoryList__init(message_memory);
}

void local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_fini_function(void * message_memory)
{
  local_planner_msgs__msg__TrajectoryList__fini(message_memory);
}

size_t local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__size_function__TrajectoryList__paths(
  const void * untyped_member)
{
  const local_planner_msgs__msg__Trajectory__Sequence * member =
    (const local_planner_msgs__msg__Trajectory__Sequence *)(untyped_member);
  return member->size;
}

const void * local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__get_const_function__TrajectoryList__paths(
  const void * untyped_member, size_t index)
{
  const local_planner_msgs__msg__Trajectory__Sequence * member =
    (const local_planner_msgs__msg__Trajectory__Sequence *)(untyped_member);
  return &member->data[index];
}

void * local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__get_function__TrajectoryList__paths(
  void * untyped_member, size_t index)
{
  local_planner_msgs__msg__Trajectory__Sequence * member =
    (local_planner_msgs__msg__Trajectory__Sequence *)(untyped_member);
  return &member->data[index];
}

void local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__fetch_function__TrajectoryList__paths(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const local_planner_msgs__msg__Trajectory * item =
    ((const local_planner_msgs__msg__Trajectory *)
    local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__get_const_function__TrajectoryList__paths(untyped_member, index));
  local_planner_msgs__msg__Trajectory * value =
    (local_planner_msgs__msg__Trajectory *)(untyped_value);
  *value = *item;
}

void local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__assign_function__TrajectoryList__paths(
  void * untyped_member, size_t index, const void * untyped_value)
{
  local_planner_msgs__msg__Trajectory * item =
    ((local_planner_msgs__msg__Trajectory *)
    local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__get_function__TrajectoryList__paths(untyped_member, index));
  const local_planner_msgs__msg__Trajectory * value =
    (const local_planner_msgs__msg__Trajectory *)(untyped_value);
  *item = *value;
}

bool local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__resize_function__TrajectoryList__paths(
  void * untyped_member, size_t size)
{
  local_planner_msgs__msg__Trajectory__Sequence * member =
    (local_planner_msgs__msg__Trajectory__Sequence *)(untyped_member);
  local_planner_msgs__msg__Trajectory__Sequence__fini(member);
  return local_planner_msgs__msg__Trajectory__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_member_array[1] = {
  {
    "paths",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(local_planner_msgs__msg__TrajectoryList, paths),  // bytes offset in struct
    NULL,  // default value
    local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__size_function__TrajectoryList__paths,  // size() function pointer
    local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__get_const_function__TrajectoryList__paths,  // get_const(index) function pointer
    local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__get_function__TrajectoryList__paths,  // get(index) function pointer
    local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__fetch_function__TrajectoryList__paths,  // fetch(index, &value) function pointer
    local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__assign_function__TrajectoryList__paths,  // assign(index, value) function pointer
    local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__resize_function__TrajectoryList__paths  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_members = {
  "local_planner_msgs__msg",  // message namespace
  "TrajectoryList",  // message name
  1,  // number of fields
  sizeof(local_planner_msgs__msg__TrajectoryList),
  local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_member_array,  // message members
  local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_init_function,  // function to initialize message memory (memory has to be allocated)
  local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_type_support_handle = {
  0,
  &local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_local_planner_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, local_planner_msgs, msg, TrajectoryList)() {
  local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, local_planner_msgs, msg, Trajectory)();
  if (!local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_type_support_handle.typesupport_identifier) {
    local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &local_planner_msgs__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
