set(HEADERS file.hpp
	        functions.hpp
	        types.hpp
	        driver.hpp
	        direct_driver.hpp
	        memory_driver.hpp
	        posix_driver.hpp
	        mpi_driver.hpp
	        )
	       
add_doxygen_source_deps(${HEADERS})
install(FILES ${HEADERS}
	    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/file)