
set(test_sources
    utilities.cpp
    property_class_test.cpp
    property_list_test.cpp

    creation_order_test.cpp
    object_creation_test.cpp
    dataset_creation_test.cpp
    type_creation_test.cpp
    group_creation_test.cpp
    file_creation_test.cpp

    link_access_test.cpp
    chunk_cache_parameters_test.cpp
    dataset_access_test.cpp
    datatype_access_test.cpp
    group_access_test.cpp

    string_creation_test.cpp
    attribute_creation_test.cpp
    link_creation_test.cpp

    dataset_transfer_test.cpp
    file_access_test.cpp
    file_mount_test.cpp
    object_copy_test.cpp)

add_executable(properties_test ${test_sources})
target_link_libraries(
    properties_test
    PRIVATE
        h5cpp
        hdf5::hdf5
)
catch_discover_tests(properties_test
                     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME properties_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMAND properties_test)