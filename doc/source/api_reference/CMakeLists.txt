set(SOURCES index.rst
            namespace_hdf5.rst)

add_sphinx_source(${SOURCES})
copy_to_current_build(${SOURCES})