#
# setting up conan to be used directly from within cmake
#

#
# looking up the conan executable itself
#
find_program(CONAN conan)
if(CONAN MATCHES "CONAN-NONFOUND")
    message(FATAL_ERROR "Could not find conan executable to install dependencies")
endif()

#
# adding required files to the build directory (fetch everything from github)
#
if(NOT EXISTS ${PROJECT_BINARY_DIR}/conan.cmake)
    message(STATUS "Downloading conan.cmake file from github")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
         ${PROJECT_BINARY_DIR}/conan.cmake)
endif()

include(${PROJECT_BINARY_DIR}/conan.cmake)
