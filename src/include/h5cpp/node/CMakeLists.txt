set(HEADERS dataset.hpp
	        group_view.hpp
	        group.hpp
	        link_view.hpp
	        link.hpp
	        node.hpp
	        node_iterator.hpp
	        link_iterator.hpp
	        node_view.hpp
	        functions.hpp
	        types.hpp
	        )
	       
add_doxygen_source_deps(${HEADERS})
install(FILES ${HEADERS}
	    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/node)