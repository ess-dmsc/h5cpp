cmake_minimum_required(VERSION 3.0.0)
project(h5cpp
    LANGUAGES CXX C
    VERSION 0.0.1
    )

set(EXTRA_MODULES_DIR ${PROJECT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${EXTRA_MODULES_DIR})

option(COV "Enable code coverage test for unit tests (if possible)." OFF)
    
#=============================================================================
# enable MPI support if required 
#=============================================================================
set(WITH_MPI OFF CACHE BOOL "Enable MPI support")

if(WITH_MPI AND (CMAKE_SYSTEM_NAME MATCHES Windows))
    message(FATAL_ERROR "MPI not supported on the Windows platform!")
endif()

if(WITH_MPI AND (CMAKE_SYSTEM_NAME MATCHES Darwin))
    message(FATAL_ERROR "MPI not supported for OSX")
endif()
 

#=============================================================================
# setting up conan for use from within cmake
#=============================================================================
set(WITH_CONAN OFF CACHE BOOL "Enable dependency build with conan")

if(WITH_CONAN)
  include(${EXTRA_MODULES_DIR}/ConanSetup.cmake)
	
	conan_cmake_run(CONANFILE conanfile.txt
		            BASIC_SETUP
		            BUILD missing)
endif()

if(EXISTS ${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
    message(STATUS "Using existing conanbuildinfo.cmake file")
    include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup(SKIP_RPATH)
endif()


#=============================================================================
# some general configuration
#=============================================================================

include(${EXTRA_MODULES_DIR}/InstallConfig.cmake)
include(${EXTRA_MODULES_DIR}/OutputDirConfig.cmake)
include(${EXTRA_MODULES_DIR}/EnsureBuildType.cmake)
include(${EXTRA_MODULES_DIR}/WindowsUtils.cmake)
include(${EXTRA_MODULES_DIR}/PackageConfig.cmake)
include(${EXTRA_MODULES_DIR}/BuildInfo.cmake)
include(Sphinx)
include(utilities)
include(DoxygenUtilities)

#=============================================================================
# compiler and library configuration
#=============================================================================
if(WITH_MPI)
    include(${EXTRA_MODULES_DIR}/MPIConfig.cmake)
endif()
include(${EXTRA_MODULES_DIR}/CompilerConfig.cmake)
include(${EXTRA_MODULES_DIR}/HDF5LibraryConfig.cmake)
include(${EXTRA_MODULES_DIR}/BoostLibraryConfig.cmake)


add_custom_target(html)
add_subdirectory(src)
add_subdirectory(doc)
add_subdirectory(test)

#=============================================================================
# create package file
#=============================================================================

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
configure_file(${PACKAGE_CONFIG_FILE_NAME} ${PACKAGE_CONFIG_FILE_NAME} COPYONLY)
install(FILES ${PROJECT_BINARY_DIR}/${PACKAGE_CONFIG_FILE_NAME}
	    DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
	    COMPONENT development)

add_custom_target(BuildScripts SOURCES
  ${PROJECT_SOURCE_DIR}/conanfile.txt
  ${PROJECT_SOURCE_DIR}/Jenkinsfile
  ${PROJECT_SOURCE_DIR}/push_to_repo.sh)
