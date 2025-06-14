// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from traj_planning_msg:msg/PathList.idl
// generated code does not contain a copyright notice

#ifndef TRAJ_PLANNING_MSG__MSG__DETAIL__PATH_LIST__STRUCT_HPP_
#define TRAJ_PLANNING_MSG__MSG__DETAIL__PATH_LIST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'paths'
#include "traj_planning_msg/msg/detail/speed_path__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__traj_planning_msg__msg__PathList __attribute__((deprecated))
#else
# define DEPRECATED__traj_planning_msg__msg__PathList __declspec(deprecated)
#endif

namespace traj_planning_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct PathList_
{
  using Type = PathList_<ContainerAllocator>;

  explicit PathList_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit PathList_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _paths_type =
    std::vector<traj_planning_msg::msg::SpeedPath_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<traj_planning_msg::msg::SpeedPath_<ContainerAllocator>>>;
  _paths_type paths;

  // setters for named parameter idiom
  Type & set__paths(
    const std::vector<traj_planning_msg::msg::SpeedPath_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<traj_planning_msg::msg::SpeedPath_<ContainerAllocator>>> & _arg)
  {
    this->paths = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    traj_planning_msg::msg::PathList_<ContainerAllocator> *;
  using ConstRawPtr =
    const traj_planning_msg::msg::PathList_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<traj_planning_msg::msg::PathList_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<traj_planning_msg::msg::PathList_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      traj_planning_msg::msg::PathList_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<traj_planning_msg::msg::PathList_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      traj_planning_msg::msg::PathList_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<traj_planning_msg::msg::PathList_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<traj_planning_msg::msg::PathList_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<traj_planning_msg::msg::PathList_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__traj_planning_msg__msg__PathList
    std::shared_ptr<traj_planning_msg::msg::PathList_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__traj_planning_msg__msg__PathList
    std::shared_ptr<traj_planning_msg::msg::PathList_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const PathList_ & other) const
  {
    if (this->paths != other.paths) {
      return false;
    }
    return true;
  }
  bool operator!=(const PathList_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct PathList_

// alias to use template instance with default allocator
using PathList =
  traj_planning_msg::msg::PathList_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace traj_planning_msg

#endif  // TRAJ_PLANNING_MSG__MSG__DETAIL__PATH_LIST__STRUCT_HPP_
