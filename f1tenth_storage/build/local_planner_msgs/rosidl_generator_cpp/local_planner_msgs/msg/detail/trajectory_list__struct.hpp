// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from local_planner_msgs:msg/TrajectoryList.idl
// generated code does not contain a copyright notice

#ifndef LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY_LIST__STRUCT_HPP_
#define LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY_LIST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'paths'
#include "local_planner_msgs/msg/detail/trajectory__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__local_planner_msgs__msg__TrajectoryList __attribute__((deprecated))
#else
# define DEPRECATED__local_planner_msgs__msg__TrajectoryList __declspec(deprecated)
#endif

namespace local_planner_msgs
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
    std::vector<local_planner_msgs::msg::Trajectory_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<local_planner_msgs::msg::Trajectory_<ContainerAllocator>>>;
  _paths_type paths;

  // setters for named parameter idiom
  Type & set__paths(
    const std::vector<local_planner_msgs::msg::Trajectory_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<local_planner_msgs::msg::Trajectory_<ContainerAllocator>>> & _arg)
  {
    this->paths = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    local_planner_msgs::msg::TrajectoryList_<ContainerAllocator> *;
  using ConstRawPtr =
    const local_planner_msgs::msg::TrajectoryList_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<local_planner_msgs::msg::TrajectoryList_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<local_planner_msgs::msg::TrajectoryList_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      local_planner_msgs::msg::TrajectoryList_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<local_planner_msgs::msg::TrajectoryList_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      local_planner_msgs::msg::TrajectoryList_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<local_planner_msgs::msg::TrajectoryList_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<local_planner_msgs::msg::TrajectoryList_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<local_planner_msgs::msg::TrajectoryList_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__local_planner_msgs__msg__TrajectoryList
    std::shared_ptr<local_planner_msgs::msg::TrajectoryList_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__local_planner_msgs__msg__TrajectoryList
    std::shared_ptr<local_planner_msgs::msg::TrajectoryList_<ContainerAllocator> const>
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
  local_planner_msgs::msg::TrajectoryList_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace local_planner_msgs

#endif  // LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY_LIST__STRUCT_HPP_
