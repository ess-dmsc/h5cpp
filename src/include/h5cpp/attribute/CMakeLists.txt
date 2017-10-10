set(HEADERS attribute_iterator.hpp
	        attribute_manager.hpp
	        attribute.hpp)
	       
add_doxygen_source_deps(${HEADERS})	       
install(FILES ${HEADERS} 
	    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/attribute)     
	 