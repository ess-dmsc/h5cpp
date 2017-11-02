add_subdirectory(advanced)
set(SOURCES index.rst
	        installing.rst
            using.rst
            files.rst
            groups.rst
            overview.rst
            dataspace.rst
        )

add_sphinx_source(${SOURCES})
copy_to_current_build(${SOURCES})
