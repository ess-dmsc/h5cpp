set(HEADERS filter.hpp
            types.hpp
            deflate.hpp
            fletcher32.hpp
            shuffle.hpp
)

add_doxygen_source_deps(${HEADERS})
install(FILES ${HEADERS} 
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/filter) 