set(HEADERS dataspace.hpp
	        scalar.hpp
	        selection_manager.hpp
	        selection.hpp
	        simple.hpp
	        type.hpp
	        )
	       
add_doxygen_source_deps(${HEADERS})
install(FILES ${HEADERS}
	    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/dataspace)