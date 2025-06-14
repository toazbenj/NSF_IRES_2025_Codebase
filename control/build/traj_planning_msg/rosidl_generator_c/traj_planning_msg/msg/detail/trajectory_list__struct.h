// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from traj_planning_msg:msg/TrajectoryList.idl
// generated code does not contain a copyright notice

#ifndef TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY_LIST__STRUCT_H_
#define TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY_LIST__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'paths'
#include "traj_planning_msg/msg/detail/trajectory__struct.h"

/// Struct defined in msg/TrajectoryList in the package traj_planning_msg.
typedef struct traj_planning_msg__msg__TrajectoryList
{
  traj_planning_msg__msg__Trajectory__Sequence paths;
} traj_planning_msg__msg__TrajectoryList;

// Struct for a sequence of traj_planning_msg__msg__TrajectoryList.
typedef struct traj_planning_msg__msg__TrajectoryList__Sequence
{
  traj_planning_msg__msg__TrajectoryList * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} traj_planning_msg__msg__TrajectoryList__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY_LIST__STRUCT_H_
