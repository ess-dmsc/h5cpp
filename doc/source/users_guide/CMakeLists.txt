set(SOURCES index.rst)

add_sphinx_source(${SOURCES})

foreach(SRC ${SOURCES})
	configure_file(${SRC} ${SRC} COPYONLY)
endforeach()