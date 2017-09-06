configure_file(conf.py.in conf.py @ONLY)
configure_file(index.rst.in index.rst @ONLY)


set_property(GLOBAL APPEND PROPERTY RST_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/conf.py)
set_property(GLOBAL APPEND PROPERTY RST_SOURCES ${CMAKE_CURRENT_BINARY_DIR}/index.rst)


add_subdirectory(_static)
add_subdirectory(_templates)
add_subdirectory(images)
add_subdirectory(users_guide)
add_subdirectory(design)
add_subdirectory(api_reference)


                   


