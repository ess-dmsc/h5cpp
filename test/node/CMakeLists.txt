set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(test_sources node_test.cpp
                 functions_test.cpp
                 type_test.cpp
                 link_type_test.cpp
                 link_test.cpp
                 group_test.cpp
                 dataset_test.cpp
                 group_node_iteration_test.cpp
                 dataset_partial_io_test.cpp
                 dataset_extent_test.cpp
                 dataset_array_type_io.cpp
                 dataset_dynamic_type_io.cpp
                 dataset_const_data.cpp
                 dataset_vlen_array_io.cpp
                 dataset_fixed_string_io.cpp
                 dataset_variable_string_io.cpp
                 get_test.cpp
                 chunked_dataset_test.cpp
                 recursive_node_iterator_test.cpp
                 is_group_is_dataset_test.cpp
                 get_group_and_dataset_test.cpp
                 symbolic_link_creation_test.cpp
                 dataset_bool_io.cpp
                 dataset_h5py_string_compat_test.cpp
                 link_target_test.cpp
                 dataset_io_speed_test.cpp
                 virtual_dataset_test.cpp
                 dataset_direct_chunk_test.cpp)

add_executable(node_test ${test_sources})
target_link_libraries(
   node_test
   PRIVATE
       h5cpp
       hdf5::hdf5
       example_lib
)
target_compile_definitions(node_test PRIVATE CATCH_CONFIG_ENABLE_BENCHMARKING)
catch_discover_tests(node_test)
