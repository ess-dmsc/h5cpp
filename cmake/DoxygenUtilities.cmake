#
# utility functions and variables for building doxygen documentation
#

#
# this variable adds build depencencies for the doxygen build
#
set(CMAKE_DOXYGEN_BUILD_DEPENDENCIES CACHE INTERNAL "")

#
# add doxygen dependencies in the source tree
#
function(add_doxygen_source_deps)
	
	set(DEPENDENCIES)
	foreach(deps ${ARGV})
		list(APPEND DEPENDENCIES ${deps})
	endforeach()
	
	set(CMAKE_DOXYGEN_BUILD_DEPENDENCIES ${CMAKE_DOXYGEN_BUILD_DEPENDENCIES} 
	                                     ${DEPENDENCIES} CACHE INTERNAL "")

endfunction()