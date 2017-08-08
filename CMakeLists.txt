cmake_minimum_required(VERSION 3.0.0)
project(h5++
    LANGUAGES CXX C
    VERSION 0.0.1
    )

include(CTest)
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




#add_custom_target(html)
#add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(test)
