set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS
    ${dir}/property_class.hpp
    ${dir}/property_list.hpp

    ${dir}/attribute_creation.hpp
    ${dir}/creation_order.hpp
    ${dir}/dataset_access.hpp
    ${dir}/dataset_creation.hpp
    ${dir}/dataset_transfer.hpp
    ${dir}/datatype_access.hpp
    ${dir}/file_access.hpp
    ${dir}/file_creation.hpp
    ${dir}/file_mount.hpp
    ${dir}/group_access.hpp
    ${dir}/group_creation.hpp
    ${dir}/link_access.hpp
    ${dir}/link_creation.hpp
    ${dir}/object_copy.hpp
    ${dir}/object_creation.hpp
    ${dir}/string_creation.hpp
    ${dir}/type_creation.hpp
    ${dir}/virtual_data_map.hpp
    )

install(FILES ${HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/property)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
