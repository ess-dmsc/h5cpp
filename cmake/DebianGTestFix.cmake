include(ExternalProject)

set(GTEST_SOURCE_DIR /usr/src/googletest/googletest)
set(GTEST_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/googletest-build)
add_subdirectory(${GTEST_SOURCE_DIR} ${GTEST_BINARY_DIR})
set(GTEST_INCLUDE_DIRS ${GTEST_SOURCE_DIR}/include)
set(GTEST_LIBRARIES gtest gtest_main)
