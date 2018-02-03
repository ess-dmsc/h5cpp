#
# Utility functions and variables for using shpinx
#
#
message(STATUS "Looking for thes phinx documentation generator")
set(CMAKE_SPHINX_SOURCES CACHE INTERNAL "List with sphinx source files" FORCE)

find_program(SPHINX_BUILD_EXEC NAMES sphinx-build)

if(SPHINX_BUILD_EXEC MATCHES "SPHINX_BUILD_EXEC-NOTFOUND")
	message(STATUS "Could not find sphinx executable")
else()
	message(STATUS "Found sphinx executable: ${SPHINX_BUILD_EXEC}")
endif()

function(add_sphinx_source)
	
	set(SOURCES)
	foreach(arg ${ARGV})
#		message(STATUS "Add sphinx source: ${arg}")
		list(APPEND SOURCES ${CMAKE_CURRENT_BINARY_DIR}/${arg})
	endforeach()
	
	set(CMAKE_SPHINX_SOURCES ${CMAKE_SPHINX_SOURCES} ${SOURCES} CACHE INTERNAL "" FORCE)

endfunction()
	

