set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS
    ${dir}/dataset.hpp
    ${dir}/group_view.hpp
    ${dir}/group.hpp
    ${dir}/link_view.hpp
    ${dir}/link.hpp
    ${dir}/node.hpp
    ${dir}/node_iterator.hpp
    ${dir}/link_iterator.hpp
    ${dir}/node_view.hpp
    ${dir}/functions.hpp
    ${dir}/types.hpp
    )

install(FILES ${HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/node)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
