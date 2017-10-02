set(HEADERS file.hpp
	        functions.hpp
	        types.hpp
	        )
	       
add_doxygen_source_deps(${HEADERS})
install(FILES ${HEADERS}
	    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/file)