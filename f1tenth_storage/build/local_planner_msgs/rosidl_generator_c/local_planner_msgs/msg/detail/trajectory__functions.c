// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from local_planner_msgs:msg/Trajectory.idl
// generated code does not contain a copyright notice
#include "local_planner_msgs/msg/detail/trajectory__functions.h"

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
local_planner_msgs__msg__Trajectory__init(local_planner_msgs__msg__Trajectory * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    local_planner_msgs__msg__Trajectory__fini(msg);
    return false;
  }
  // path
  if (!nav_msgs__msg__Path__init(&msg->path)) {
    local_planner_msgs__msg__Trajectory__fini(msg);
    return false;
  }
  // speed
  if (!std_msgs__msg__Float64__init(&msg->speed)) {
    local_planner_msgs__msg__Trajectory__fini(msg);
    return false;
  }
  return true;
}

void
local_planner_msgs__msg__Trajectory__fini(local_planner_msgs__msg__Trajectory * msg)
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
local_planner_msgs__msg__Trajectory__are_equal(const local_planner_msgs__msg__Trajectory * lhs, const local_planner_msgs__msg__Trajectory * rhs)
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
local_planner_msgs__msg__Trajectory__copy(
  const local_planner_msgs__msg__Trajectory * input,
  local_planner_msgs__msg__Trajectory * output)
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

local_planner_msgs__msg__Trajectory *
local_planner_msgs__msg__Trajectory__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  local_planner_msgs__msg__Trajectory * msg = (local_planner_msgs__msg__Trajectory *)allocator.allocate(sizeof(local_planner_msgs__msg__Trajectory), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(local_planner_msgs__msg__Trajectory));
  bool success = local_planner_msgs__msg__Trajectory__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
local_planner_msgs__msg__Trajectory__destroy(local_planner_msgs__msg__Trajectory * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    local_planner_msgs__msg__Trajectory__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
local_planner_msgs__msg__Trajectory__Sequence__init(local_planner_msgs__msg__Trajectory__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  local_planner_msgs__msg__Trajectory * data = NULL;

  if (size) {
    data = (local_planner_msgs__msg__Trajectory *)allocator.zero_allocate(size, sizeof(local_planner_msgs__msg__Trajectory), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = local_planner_msgs__msg__Trajectory__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        local_planner_msgs__msg__Trajectory__fini(&data[i - 1]);
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
local_planner_msgs__msg__Trajectory__Sequence__fini(local_planner_msgs__msg__Trajectory__Sequence * array)
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
      local_planner_msgs__msg__Trajectory__fini(&array->data[i]);
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

local_planner_msgs__msg__Trajectory__Sequence *
local_planner_msgs__msg__Trajectory__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  local_planner_msgs__msg__Trajectory__Sequence * array = (local_planner_msgs__msg__Trajectory__Sequence *)allocator.allocate(sizeof(local_planner_msgs__msg__Trajectory__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = local_planner_msgs__msg__Trajectory__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
local_planner_msgs__msg__Trajectory__Sequence__destroy(local_planner_msgs__msg__Trajectory__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    local_planner_msgs__msg__Trajectory__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
local_planner_msgs__msg__Trajectory__Sequence__are_equal(const local_planner_msgs__msg__Trajectory__Sequence * lhs, const local_planner_msgs__msg__Trajectory__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!local_planner_msgs__msg__Trajectory__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
local_planner_msgs__msg__Trajectory__Sequence__copy(
  const local_planner_msgs__msg__Trajectory__Sequence * input,
  local_planner_msgs__msg__Trajectory__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(local_planner_msgs__msg__Trajectory);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    local_planner_msgs__msg__Trajectory * data =
      (local_planner_msgs__msg__Trajectory *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!local_planner_msgs__msg__Trajectory__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          local_planner_msgs__msg__Trajectory__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!local_planner_msgs__msg__Trajectory__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
