configure_file(conf.py.in conf.py @ONLY)
configure_file(index.rst.in index.rst @ONLY)

add_subdirectory(_static)
add_subdirectory(_templates)

add_sphinx_source(conf.py index.rst)

add_subdirectory(images)
add_subdirectory(users_guide)
add_subdirectory(design)
add_subdirectory(api_reference)
add_subdirectory(advanced)
