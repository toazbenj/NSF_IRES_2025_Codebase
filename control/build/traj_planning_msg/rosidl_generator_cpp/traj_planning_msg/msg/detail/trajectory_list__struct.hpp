// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from traj_planning_msg:msg/TrajectoryList.idl
// generated code does not contain a copyright notice

#ifndef TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY_LIST__STRUCT_HPP_
#define TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY_LIST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'paths'
#include "traj_planning_msg/msg/detail/trajectory__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__traj_planning_msg__msg__TrajectoryList __attribute__((deprecated))
#else
# define DEPRECATED__traj_planning_msg__msg__TrajectoryList __declspec(deprecated)
#endif

namespace traj_planning_msg
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct TrajectoryList_
{
  using Type = TrajectoryList_<ContainerAllocator>;

  explicit TrajectoryList_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit TrajectoryList_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _paths_type =
    std::vector<traj_planning_msg::msg::Trajectory_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<traj_planning_msg::msg::Trajectory_<ContainerAllocator>>>;
  _paths_type paths;

  // setters for named parameter idiom
  Type & set__paths(
    const std::vector<traj_planning_msg::msg::Trajectory_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<traj_planning_msg::msg::Trajectory_<ContainerAllocator>>> & _arg)
  {
    this->paths = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    traj_planning_msg::msg::TrajectoryList_<ContainerAllocator> *;
  using ConstRawPtr =
    const traj_planning_msg::msg::TrajectoryList_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<traj_planning_msg::msg::TrajectoryList_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<traj_planning_msg::msg::TrajectoryList_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      traj_planning_msg::msg::TrajectoryList_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<traj_planning_msg::msg::TrajectoryList_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      traj_planning_msg::msg::TrajectoryList_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<traj_planning_msg::msg::TrajectoryList_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<traj_planning_msg::msg::TrajectoryList_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<traj_planning_msg::msg::TrajectoryList_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__traj_planning_msg__msg__TrajectoryList
    std::shared_ptr<traj_planning_msg::msg::TrajectoryList_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__traj_planning_msg__msg__TrajectoryList
    std::shared_ptr<traj_planning_msg::msg::TrajectoryList_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const TrajectoryList_ & other) const
  {
    if (this->paths != other.paths) {
      return false;
    }
    return true;
  }
  bool operator!=(const TrajectoryList_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct TrajectoryList_

// alias to use template instance with default allocator
using TrajectoryList =
  traj_planning_msg::msg::TrajectoryList_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace traj_planning_msg

#endif  // TRAJ_PLANNING_MSG__MSG__DETAIL__TRAJECTORY_LIST__STRUCT_HPP_
