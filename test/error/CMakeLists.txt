set(test_sources
    descriptor_test.cpp
    h5c_error_test.cpp
    error_test.cpp)

add_executable(error_test ${test_sources})
target_link_libraries(error_test h5cpp)
catch_discover_tests(error_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
