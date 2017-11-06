set(HEADERS object_handle.hpp
	        windows.hpp
	        types.hpp
	        path.hpp
	        iterator_config.hpp
	        iterator.hpp
	        object_id.hpp
	        hdf5.hpp
	       )
	      
	      
add_doxygen_source_deps(${HEADERS})	      
add_subdirectory(property)	
add_subdirectory(dataspace)
add_subdirectory(datatype)  
add_subdirectory(node)
add_subdirectory(file)
add_subdirectory(attribute)
add_subdirectory(error)
add_subdirectory(filter)

install(FILES ${HEADERS} 
	    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp)     