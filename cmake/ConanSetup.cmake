#
# setting up conan to be used directly from within cmake
#

#
# looking up the conan executable itself
#
find_program(CONAN NAMES conan PATHS ${CONAN_PATH})
if(CONAN MATCHES CONAN-NOTFOUND)
    message(FATAL_ERROR "Could not find conan executable to install dependencies ${CONAN_PATH}")
else()
    message(STATUS "Found conan: ${CONAN}")
    
    #need to add the directory to the path
    get_filename_component(CONAN_EXEC_PATH ${CONAN} DIRECTORY)
    set(ENV{PATH} "$ENV{PATH}:${CONAN_EXEC_PATH}")
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
