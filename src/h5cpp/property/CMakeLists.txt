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
set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
