set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS
    ${dir}/hdf5.hpp
    )

install(FILES ${HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp)

set(h5cpp_headers ${HEADERS})

add_subdirectory(core)
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
