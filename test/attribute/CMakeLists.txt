set(test_sources
    attribute_test.cpp
    attribute_name_access_test.cpp
    attribute_management_test.cpp
    attribute_scalar_io_test.cpp
    attribute_multidim_io_test.cpp
    attribute_fixed_string_io.cpp
    attribute_variable_string_io.cpp
    attribute_h5py_bool_test.cpp
    attribute_pniio_bool_test.cpp)

add_executable(attribute_test ${test_sources})
target_link_libraries(
    attribute_test
    PRIVATE
        h5cpp
        hdf5::hdf5
)
catch_discover_tests(attribute_test)
