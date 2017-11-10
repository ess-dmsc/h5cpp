set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS
    ${dir}/attribute_iterator.hpp
    ${dir}/attribute_manager.hpp
    ${dir}/attribute.hpp
    )

install(FILES ${HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/attribute)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
