
set(test_sources 
    ObjectHandleDefault.cpp
    object_handle_test.cpp
    file_object_handle_test.cpp
    datatype_object_handle_test.cpp
    dataspace_object_handle_test.cpp
    group_object_handle_test.cpp
    dataset_object_handle_test.cpp
    attribute_object_handle_test.cpp
    property_objects_handle_test.cpp
    error_objects_handle_test.cpp
    test_environment.cpp
    iteration_index_test.cpp
    iteration_order_test.cpp
    object_id_test.cpp
    iterator_test.cpp
    path_test.cpp
    version_test.cpp)

if(WIN32)
  add_executable(core_test WIN32 ${test_sources})
else()
  add_executable(core_test ${test_sources})
endif()
target_link_libraries(
    core_test
    PRIVATE
        h5cpp
	Catch2::Catch2
        hdf5::hdf5
        $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,11.0>>:stdc++fs>
)

catch_discover_tests(core_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
