set(SOURCES index.rst)

foreach(SRC ${SOURCES})
	configure_file(${SRC} ${SRC} COPYONLY)
	set_property(GLOBAL APPEND PROPERTY RST_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/${SRC})
endforeach()