// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from traj_planning_msg:msg/Trajectory.idl
// generated code does not contain a copyright notice

#ifndef TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY__STRUCT_HPP_
#define TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'path'
#include "nav_msgs/msg/detail/path__struct.hpp"
// Member 'speed'
#include "std_msgs/msg/detail/float64__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__traj_planning_msg__msg__Trajectory __attribute__((deprecated))
#else
# define DEPRECATED__traj_planning_msg__msg__Trajectory __declspec(deprecated)
#endif

namespace traj_planning_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Trajectory_
{
  using Type = Trajectory_<ContainerAllocator>;

  explicit Trajectory_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    path(_init),
    speed(_init)
  {
    (void)_init;
  }

  explicit Trajectory_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    path(_alloc, _init),
    speed(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _path_type =
    nav_msgs::msg::Path_<ContainerAllocator>;
  _path_type path;
  using _speed_type =
    std_msgs::msg::Float64_<ContainerAllocator>;
  _speed_type speed;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__path(
    const nav_msgs::msg::Path_<ContainerAllocator> & _arg)
  {
    this->path = _arg;
    return *this;
  }
  Type & set__speed(
    const std_msgs::msg::Float64_<ContainerAllocator> & _arg)
  {
    this->speed = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    traj_planning_msg::msg::Trajectory_<ContainerAllocator> *;
  using ConstRawPtr =
    const traj_planning_msg::msg::Trajectory_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<traj_planning_msg::msg::Trajectory_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<traj_planning_msg::msg::Trajectory_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      traj_planning_msg::msg::Trajectory_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<traj_planning_msg::msg::Trajectory_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      traj_planning_msg::msg::Trajectory_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<traj_planning_msg::msg::Trajectory_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<traj_planning_msg::msg::Trajectory_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<traj_planning_msg::msg::Trajectory_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__traj_planning_msg__msg__Trajectory
    std::shared_ptr<traj_planning_msg::msg::Trajectory_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__traj_planning_msg__msg__Trajectory
    std::shared_ptr<traj_planning_msg::msg::Trajectory_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Trajectory_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->path != other.path) {
      return false;
    }
    if (this->speed != other.speed) {
      return false;
    }
    return true;
  }
  bool operator!=(const Trajectory_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Trajectory_

// alias to use template instance with default allocator
using Trajectory =
  traj_planning_msg::msg::Trajectory_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace traj_planning_msg

#endif  // TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY__STRUCT_HPP_
