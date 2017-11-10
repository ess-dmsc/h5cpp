set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS
    ${dir}/error.hpp
    )

install(FILES ${HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/error)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
