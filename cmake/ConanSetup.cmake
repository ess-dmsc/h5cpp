find_program(CONAN_EXEC NAMES conan PATHS ${CONAN_PATH})
if(CONAN_EXEC MATCHES CONAN_EXEC-NOTFOUND)
    message(FATAL_ERROR "Could not find conan executable to install dependencies ${CONAN_PATH}")
else()
    message(STATUS "Found conan: ${CONAN_EXEC}")
    
    #need to add the directory to the path
    get_filename_component(CONAN_EXEC_PATH ${CONAN_EXEC} DIRECTORY)
    message(STATUS "Conan executable found in: ${CONAN_EXEC_PATH}")
    set(ENV{PATH} "$ENV{PATH}:${CONAN_EXEC_PATH}")
endif()

#=============================================================================
# adding required files to the build directory (fetch everything from github)
#=============================================================================
if(NOT EXISTS ${EXTRA_MODULES_DIR}/conan.cmake)
  message(STATUS "Downloading conan.cmake file from github")
  file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/master/conan.cmake"
      ${EXTRA_MODULES_DIR}/conan.cmake)
endif()

include(${EXTRA_MODULES_DIR}/conan.cmake)
