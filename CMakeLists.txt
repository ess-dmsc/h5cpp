cmake_minimum_required(VERSION 3.0.0)
project(h5cpp
  LANGUAGES CXX C
  VERSION 0.0.5
  )

set(EXTRA_MODULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${EXTRA_MODULES_DIR})

#=============================================================================
# Conan
#=============================================================================
option(WITH_CONAN "Enable dependency build with conan" OFF)
set(CONAN_FILE "conanfile_default.txt" CACHE STRING "The conanfile to use for the build")
if(WITH_CONAN)
	include(${EXTRA_MODULES_DIR}/ConanSetup.cmake)
	conan_cmake_run(CONANFILE ${CONAN_FILE}
		BASIC_SETUP KEEP_RPATHS
		BUILD outdated)
elseif(EXISTS ${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
	message(STATUS "Using existing conanbuildinfo.cmake file")
	include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
	conan_basic_setup(KEEP_RPATHS)
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
include(${EXTRA_MODULES_DIR}/CompilerConfig.cmake)
include(${EXTRA_MODULES_DIR}/MPIConfig.cmake)
include(${EXTRA_MODULES_DIR}/HDF5LibraryConfig.cmake)
include(${EXTRA_MODULES_DIR}/BoostLibraryConfig.cmake)

add_custom_target(html)
add_subdirectory(src)
add_subdirectory(doc)

#=============================================================================
# unit tests if GTest if present
#=============================================================================
include(${EXTRA_MODULES_DIR}/FindGTestFix.cmake)
if (GTest_FOUND)
  add_subdirectory(test)
else()
  message(WARNING "GTest not found. No tests will be built.")
endif()

#=============================================================================
# create package file
#=============================================================================
set(WITH_SWMR OFF CACHE BOOL "enable SWMR support")
set(WITH_VDS OFF CACHE BOOL "enable VDS support")
if(HDF5_VERSION VERSION_GREATER 1.10.0 OR HDF5_VERSION VERSION_EQUAL 1.10.0)
    set(WITH_SWMR ON)
    set(WITH_VDS ON)
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
