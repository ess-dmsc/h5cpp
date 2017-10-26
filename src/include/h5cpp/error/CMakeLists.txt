set(HEADERS error.hpp
	        )
add_doxygen_source_deps(${HEADERS})
install(FILES ${HEADERS}
	    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/error)