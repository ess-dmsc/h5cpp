add_executable(utilities_test array_adapter_test.cpp)
target_link_libraries(
    utilities_test
    PRIVATE
        h5cpp
        hdf5::hdf5
)
catch_discover_tests(utilities_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
