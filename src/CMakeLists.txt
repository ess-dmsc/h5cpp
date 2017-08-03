cmake_minimum_required(VERSION 2.8.11 FATAL_ERROR)
project(h5cpp CXX)

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
include(GNUInstallDirs)

#=========================================================
# Internal compiler options
#=========================================================
# C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_CXX_STANDARD OR CMAKE_CXX_STANDARD LESS 11)
  set(CMAKE_CXX_STANDARD 11)
endif()

# Warnings
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

#=========================================================
# Function for deducing include dirs
# retname - name of parent variable to fill
# file_list - list of dirs, pass to fn as "${list_var}"
#=========================================================
function(dirs_of retname file_list)
  set(dlist "")
  foreach (_file ${file_list})
      get_filename_component(_dir ${_file} PATH)
      list (APPEND dlist ${_dir})
  endforeach()
  list(REMOVE_DUPLICATES dlist)
  set (${retname} ${dlist} PARENT_SCOPE)
endfunction(dirs_of)

# HDF5
set(HDF5_USE_SHARED_LIBRARIES ON)
find_package(HDF5 1.8.15 COMPONENTS C REQUIRED)
add_library(HDF5 INTERFACE IMPORTED)
set_property(TARGET HDF5 PROPERTY
    INTERFACE_INCLUDE_DIRECTORIES ${HDF5_INCLUDE_DIRS})

# Boost
SET(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

file(GLOB ${PROJECT_NAME}_sources *.cpp)
file(GLOB ${PROJECT_NAME}_headers *.h)
dirs_of(${PROJECT_NAME}_include_dirs "${${PROJECT_NAME}_headers}")

add_executable(
  ${PROJECT_NAME}
  ${${PROJECT_NAME}_sources}
  ${${PROJECT_NAME}_headers}
)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE ${HDF5_INCLUDE_DIRS}
)

target_link_libraries(
  ${PROJECT_NAME}
  ${CMAKE_THREAD_LIBS_INIT}
  ${HDF5_LIBRARIES}
  ${Boost_LIBRARIES}
)
