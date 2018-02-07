#=============================================================================
# adding required files to the build directory (fetch everything from github)
#=============================================================================
if(NOT EXISTS ${PROJECT_BINARY_DIR}/conan.cmake)
  message(STATUS "Downloading conan.cmake file from github")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
    ${PROJECT_BINARY_DIR}/conan.cmake)
endif()

include(${PROJECT_BINARY_DIR}/conan.cmake)
