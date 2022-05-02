set(test_sources attribute_h5py_bool_test.cpp
                 attribute_pniio_bool_test.cpp
                 dataset_h5py_bool_test.cpp
                 dataset_pniio_bool_test.cpp
                 ebool_test.cpp)

add_executable(ebool_test ${test_sources})
target_link_libraries(
    ebool_test
    PRIVATE
        h5cpp
        hdf5::hdf5
)
catch_discover_tests(ebool_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
