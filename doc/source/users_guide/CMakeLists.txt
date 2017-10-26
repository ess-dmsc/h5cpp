set(SOURCES index.rst
	        installing.rst
            using.rst)

add_sphinx_source(${SOURCES})
copy_to_current_build(${SOURCES})
