// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from local_planner_msgs:msg/Trajectory.idl
// generated code does not contain a copyright notice

#ifndef LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY__STRUCT_H_
#define LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'path'
#include "nav_msgs/msg/detail/path__struct.h"
// Member 'speed'
#include "std_msgs/msg/detail/float64__struct.h"

/// Struct defined in msg/Trajectory in the package local_planner_msgs.
typedef struct local_planner_msgs__msg__Trajectory
{
  std_msgs__msg__Header header;
  nav_msgs__msg__Path path;
  std_msgs__msg__Float64 speed;
} local_planner_msgs__msg__Trajectory;

// Struct for a sequence of local_planner_msgs__msg__Trajectory.
typedef struct local_planner_msgs__msg__Trajectory__Sequence
{
  local_planner_msgs__msg__Trajectory * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} local_planner_msgs__msg__Trajectory__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY__STRUCT_H_
