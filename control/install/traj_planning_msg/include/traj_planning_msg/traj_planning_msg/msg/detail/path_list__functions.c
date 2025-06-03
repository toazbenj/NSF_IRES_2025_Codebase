// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from traj_planning_msg:msg/PathList.idl
// generated code does not contain a copyright notice
#include "traj_planning_msg/msg/detail/path_list__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `paths`
#include "nav_msgs/msg/detail/path__functions.h"

bool
traj_planning_msg__msg__PathList__init(traj_planning_msg__msg__PathList * msg)
{
  if (!msg) {
    return false;
  }
  // paths
  if (!nav_msgs__msg__Path__Sequence__init(&msg->paths, 0)) {
    traj_planning_msg__msg__PathList__fini(msg);
    return false;
  }
  return true;
}

void
traj_planning_msg__msg__PathList__fini(traj_planning_msg__msg__PathList * msg)
{
  if (!msg) {
    return;
  }
  // paths
  nav_msgs__msg__Path__Sequence__fini(&msg->paths);
}

bool
traj_planning_msg__msg__PathList__are_equal(const traj_planning_msg__msg__PathList * lhs, const traj_planning_msg__msg__PathList * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // paths
  if (!nav_msgs__msg__Path__Sequence__are_equal(
      &(lhs->paths), &(rhs->paths)))
  {
    return false;
  }
  return true;
}

bool
traj_planning_msg__msg__PathList__copy(
  const traj_planning_msg__msg__PathList * input,
  traj_planning_msg__msg__PathList * output)
{
  if (!input || !output) {
    return false;
  }
  // paths
  if (!nav_msgs__msg__Path__Sequence__copy(
      &(input->paths), &(output->paths)))
  {
    return false;
  }
  return true;
}

traj_planning_msg__msg__PathList *
traj_planning_msg__msg__PathList__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  traj_planning_msg__msg__PathList * msg = (traj_planning_msg__msg__PathList *)allocator.allocate(sizeof(traj_planning_msg__msg__PathList), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(traj_planning_msg__msg__PathList));
  bool success = traj_planning_msg__msg__PathList__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
traj_planning_msg__msg__PathList__destroy(traj_planning_msg__msg__PathList * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    traj_planning_msg__msg__PathList__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
traj_planning_msg__msg__PathList__Sequence__init(traj_planning_msg__msg__PathList__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  traj_planning_msg__msg__PathList * data = NULL;

  if (size) {
    data = (traj_planning_msg__msg__PathList *)allocator.zero_allocate(size, sizeof(traj_planning_msg__msg__PathList), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = traj_planning_msg__msg__PathList__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        traj_planning_msg__msg__PathList__fini(&data[i - 1]);
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
traj_planning_msg__msg__PathList__Sequence__fini(traj_planning_msg__msg__PathList__Sequence * array)
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
      traj_planning_msg__msg__PathList__fini(&array->data[i]);
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

traj_planning_msg__msg__PathList__Sequence *
traj_planning_msg__msg__PathList__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  traj_planning_msg__msg__PathList__Sequence * array = (traj_planning_msg__msg__PathList__Sequence *)allocator.allocate(sizeof(traj_planning_msg__msg__PathList__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = traj_planning_msg__msg__PathList__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
traj_planning_msg__msg__PathList__Sequence__destroy(traj_planning_msg__msg__PathList__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    traj_planning_msg__msg__PathList__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
traj_planning_msg__msg__PathList__Sequence__are_equal(const traj_planning_msg__msg__PathList__Sequence * lhs, const traj_planning_msg__msg__PathList__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!traj_planning_msg__msg__PathList__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
traj_planning_msg__msg__PathList__Sequence__copy(
  const traj_planning_msg__msg__PathList__Sequence * input,
  traj_planning_msg__msg__PathList__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(traj_planning_msg__msg__PathList);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    traj_planning_msg__msg__PathList * data =
      (traj_planning_msg__msg__PathList *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!traj_planning_msg__msg__PathList__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          traj_planning_msg__msg__PathList__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!traj_planning_msg__msg__PathList__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
