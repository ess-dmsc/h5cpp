set(SOURCES index.rst
            using.rst
            files.rst)

add_sphinx_source(${SOURCES})
copy_to_current_build(${SOURCES})
