// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from local_planner_msgs:msg/TrajectoryList.idl
// generated code does not contain a copyright notice
#include "local_planner_msgs/msg/detail/trajectory_list__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `paths`
#include "local_planner_msgs/msg/detail/trajectory__functions.h"

bool
local_planner_msgs__msg__TrajectoryList__init(local_planner_msgs__msg__TrajectoryList * msg)
{
  if (!msg) {
    return false;
  }
  // paths
  if (!local_planner_msgs__msg__Trajectory__Sequence__init(&msg->paths, 0)) {
    local_planner_msgs__msg__TrajectoryList__fini(msg);
    return false;
  }
  return true;
}

void
local_planner_msgs__msg__TrajectoryList__fini(local_planner_msgs__msg__TrajectoryList * msg)
{
  if (!msg) {
    return;
  }
  // paths
  local_planner_msgs__msg__Trajectory__Sequence__fini(&msg->paths);
}

bool
local_planner_msgs__msg__TrajectoryList__are_equal(const local_planner_msgs__msg__TrajectoryList * lhs, const local_planner_msgs__msg__TrajectoryList * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // paths
  if (!local_planner_msgs__msg__Trajectory__Sequence__are_equal(
      &(lhs->paths), &(rhs->paths)))
  {
    return false;
  }
  return true;
}

bool
local_planner_msgs__msg__TrajectoryList__copy(
  const local_planner_msgs__msg__TrajectoryList * input,
  local_planner_msgs__msg__TrajectoryList * output)
{
  if (!input || !output) {
    return false;
  }
  // paths
  if (!local_planner_msgs__msg__Trajectory__Sequence__copy(
      &(input->paths), &(output->paths)))
  {
    return false;
  }
  return true;
}

local_planner_msgs__msg__TrajectoryList *
local_planner_msgs__msg__TrajectoryList__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  local_planner_msgs__msg__TrajectoryList * msg = (local_planner_msgs__msg__TrajectoryList *)allocator.allocate(sizeof(local_planner_msgs__msg__TrajectoryList), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(local_planner_msgs__msg__TrajectoryList));
  bool success = local_planner_msgs__msg__TrajectoryList__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
local_planner_msgs__msg__TrajectoryList__destroy(local_planner_msgs__msg__TrajectoryList * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    local_planner_msgs__msg__TrajectoryList__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
local_planner_msgs__msg__TrajectoryList__Sequence__init(local_planner_msgs__msg__TrajectoryList__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  local_planner_msgs__msg__TrajectoryList * data = NULL;

  if (size) {
    data = (local_planner_msgs__msg__TrajectoryList *)allocator.zero_allocate(size, sizeof(local_planner_msgs__msg__TrajectoryList), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = local_planner_msgs__msg__TrajectoryList__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        local_planner_msgs__msg__TrajectoryList__fini(&data[i - 1]);
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
local_planner_msgs__msg__TrajectoryList__Sequence__fini(local_planner_msgs__msg__TrajectoryList__Sequence * array)
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
      local_planner_msgs__msg__TrajectoryList__fini(&array->data[i]);
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

local_planner_msgs__msg__TrajectoryList__Sequence *
local_planner_msgs__msg__TrajectoryList__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  local_planner_msgs__msg__TrajectoryList__Sequence * array = (local_planner_msgs__msg__TrajectoryList__Sequence *)allocator.allocate(sizeof(local_planner_msgs__msg__TrajectoryList__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = local_planner_msgs__msg__TrajectoryList__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
local_planner_msgs__msg__TrajectoryList__Sequence__destroy(local_planner_msgs__msg__TrajectoryList__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    local_planner_msgs__msg__TrajectoryList__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
local_planner_msgs__msg__TrajectoryList__Sequence__are_equal(const local_planner_msgs__msg__TrajectoryList__Sequence * lhs, const local_planner_msgs__msg__TrajectoryList__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!local_planner_msgs__msg__TrajectoryList__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
local_planner_msgs__msg__TrajectoryList__Sequence__copy(
  const local_planner_msgs__msg__TrajectoryList__Sequence * input,
  local_planner_msgs__msg__TrajectoryList__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(local_planner_msgs__msg__TrajectoryList);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    local_planner_msgs__msg__TrajectoryList * data =
      (local_planner_msgs__msg__TrajectoryList *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!local_planner_msgs__msg__TrajectoryList__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          local_planner_msgs__msg__TrajectoryList__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!local_planner_msgs__msg__TrajectoryList__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
