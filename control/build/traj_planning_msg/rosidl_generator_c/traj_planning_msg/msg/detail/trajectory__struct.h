// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from traj_planning_msg:msg/Trajectory.idl
// generated code does not contain a copyright notice

#ifndef TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY__STRUCT_H_
#define TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY__STRUCT_H_

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

/// Struct defined in msg/Trajectory in the package traj_planning_msg.
typedef struct traj_planning_msg__msg__Trajectory
{
  std_msgs__msg__Header header;
  nav_msgs__msg__Path path;
  std_msgs__msg__Float64 speed;
} traj_planning_msg__msg__Trajectory;

// Struct for a sequence of traj_planning_msg__msg__Trajectory.
typedef struct traj_planning_msg__msg__Trajectory__Sequence
{
  traj_planning_msg__msg__Trajectory * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} traj_planning_msg__msg__Trajectory__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY__STRUCT_H_
