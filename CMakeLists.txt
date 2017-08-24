cmake_minimum_required(VERSION 3.0.0)
project(h5++
    LANGUAGES CXX C
    VERSION 0.0.1
    )

include(CTest)
option(COV "Enable code coverage test for unit tests (if possible)." OFF)

#=============================================================================
# setting up conan for use from within cmake
#=============================================================================
set(WITH_CONAN OFF CACHE BOOL "Enable dependency build with conan")

if(WITH_CONAN)
	include(cmake/ConanSetup.cmake)
	
	conan_cmake_run(CONANFILE conanfile.txt
		            BASIC_SETUP
		            BUILD missing)
endif()

if(EXISTS ${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
    message(STATUS "Using existing conanbuildinfo.cmake file")
    include(${PROJECT_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
endif()


#=============================================================================
# some general configuration
#=============================================================================
include(cmake/InstallConfig.cmake)
include(cmake/OutputDirConfig.cmake)
include(cmake/EnsureBuildType.cmake)
include(cmake/WindowsUtils.cmake)

#=============================================================================
# Internal compiler options
#=============================================================================
# C++ standard
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
if(NOT CMAKE_CXX_STANDARD OR CMAKE_CXX_STANDARD LESS 11)
  set(CMAKE_CXX_STANDARD 11)
endif()

#=============================================================================
# compiler and library configuration
#=============================================================================
include(cmake/CompilerConfig.cmake)
include(cmake/HDF5LibraryConfig.cmake)
include(cmake/BoostLibraryConfig.cmake)




add_custom_target(html)
add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(test)
