set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
    ${dir}/property_class.cpp
    ${dir}/property_list.cpp

    ${dir}/attribute_creation.cpp
    ${dir}/creation_order.cpp
    ${dir}/dataset_access.cpp
    ${dir}/dataset_creation.cpp
    ${dir}/dataset_transfer.cpp
    ${dir}/datatype_access.cpp
    ${dir}/file_access.cpp
    ${dir}/file_creation.cpp
    ${dir}/file_mount.cpp
    ${dir}/group_access.cpp
    ${dir}/group_creation.cpp
    ${dir}/link_access.cpp
    ${dir}/link_creation.cpp
    ${dir}/object_copy.cpp
    ${dir}/object_creation.cpp
    ${dir}/string_creation.cpp
    ${dir}/type_creation.cpp
    ${dir}/virtual_data_map.cpp
    )

set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
