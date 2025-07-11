# generated from ament/cmake/core/templates/nameConfig.cmake.in

# prevent multiple inclusion
if(_scan_matching_CONFIG_INCLUDED)
  # ensure to keep the found flag the same
  if(NOT DEFINED scan_matching_FOUND)
    # explicitly set it to FALSE, otherwise CMake will set it to TRUE
    set(scan_matching_FOUND FALSE)
  elseif(NOT scan_matching_FOUND)
    # use separate condition to avoid uninitialized variable warning
    set(scan_matching_FOUND FALSE)
  endif()
  return()
endif()
set(_scan_matching_CONFIG_INCLUDED TRUE)

# output package information
if(NOT scan_matching_FIND_QUIETLY)
  message(STATUS "Found scan_matching: 0.0.0 (${scan_matching_DIR})")
endif()

# warn when using a deprecated package
if(NOT "" STREQUAL "")
  set(_msg "Package 'scan_matching' is deprecated")
  # append custom deprecation text if available
  if(NOT "" STREQUAL "TRUE")
    set(_msg "${_msg} ()")
  endif()
  # optionally quiet the deprecation message
  if(NOT ${scan_matching_DEPRECATED_QUIET})
    message(DEPRECATION "${_msg}")
  endif()
endif()

# flag package as ament-based to distinguish it after being find_package()-ed
set(scan_matching_FOUND_AMENT_PACKAGE TRUE)

# include all config extra files
set(_extras "")
foreach(_extra ${_extras})
  include("${scan_matching_DIR}/${_extra}")
endforeach()
