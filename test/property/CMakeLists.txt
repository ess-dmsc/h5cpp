set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(test_sources
    ${test_sources}
    ${dir}/property_class_test.cpp
    ${dir}/property_list_test.cpp
    ${dir}/attribute_creation_test.cpp
    ${dir}/chunk_cache_parameters_test.cpp
    ${dir}/creation_order_test.cpp
    ${dir}/dataset_access_test.cpp
    ${dir}/dataset_creation_test.cpp
    ${dir}/dataset_transfer_test.cpp
    ${dir}/datatype_access_test.cpp
    ${dir}/file_access_test.cpp
    ${dir}/file_creation_test.cpp
    ${dir}/file_mount_test.cpp
    ${dir}/group_access_test.cpp
    ${dir}/group_creation_test.cpp
    ${dir}/link_access_test.cpp
    ${dir}/link_creation_test.cpp
    ${dir}/object_copy_test.cpp
    ${dir}/object_creation_test.cpp
    ${dir}/string_creation_test.cpp
    ${dir}/type_creation_test.cpp
    PARENT_SCOPE)
