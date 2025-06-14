// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from traj_planning_msg:msg/Trajectory.idl
// generated code does not contain a copyright notice
#include "traj_planning_msg/msg/detail/trajectory__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `path`
#include "nav_msgs/msg/detail/path__functions.h"
// Member `speed`
#include "std_msgs/msg/detail/float64__functions.h"

bool
traj_planning_msg__msg__Trajectory__init(traj_planning_msg__msg__Trajectory * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    traj_planning_msg__msg__Trajectory__fini(msg);
    return false;
  }
  // path
  if (!nav_msgs__msg__Path__init(&msg->path)) {
    traj_planning_msg__msg__Trajectory__fini(msg);
    return false;
  }
  // speed
  if (!std_msgs__msg__Float64__init(&msg->speed)) {
    traj_planning_msg__msg__Trajectory__fini(msg);
    return false;
  }
  return true;
}

void
traj_planning_msg__msg__Trajectory__fini(traj_planning_msg__msg__Trajectory * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // path
  nav_msgs__msg__Path__fini(&msg->path);
  // speed
  std_msgs__msg__Float64__fini(&msg->speed);
}

bool
traj_planning_msg__msg__Trajectory__are_equal(const traj_planning_msg__msg__Trajectory * lhs, const traj_planning_msg__msg__Trajectory * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // path
  if (!nav_msgs__msg__Path__are_equal(
      &(lhs->path), &(rhs->path)))
  {
    return false;
  }
  // speed
  if (!std_msgs__msg__Float64__are_equal(
      &(lhs->speed), &(rhs->speed)))
  {
    return false;
  }
  return true;
}

bool
traj_planning_msg__msg__Trajectory__copy(
  const traj_planning_msg__msg__Trajectory * input,
  traj_planning_msg__msg__Trajectory * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // path
  if (!nav_msgs__msg__Path__copy(
      &(input->path), &(output->path)))
  {
    return false;
  }
  // speed
  if (!std_msgs__msg__Float64__copy(
      &(input->speed), &(output->speed)))
  {
    return false;
  }
  return true;
}

traj_planning_msg__msg__Trajectory *
traj_planning_msg__msg__Trajectory__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  traj_planning_msg__msg__Trajectory * msg = (traj_planning_msg__msg__Trajectory *)allocator.allocate(sizeof(traj_planning_msg__msg__Trajectory), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(traj_planning_msg__msg__Trajectory));
  bool success = traj_planning_msg__msg__Trajectory__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
traj_planning_msg__msg__Trajectory__destroy(traj_planning_msg__msg__Trajectory * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    traj_planning_msg__msg__Trajectory__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
traj_planning_msg__msg__Trajectory__Sequence__init(traj_planning_msg__msg__Trajectory__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  traj_planning_msg__msg__Trajectory * data = NULL;

  if (size) {
    data = (traj_planning_msg__msg__Trajectory *)allocator.zero_allocate(size, sizeof(traj_planning_msg__msg__Trajectory), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = traj_planning_msg__msg__Trajectory__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        traj_planning_msg__msg__Trajectory__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
traj_planning_msg__msg__Trajectory__Sequence__fini(traj_planning_msg__msg__Trajectory__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      traj_planning_msg__msg__Trajectory__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

traj_planning_msg__msg__Trajectory__Sequence *
traj_planning_msg__msg__Trajectory__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  traj_planning_msg__msg__Trajectory__Sequence * array = (traj_planning_msg__msg__Trajectory__Sequence *)allocator.allocate(sizeof(traj_planning_msg__msg__Trajectory__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = traj_planning_msg__msg__Trajectory__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
traj_planning_msg__msg__Trajectory__Sequence__destroy(traj_planning_msg__msg__Trajectory__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    traj_planning_msg__msg__Trajectory__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
traj_planning_msg__msg__Trajectory__Sequence__are_equal(const traj_planning_msg__msg__Trajectory__Sequence * lhs, const traj_planning_msg__msg__Trajectory__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!traj_planning_msg__msg__Trajectory__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
traj_planning_msg__msg__Trajectory__Sequence__copy(
  const traj_planning_msg__msg__Trajectory__Sequence * input,
  traj_planning_msg__msg__Trajectory__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(traj_planning_msg__msg__Trajectory);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    traj_planning_msg__msg__Trajectory * data =
      (traj_planning_msg__msg__Trajectory *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!traj_planning_msg__msg__Trajectory__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          traj_planning_msg__msg__Trajectory__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!traj_planning_msg__msg__Trajectory__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
