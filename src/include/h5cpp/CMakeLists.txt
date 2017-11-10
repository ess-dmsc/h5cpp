set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS
    ${dir}/object_handle.hpp
    ${dir}/windows.hpp
    ${dir}/types.hpp
    ${dir}/path.hpp
    ${dir}/iterator_config.hpp
    ${dir}/iterator.hpp
    ${dir}/object_id.hpp
    ${dir}/hdf5.hpp
    ${dir}/hdf5_capi.hpp
    )

install(FILES ${HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp)

set(h5cpp_headers ${HEADERS})

add_subdirectory(attribute)
add_subdirectory(dataspace)
add_subdirectory(datatype)
add_subdirectory(error)
add_subdirectory(file)
add_subdirectory(filter)
add_subdirectory(node)
add_subdirectory(property)

add_doxygen_source_deps(${h5cpp_headers})

set(h5cpp_headers ${h5cpp_headers} PARENT_SCOPE)
