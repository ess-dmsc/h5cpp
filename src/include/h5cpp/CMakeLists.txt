set(HEADERS object_handle.hpp
	        windows.hpp
	        types.hpp
	        path.hpp)
	      
	      
add_doxygen_source_deps(${HEADERS})	      
add_subdirectory(property)	
add_subdirectory(dataspace)
add_subdirectory(datatype)  

install(FILES ${HEADERS} 
	    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp)     