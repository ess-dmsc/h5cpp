#
# some utility functions which make life easier
#

function(copy_to_current_build)

	foreach(f ${ARGV})
		configure_file(${f} ${f} COPYONLY)
	endforeach()
	
endfunction()
