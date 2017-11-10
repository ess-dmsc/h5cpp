# Install script for directory: /home/bdv/dev/h5cpp/src/include/h5cpp/node

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/h5cpp/node" TYPE FILE FILES
    "/home/bdv/dev/h5cpp/src/include/h5cpp/node/dataset.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/node/group_view.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/node/group.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/node/link_view.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/node/link.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/node/node.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/node/node_iterator.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/node/link_iterator.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/node/node_view.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/node/functions.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/node/types.hpp"
    )
endif()

