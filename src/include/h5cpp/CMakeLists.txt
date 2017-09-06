set(HEADERS object_handle.hpp
	        windows.hpp
	        types.hpp
	        path.hpp)
	      
	      
add_doxygen_source_deps(${HEADERS})	      
add_subdirectory(property)	
add_subdirectory(dataspace)
add_subdirectory(datatype)       