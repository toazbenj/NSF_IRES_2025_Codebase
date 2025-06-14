// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from traj_planning_msg:msg/TrajectoryList.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "traj_planning_msg/msg/detail/trajectory_list__rosidl_typesupport_introspection_c.h"
#include "traj_planning_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "traj_planning_msg/msg/detail/trajectory_list__functions.h"
#include "traj_planning_msg/msg/detail/trajectory_list__struct.h"


// Include directives for member types
// Member `paths`
#include "traj_planning_msg/msg/trajectory.h"
// Member `paths`
#include "traj_planning_msg/msg/detail/trajectory__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  traj_planning_msg__msg__TrajectoryList__init(message_memory);
}

void traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_fini_function(void * message_memory)
{
  traj_planning_msg__msg__TrajectoryList__fini(message_memory);
}

size_t traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__size_function__TrajectoryList__paths(
  const void * untyped_member)
{
  const traj_planning_msg__msg__Trajectory__Sequence * member =
    (const traj_planning_msg__msg__Trajectory__Sequence *)(untyped_member);
  return member->size;
}

const void * traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__get_const_function__TrajectoryList__paths(
  const void * untyped_member, size_t index)
{
  const traj_planning_msg__msg__Trajectory__Sequence * member =
    (const traj_planning_msg__msg__Trajectory__Sequence *)(untyped_member);
  return &member->data[index];
}

void * traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__get_function__TrajectoryList__paths(
  void * untyped_member, size_t index)
{
  traj_planning_msg__msg__Trajectory__Sequence * member =
    (traj_planning_msg__msg__Trajectory__Sequence *)(untyped_member);
  return &member->data[index];
}

void traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__fetch_function__TrajectoryList__paths(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const traj_planning_msg__msg__Trajectory * item =
    ((const traj_planning_msg__msg__Trajectory *)
    traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__get_const_function__TrajectoryList__paths(untyped_member, index));
  traj_planning_msg__msg__Trajectory * value =
    (traj_planning_msg__msg__Trajectory *)(untyped_value);
  *value = *item;
}

void traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__assign_function__TrajectoryList__paths(
  void * untyped_member, size_t index, const void * untyped_value)
{
  traj_planning_msg__msg__Trajectory * item =
    ((traj_planning_msg__msg__Trajectory *)
    traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__get_function__TrajectoryList__paths(untyped_member, index));
  const traj_planning_msg__msg__Trajectory * value =
    (const traj_planning_msg__msg__Trajectory *)(untyped_value);
  *item = *value;
}

bool traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__resize_function__TrajectoryList__paths(
  void * untyped_member, size_t size)
{
  traj_planning_msg__msg__Trajectory__Sequence * member =
    (traj_planning_msg__msg__Trajectory__Sequence *)(untyped_member);
  traj_planning_msg__msg__Trajectory__Sequence__fini(member);
  return traj_planning_msg__msg__Trajectory__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_member_array[1] = {
  {
    "paths",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(traj_planning_msg__msg__TrajectoryList, paths),  // bytes offset in struct
    NULL,  // default value
    traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__size_function__TrajectoryList__paths,  // size() function pointer
    traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__get_const_function__TrajectoryList__paths,  // get_const(index) function pointer
    traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__get_function__TrajectoryList__paths,  // get(index) function pointer
    traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__fetch_function__TrajectoryList__paths,  // fetch(index, &value) function pointer
    traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__assign_function__TrajectoryList__paths,  // assign(index, value) function pointer
    traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__resize_function__TrajectoryList__paths  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_members = {
  "traj_planning_msg__msg",  // message namespace
  "TrajectoryList",  // message name
  1,  // number of fields
  sizeof(traj_planning_msg__msg__TrajectoryList),
  traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_member_array,  // message members
  traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_init_function,  // function to initialize message memory (memory has to be allocated)
  traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_type_support_handle = {
  0,
  &traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_traj_planning_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, traj_planning_msg, msg, TrajectoryList)() {
  traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, traj_planning_msg, msg, Trajectory)();
  if (!traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_type_support_handle.typesupport_identifier) {
    traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &traj_planning_msg__msg__TrajectoryList__rosidl_typesupport_introspection_c__TrajectoryList_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
