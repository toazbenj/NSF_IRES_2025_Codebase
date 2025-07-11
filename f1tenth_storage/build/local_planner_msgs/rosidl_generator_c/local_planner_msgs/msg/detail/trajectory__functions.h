// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from local_planner_msgs:msg/Trajectory.idl
// generated code does not contain a copyright notice

#ifndef LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY__FUNCTIONS_H_
#define LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "local_planner_msgs/msg/rosidl_generator_c__visibility_control.h"

#include "local_planner_msgs/msg/detail/trajectory__struct.h"

/// Initialize msg/Trajectory message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * local_planner_msgs__msg__Trajectory
 * )) before or use
 * local_planner_msgs__msg__Trajectory__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_local_planner_msgs
bool
local_planner_msgs__msg__Trajectory__init(local_planner_msgs__msg__Trajectory * msg);

/// Finalize msg/Trajectory message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_local_planner_msgs
void
local_planner_msgs__msg__Trajectory__fini(local_planner_msgs__msg__Trajectory * msg);

/// Create msg/Trajectory message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * local_planner_msgs__msg__Trajectory__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_local_planner_msgs
local_planner_msgs__msg__Trajectory *
local_planner_msgs__msg__Trajectory__create();

/// Destroy msg/Trajectory message.
/**
 * It calls
 * local_planner_msgs__msg__Trajectory__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_local_planner_msgs
void
local_planner_msgs__msg__Trajectory__destroy(local_planner_msgs__msg__Trajectory * msg);

/// Check for msg/Trajectory message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_local_planner_msgs
bool
local_planner_msgs__msg__Trajectory__are_equal(const local_planner_msgs__msg__Trajectory * lhs, const local_planner_msgs__msg__Trajectory * rhs);

/// Copy a msg/Trajectory message.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source message pointer.
 * \param[out] output The target message pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer is null
 *   or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_local_planner_msgs
bool
local_planner_msgs__msg__Trajectory__copy(
  const local_planner_msgs__msg__Trajectory * input,
  local_planner_msgs__msg__Trajectory * output);

/// Initialize array of msg/Trajectory messages.
/**
 * It allocates the memory for the number of elements and calls
 * local_planner_msgs__msg__Trajectory__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_local_planner_msgs
bool
local_planner_msgs__msg__Trajectory__Sequence__init(local_planner_msgs__msg__Trajectory__Sequence * array, size_t size);

/// Finalize array of msg/Trajectory messages.
/**
 * It calls
 * local_planner_msgs__msg__Trajectory__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_local_planner_msgs
void
local_planner_msgs__msg__Trajectory__Sequence__fini(local_planner_msgs__msg__Trajectory__Sequence * array);

/// Create array of msg/Trajectory messages.
/**
 * It allocates the memory for the array and calls
 * local_planner_msgs__msg__Trajectory__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_local_planner_msgs
local_planner_msgs__msg__Trajectory__Sequence *
local_planner_msgs__msg__Trajectory__Sequence__create(size_t size);

/// Destroy array of msg/Trajectory messages.
/**
 * It calls
 * local_planner_msgs__msg__Trajectory__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_local_planner_msgs
void
local_planner_msgs__msg__Trajectory__Sequence__destroy(local_planner_msgs__msg__Trajectory__Sequence * array);

/// Check for msg/Trajectory message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_local_planner_msgs
bool
local_planner_msgs__msg__Trajectory__Sequence__are_equal(const local_planner_msgs__msg__Trajectory__Sequence * lhs, const local_planner_msgs__msg__Trajectory__Sequence * rhs);

/// Copy an array of msg/Trajectory messages.
/**
 * This functions performs a deep copy, as opposed to the shallow copy that
 * plain assignment yields.
 *
 * \param[in] input The source array pointer.
 * \param[out] output The target array pointer, which must
 *   have been initialized before calling this function.
 * \return true if successful, or false if either pointer
 *   is null or memory allocation fails.
 */
ROSIDL_GENERATOR_C_PUBLIC_local_planner_msgs
bool
local_planner_msgs__msg__Trajectory__Sequence__copy(
  const local_planner_msgs__msg__Trajectory__Sequence * input,
  local_planner_msgs__msg__Trajectory__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY__FUNCTIONS_H_
