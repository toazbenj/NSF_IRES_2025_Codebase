// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from local_planner_msgs:msg/TrajectoryList.idl
// generated code does not contain a copyright notice

#ifndef LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY_LIST__STRUCT_H_
#define LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY_LIST__STRUCT_H_

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
#include "local_planner_msgs/msg/detail/trajectory__struct.h"

/// Struct defined in msg/TrajectoryList in the package local_planner_msgs.
typedef struct local_planner_msgs__msg__TrajectoryList
{
  local_planner_msgs__msg__Trajectory__Sequence paths;
} local_planner_msgs__msg__TrajectoryList;

// Struct for a sequence of local_planner_msgs__msg__TrajectoryList.
typedef struct local_planner_msgs__msg__TrajectoryList__Sequence
{
  local_planner_msgs__msg__TrajectoryList * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} local_planner_msgs__msg__TrajectoryList__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY_LIST__STRUCT_H_
