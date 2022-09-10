#
# some utility functions which make life easier
#

function(H5CPP_MESSAGE LEVEL)
	message(${LEVEL} "H5CPP: ${ARGN}")
endfunction()

function(copy_to_current_build)
	foreach(f ${ARGV})
		configure_file(${f} ${f} COPYONLY)
	endforeach()

endfunction()
