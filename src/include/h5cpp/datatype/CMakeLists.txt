set(HEADERS datatype.hpp
	        factory.hpp
	        float.hpp
	        integer.hpp
	        type_trait.hpp
	        types.hpp
	        compound.hpp
          string.hpp
          )
	       
add_doxygen_source_deps(${HEADERS})
install(FILES ${HEADERS}
	    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/datatype)
