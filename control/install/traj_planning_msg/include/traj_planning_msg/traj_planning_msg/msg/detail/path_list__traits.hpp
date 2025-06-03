// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from traj_planning_msg:msg/PathList.idl
// generated code does not contain a copyright notice

#ifndef TRAJ_PLANNING_MSG__MSG__DETAIL__PATH_LIST__TRAITS_HPP_
#define TRAJ_PLANNING_MSG__MSG__DETAIL__PATH_LIST__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "traj_planning_msg/msg/detail/path_list__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'paths'
#include "nav_msgs/msg/detail/path__traits.hpp"

namespace traj_planning_msg
{

namespace msg
{

inline void to_flow_style_yaml(
  const PathList & msg,
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
  const PathList & msg,
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

inline std::string to_yaml(const PathList & msg, bool use_flow_style = false)
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

}  // namespace traj_planning_msg

namespace rosidl_generator_traits
{

[[deprecated("use traj_planning_msg::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const traj_planning_msg::msg::PathList & msg,
  std::ostream & out, size_t indentation = 0)
{
  traj_planning_msg::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use traj_planning_msg::msg::to_yaml() instead")]]
inline std::string to_yaml(const traj_planning_msg::msg::PathList & msg)
{
  return traj_planning_msg::msg::to_yaml(msg);
}

template<>
inline const char * data_type<traj_planning_msg::msg::PathList>()
{
  return "traj_planning_msg::msg::PathList";
}

template<>
inline const char * name<traj_planning_msg::msg::PathList>()
{
  return "traj_planning_msg/msg/PathList";
}

template<>
struct has_fixed_size<traj_planning_msg::msg::PathList>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<traj_planning_msg::msg::PathList>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<traj_planning_msg::msg::PathList>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // TRAJ_PLANNING_MSG__MSG__DETAIL__PATH_LIST__TRAITS_HPP_
