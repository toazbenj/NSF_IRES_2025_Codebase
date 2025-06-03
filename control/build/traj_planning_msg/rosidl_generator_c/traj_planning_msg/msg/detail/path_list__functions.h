// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from traj_planning_msg:msg/PathList.idl
// generated code does not contain a copyright notice

#ifndef TRAJ_PLANNING_MSG__MSG__DETAIL__PATH_LIST__FUNCTIONS_H_
#define TRAJ_PLANNING_MSG__MSG__DETAIL__PATH_LIST__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "traj_planning_msg/msg/rosidl_generator_c__visibility_control.h"

#include "traj_planning_msg/msg/detail/path_list__struct.h"

/// Initialize msg/PathList message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * traj_planning_msg__msg__PathList
 * )) before or use
 * traj_planning_msg__msg__PathList__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_traj_planning_msg
bool
traj_planning_msg__msg__PathList__init(traj_planning_msg__msg__PathList * msg);

/// Finalize msg/PathList message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_traj_planning_msg
void
traj_planning_msg__msg__PathList__fini(traj_planning_msg__msg__PathList * msg);

/// Create msg/PathList message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * traj_planning_msg__msg__PathList__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_traj_planning_msg
traj_planning_msg__msg__PathList *
traj_planning_msg__msg__PathList__create();

/// Destroy msg/PathList message.
/**
 * It calls
 * traj_planning_msg__msg__PathList__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_traj_planning_msg
void
traj_planning_msg__msg__PathList__destroy(traj_planning_msg__msg__PathList * msg);

/// Check for msg/PathList message equality.
/**
 * \param[in] lhs The message on the left hand size of the equality operator.
 * \param[in] rhs The message on the right hand size of the equality operator.
 * \return true if messages are equal, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_traj_planning_msg
bool
traj_planning_msg__msg__PathList__are_equal(const traj_planning_msg__msg__PathList * lhs, const traj_planning_msg__msg__PathList * rhs);

/// Copy a msg/PathList message.
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
ROSIDL_GENERATOR_C_PUBLIC_traj_planning_msg
bool
traj_planning_msg__msg__PathList__copy(
  const traj_planning_msg__msg__PathList * input,
  traj_planning_msg__msg__PathList * output);

/// Initialize array of msg/PathList messages.
/**
 * It allocates the memory for the number of elements and calls
 * traj_planning_msg__msg__PathList__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_traj_planning_msg
bool
traj_planning_msg__msg__PathList__Sequence__init(traj_planning_msg__msg__PathList__Sequence * array, size_t size);

/// Finalize array of msg/PathList messages.
/**
 * It calls
 * traj_planning_msg__msg__PathList__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_traj_planning_msg
void
traj_planning_msg__msg__PathList__Sequence__fini(traj_planning_msg__msg__PathList__Sequence * array);

/// Create array of msg/PathList messages.
/**
 * It allocates the memory for the array and calls
 * traj_planning_msg__msg__PathList__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_traj_planning_msg
traj_planning_msg__msg__PathList__Sequence *
traj_planning_msg__msg__PathList__Sequence__create(size_t size);

/// Destroy array of msg/PathList messages.
/**
 * It calls
 * traj_planning_msg__msg__PathList__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_traj_planning_msg
void
traj_planning_msg__msg__PathList__Sequence__destroy(traj_planning_msg__msg__PathList__Sequence * array);

/// Check for msg/PathList message array equality.
/**
 * \param[in] lhs The message array on the left hand size of the equality operator.
 * \param[in] rhs The message array on the right hand size of the equality operator.
 * \return true if message arrays are equal in size and content, otherwise false.
 */
ROSIDL_GENERATOR_C_PUBLIC_traj_planning_msg
bool
traj_planning_msg__msg__PathList__Sequence__are_equal(const traj_planning_msg__msg__PathList__Sequence * lhs, const traj_planning_msg__msg__PathList__Sequence * rhs);

/// Copy an array of msg/PathList messages.
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
ROSIDL_GENERATOR_C_PUBLIC_traj_planning_msg
bool
traj_planning_msg__msg__PathList__Sequence__copy(
  const traj_planning_msg__msg__PathList__Sequence * input,
  traj_planning_msg__msg__PathList__Sequence * output);

#ifdef __cplusplus
}
#endif

#endif  // TRAJ_PLANNING_MSG__MSG__DETAIL__PATH_LIST__FUNCTIONS_H_
