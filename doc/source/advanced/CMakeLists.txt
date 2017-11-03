set(SOURCES index.rst
            user_data.rst
            io.rst
            cpp_datastructures.rst
            hdf5_handlers.rst
        )

add_sphinx_source(${SOURCES})
copy_to_current_build(${SOURCES})