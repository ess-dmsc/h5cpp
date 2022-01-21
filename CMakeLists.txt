cmake_minimum_required(VERSION 3.10)
project(h5cpp
    LANGUAGES CXX C
      # VERSION 0.4.1
      # documentation for VERSION with one '.' is stored as v:latest (see doc/conf.py.in)
      VERSION 0.5
    )


#=============================================================================
# Augment CMake with our custom scripts
#=============================================================================
set(EXTRA_MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${EXTRA_MODULES_DIR})

if (NOT DEFINED BUILD_SHARED_LIBS)
  set(BUILD_SHARED_LIBS ON)
endif()
option(H5CPP_BUILD_SHARED "Build h5cpp as a shared library" ${BUILD_SHARED_LIBS})
if (NOT H5CPP_BUILD_SHARED)
  set(BUILD_SHARED_LIBS OFF)
endif()
option(H5CPP_LOCAL_MODULES "Build h5cpp using cmake local modules first")

#=============================================================================
# Conan
#=============================================================================
set(H5CPP_CONAN "AUTO" CACHE STRING "conan options AUTO (conan must be in path), MANUAL (expects conanbuildinfo.cmake in build directory) or DISABLE")
set(H5CPP_CONAN_PROFILE "default" CACHE STRING "Name of conan profile to use, uses default by default")
set(H5CPP_CONAN_FILE "conanfile_ess.txt" CACHE STRING "The conanfile to use for the build")

if(${H5CPP_CONAN} MATCHES "AUTO")
  include(${EXTRA_MODULES_DIR}/ConanSetup.cmake)
  conan_cmake_run(CONANFILE ${H5CPP_CONAN_FILE}
      PROFILE ${H5CPP_CONAN_PROFILE}
      BASIC_SETUP NO_OUTPUT_DIRS KEEP_RPATHS
      BUILD_TYPE "None"
      BUILD outdated)
  if(H5CPP_LOCAL_MODULES)
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
  else()
    list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_BINARY_DIR})
  endif()
elseif(${H5CPP_CONAN} MATCHES "MANUAL")
  if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    conan_basic_setup(NO_OUTPUT_DIRS KEEP_RPATHS)
    if(H5CPP_LOCAL_MODULES)
      list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
    else()
      list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_BINARY_DIR})
    endif()
  else()
    message(FATAL_ERROR "H5CPP_CONAN set to MANUAL but no file named conanbuildinfo.cmake found in build directory")
  endif()
elseif(NOT ${H5CPP_CONAN} MATCHES "DISABLE")
  message(FATAL_ERROR "Unrecognised option for H5CPP_CONAN (${H5CPP_CONAN}), use AUTO, MANUAL or DISABLE")
endif()

#=============================================================================
# contrib extensions
#=============================================================================
set(H5CPP_ENABLE_NEXUS "true" CACHE BOOL "enable support or Nexus types")
set(H5CPP_ENABLE_STL "true" CACHE BOOL "enable STL support for H5CPP")

#=============================================================================
# General configuration
#=============================================================================

include(${EXTRA_MODULES_DIR}/EnsureBuildType.cmake)
include(${EXTRA_MODULES_DIR}/CoverageReports.cmake)
include(${EXTRA_MODULES_DIR}/InstallConfig.cmake)
include(${EXTRA_MODULES_DIR}/OutputDirConfig.cmake)
include(${EXTRA_MODULES_DIR}/WindowsUtils.cmake)
include(${EXTRA_MODULES_DIR}/PackageConfig.cmake)
include(${EXTRA_MODULES_DIR}/BuildInfo.cmake)
include(Sphinx)
include(utilities)
include(DoxygenUtilities)

#=============================================================================
# compiler and library configuration
#=============================================================================
option(H5CPP_WITH_BOOST "enable Boost filesystem support" ON)
if(H5CPP_WITH_BOOST)
  find_package(Boost 1.41 COMPONENTS filesystem system REQUIRED)
else()
  # if we do not use Boost we have to ensure a C++ standard of at least 2017
  # since we require the std::filesystem API
  set(CMAKE_CXX_STANDARD 17)
endif()

include(${EXTRA_MODULES_DIR}/CompilerConfig.cmake)
include(${EXTRA_MODULES_DIR}/MPIConfig.cmake)
include(${EXTRA_MODULES_DIR}/HDF5LibraryConfig.cmake)

if(H5CPP_BUILD_SHARED)
  h5cpp_message(STATUS "Building shared library")
else()
  h5cpp_message(STATUS "Building static library")
endif()
if (H5CPP_WITH_MPI)
  h5cpp_message(STATUS "Building with MPI support")
endif()
if(H5CPP_WITH_BOOST)
  h5cpp_message(STATUS "Using Boost library for filesystem")
else()
  h5cpp_message(STATUS "Using std library for filesystem")
endif()

find_package(Threads REQUIRED)
find_package(SZIP)
find_package(ZLIB REQUIRED)

add_subdirectory(src)
option(H5CPP_BUILD_DOCS "Build documentation" ON)
if(H5CPP_BUILD_DOCS)
  add_subdirectory(doc)
endif()

#=============================================================================
# install the examples directory to the documentation directory
#=============================================================================
install(DIRECTORY examples
        DESTINATION ${CMAKE_INSTALL_DOCDIR})

#=============================================================================
# unit tests if GTest if present
#=============================================================================
option(H5CPP_DISABLE_TESTS "Disable building unit tests" OFF)
if(NOT H5CPP_DISABLE_TESTS)
    find_package(Catch2 REQUIRED)
    enable_testing()
    include(Catch)
    add_subdirectory(test)
endif()

#=============================================================================
# create package file
#=============================================================================
option(H5CPP_WITH_SWMR "enable SWMR support" OFF)
option(H5CPP_WITH_VDS "enable VDS support" OFF)
if(HDF5_VERSION VERSION_GREATER 1.10.0 OR HDF5_VERSION VERSION_EQUAL 1.10.0)
  set(H5CPP_WITH_SWMR ON)
  set(H5CPP_WITH_VDS ON)
endif()

#
# create and install the version file
#
write_basic_package_version_file(
    ${PROJECT_BINARY_DIR}/${PACKAGE_VERSION_FILE_NAME}
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion)

install(FILES ${PROJECT_BINARY_DIR}/${PACKAGE_VERSION_FILE_NAME}
    DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
    COMPONENT development)

#
# create and install the package file
#
configure_file("${PACKAGE_CONFIG_FILE_NAME}.in" ${PACKAGE_CONFIG_FILE_NAME} @ONLY)
install(FILES ${PROJECT_BINARY_DIR}/${PACKAGE_CONFIG_FILE_NAME}
    DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
    COMPONENT development)

#
# uninstall target
#
if(NOT TARGET uninstall)
  configure_file(
      "${EXTRA_MODULES_DIR}/cmake_uninstall.cmake.in"
      "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
      IMMEDIATE @ONLY)

  add_custom_target(uninstall
      COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)
endif()
