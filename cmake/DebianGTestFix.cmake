include(ExternalProject)

execute_process(COMMAND ${LSB_RELEASE} -cs 
                OUTPUT_VARIABLE LSB_CODENAME 
                OUTPUT_STRIP_TRAILING_WHITESPACE)
                
if(LSB_CODENAME MATCHES stretch)
	set(GTEST_SOURCE_DIR /usr/src/googletest/googletest)
elseif(LSB_CODENAME MATCHES jessie)
	set(GTEST_SOURCE_DIR /usr/src/gtest)
else()
	message(FATAL_ERROR "Could not identify Debian distribution!")
endif()

set(GTEST_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/googletest-build)
add_subdirectory(${GTEST_SOURCE_DIR} ${GTEST_BINARY_DIR})
set(GTEST_INCLUDE_DIRS ${GTEST_SOURCE_DIR}/include)
set(GTEST_LIBRARIES gtest gtest_main)
