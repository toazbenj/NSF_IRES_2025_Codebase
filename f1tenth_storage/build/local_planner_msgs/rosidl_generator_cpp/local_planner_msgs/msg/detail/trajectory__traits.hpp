// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from local_planner_msgs:msg/Trajectory.idl
// generated code does not contain a copyright notice

#ifndef LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY__TRAITS_HPP_
#define LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "local_planner_msgs/msg/detail/trajectory__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'path'
#include "nav_msgs/msg/detail/path__traits.hpp"
// Member 'speed'
#include "std_msgs/msg/detail/float64__traits.hpp"

namespace local_planner_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Trajectory & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: path
  {
    out << "path: ";
    to_flow_style_yaml(msg.path, out);
    out << ", ";
  }

  // member: speed
  {
    out << "speed: ";
    to_flow_style_yaml(msg.speed, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Trajectory & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: path
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "path:\n";
    to_block_style_yaml(msg.path, out, indentation + 2);
  }

  // member: speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed:\n";
    to_block_style_yaml(msg.speed, out, indentation + 2);
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Trajectory & msg, bool use_flow_style = false)
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
  const local_planner_msgs::msg::Trajectory & msg,
  std::ostream & out, size_t indentation = 0)
{
  local_planner_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use local_planner_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const local_planner_msgs::msg::Trajectory & msg)
{
  return local_planner_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<local_planner_msgs::msg::Trajectory>()
{
  return "local_planner_msgs::msg::Trajectory";
}

template<>
inline const char * name<local_planner_msgs::msg::Trajectory>()
{
  return "local_planner_msgs/msg/Trajectory";
}

template<>
struct has_fixed_size<local_planner_msgs::msg::Trajectory>
  : std::integral_constant<bool, has_fixed_size<nav_msgs::msg::Path>::value && has_fixed_size<std_msgs::msg::Float64>::value && has_fixed_size<std_msgs::msg::Header>::value> {};

template<>
struct has_bounded_size<local_planner_msgs::msg::Trajectory>
  : std::integral_constant<bool, has_bounded_size<nav_msgs::msg::Path>::value && has_bounded_size<std_msgs::msg::Float64>::value && has_bounded_size<std_msgs::msg::Header>::value> {};

template<>
struct is_message<local_planner_msgs::msg::Trajectory>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // LOCAL_PLANNER_MSGS__MSG__DETAIL__TRAJECTORY__TRAITS_HPP_
