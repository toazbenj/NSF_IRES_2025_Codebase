// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from traj_planning_msg:msg/SpeedPath.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "traj_planning_msg/msg/detail/speed_path__rosidl_typesupport_introspection_c.h"
#include "traj_planning_msg/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "traj_planning_msg/msg/detail/speed_path__functions.h"
#include "traj_planning_msg/msg/detail/speed_path__struct.h"


// Include directives for member types
// Member `path`
#include "nav_msgs/msg/path.h"
// Member `path`
#include "nav_msgs/msg/detail/path__rosidl_typesupport_introspection_c.h"
// Member `speed`
#include "std_msgs/msg/float64.h"
// Member `speed`
#include "std_msgs/msg/detail/float64__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void traj_planning_msg__msg__SpeedPath__rosidl_typesupport_introspection_c__SpeedPath_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  traj_planning_msg__msg__SpeedPath__init(message_memory);
}

void traj_planning_msg__msg__SpeedPath__rosidl_typesupport_introspection_c__SpeedPath_fini_function(void * message_memory)
{
  traj_planning_msg__msg__SpeedPath__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember traj_planning_msg__msg__SpeedPath__rosidl_typesupport_introspection_c__SpeedPath_message_member_array[2] = {
  {
    "path",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(traj_planning_msg__msg__SpeedPath, path),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "speed",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(traj_planning_msg__msg__SpeedPath, speed),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers traj_planning_msg__msg__SpeedPath__rosidl_typesupport_introspection_c__SpeedPath_message_members = {
  "traj_planning_msg__msg",  // message namespace
  "SpeedPath",  // message name
  2,  // number of fields
  sizeof(traj_planning_msg__msg__SpeedPath),
  traj_planning_msg__msg__SpeedPath__rosidl_typesupport_introspection_c__SpeedPath_message_member_array,  // message members
  traj_planning_msg__msg__SpeedPath__rosidl_typesupport_introspection_c__SpeedPath_init_function,  // function to initialize message memory (memory has to be allocated)
  traj_planning_msg__msg__SpeedPath__rosidl_typesupport_introspection_c__SpeedPath_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t traj_planning_msg__msg__SpeedPath__rosidl_typesupport_introspection_c__SpeedPath_message_type_support_handle = {
  0,
  &traj_planning_msg__msg__SpeedPath__rosidl_typesupport_introspection_c__SpeedPath_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_traj_planning_msg
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, traj_planning_msg, msg, SpeedPath)() {
  traj_planning_msg__msg__SpeedPath__rosidl_typesupport_introspection_c__SpeedPath_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, nav_msgs, msg, Path)();
  traj_planning_msg__msg__SpeedPath__rosidl_typesupport_introspection_c__SpeedPath_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Float64)();
  if (!traj_planning_msg__msg__SpeedPath__rosidl_typesupport_introspection_c__SpeedPath_message_type_support_handle.typesupport_identifier) {
    traj_planning_msg__msg__SpeedPath__rosidl_typesupport_introspection_c__SpeedPath_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &traj_planning_msg__msg__SpeedPath__rosidl_typesupport_introspection_c__SpeedPath_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
