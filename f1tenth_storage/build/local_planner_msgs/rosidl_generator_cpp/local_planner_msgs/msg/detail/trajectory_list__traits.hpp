// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from local_planner_msgs:msg/TrajectoryList.idl
// generated code does not contain a copyright notice

#ifndef LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY_LIST__TRAITS_HPP_
#define LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY_LIST__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "local_planner_msgs/msg/detail/trajectory_list__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'paths'
#include "local_planner_msgs/msg/detail/trajectory__traits.hpp"

namespace local_planner_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const TrajectoryList & msg,
  std::ostream & out)
{
  out << "{";
  // member: paths
  {
    if (msg.paths.size() == 0) {
      out << "paths: []";
    } else {
      out << "paths: [";
      size_t pending_items = msg.paths.size();
      for (auto item : msg.paths) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const TrajectoryList & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: paths
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.paths.size() == 0) {
      out << "paths: []\n";
    } else {
      out << "paths:\n";
      for (auto item : msg.paths) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const TrajectoryList & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace local_planner_msgs

namespace rosidl_generator_traits
{

[[deprecated("use local_planner_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const local_planner_msgs::msg::TrajectoryList & msg,
  std::ostream & out, size_t indentation = 0)
{
  local_planner_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use local_planner_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const local_planner_msgs::msg::TrajectoryList & msg)
{
  return local_planner_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<local_planner_msgs::msg::TrajectoryList>()
{
  return "local_planner_msgs::msg::TrajectoryList";
}

template<>
inline const char * name<local_planner_msgs::msg::TrajectoryList>()
{
  return "local_planner_msgs/msg/TrajectoryList";
}

template<>
struct has_fixed_size<local_planner_msgs::msg::TrajectoryList>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<local_planner_msgs::msg::TrajectoryList>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<local_planner_msgs::msg::TrajectoryList>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY_LIST__TRAITS_HPP_
