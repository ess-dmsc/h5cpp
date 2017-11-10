# Install script for directory: /home/bdv/dev/h5cpp/src/include/h5cpp/property

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/h5cpp/property" TYPE FILE FILES
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/attribute_creation_list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/class.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/creation_order.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/dataset_access_list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/dataset_creation_list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/dataset_transfer_list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/datatype_access_list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/file_access_list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/file_creation_list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/file_mount_list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/group_access_list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/group_creation_list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/link_access_list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/link_creation_list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/object_creation_list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/string_creation_list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/type_creation_list.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/property/object_copy_list.hpp"
    )
endif()

