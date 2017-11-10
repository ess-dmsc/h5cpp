set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS
    ${dir}/filter.hpp
    ${dir}/types.hpp
    ${dir}/deflate.hpp
    ${dir}/fletcher32.hpp
    ${dir}/shuffle.hpp
    )

install(FILES ${HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/filter)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
