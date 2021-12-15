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

option(H5CPP_BUILD_SHARED "Build h5cpp as a shared library" ${BUILD_SHARED_LIBS})
if(H5CPP_BUILD_SHARED)
  set(BUILD_SHARED_LIBS ON)
endif()
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
   list(PREPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
elseif(${H5CPP_CONAN} MATCHES "MANUAL")
  if(EXISTS "${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    include("${CMAKE_BINARY_DIR}/conanbuildinfo.cmake")
    conan_basic_setup(NO_OUTPUT_DIRS KEEP_RPATHS)
    list(PREPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
  else()
    message(FATAL_ERROR "H5CPP_CONAN set to MANUAL but no file named conanbuildinfo.cmake found in build directory")
  endif()
elseif(NOT ${H5CPP_CONAN} MATCHES "DISABLE")
  message(FATAL_ERROR "Unrecognised option for H5CPP_CONAN (${H5CPP_CONAN}), use AUTO, MANUAL or DISABLE")
endif()

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
  h5cpp_message(STATUS "Using Boost library for filesystem")
else() 
  # if we do not use Boost we have to ensure a C++ standard of at least 2017
  # since we require the std::filesystem API
  set(CMAKE_CXX_STANDARD 17)
  h5cpp_message(STATUS "Using std library for filesystem")
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
