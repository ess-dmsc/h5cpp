set(SOURCES index.rst)

list(APPEND RST_SOURCES ${SOURCES})

foreach(SRC ${SOURCES})
	configure_file(${SRC} ${SRC} COPYONLY)
endforeach()