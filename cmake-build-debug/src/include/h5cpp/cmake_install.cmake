# Install script for directory: /home/bdv/dev/h5cpp/src/include/h5cpp

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
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/h5cpp" TYPE FILE FILES
    "/home/bdv/dev/h5cpp/src/include/h5cpp/object_handle.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/windows.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/types.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/path.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/iterator_config.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/iterator.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/object_id.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/hdf5.hpp"
    "/home/bdv/dev/h5cpp/src/include/h5cpp/hdf5_capi.hpp"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/bdv/dev/h5cpp/cmake-build-debug/src/include/h5cpp/property/cmake_install.cmake")
  include("/home/bdv/dev/h5cpp/cmake-build-debug/src/include/h5cpp/dataspace/cmake_install.cmake")
  include("/home/bdv/dev/h5cpp/cmake-build-debug/src/include/h5cpp/datatype/cmake_install.cmake")
  include("/home/bdv/dev/h5cpp/cmake-build-debug/src/include/h5cpp/node/cmake_install.cmake")
  include("/home/bdv/dev/h5cpp/cmake-build-debug/src/include/h5cpp/file/cmake_install.cmake")
  include("/home/bdv/dev/h5cpp/cmake-build-debug/src/include/h5cpp/attribute/cmake_install.cmake")
  include("/home/bdv/dev/h5cpp/cmake-build-debug/src/include/h5cpp/error/cmake_install.cmake")
  include("/home/bdv/dev/h5cpp/cmake-build-debug/src/include/h5cpp/filter/cmake_install.cmake")

endif()

