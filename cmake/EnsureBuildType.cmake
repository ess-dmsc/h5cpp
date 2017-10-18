if (NOT CMAKE_BUILD_TYPE)
    message(STATUS "Build type was not set. Using Relese mode.")
    set(CMAKE_BUILD_TYPE "Release")
endif()

#
# On linux it is mandatory to provide a build type during configuration
#
if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "We only support single configuration builds!")
    message(FATAL_ERROR "CMAKE_BUILD_TYPE must be provided during configuration")
endif()
