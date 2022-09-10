set(HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/array.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/complex.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/stl.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/string.hpp
            ${CMAKE_CURRENT_SOURCE_DIR}/vector.hpp)

install(FILES ${HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/contrib/stl)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
