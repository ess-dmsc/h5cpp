set(SOURCES index.rst
	    installing.rst
            using.rst
            files.rst
            groups.rst
            overview.rst
            dataspace.rst
            dataspace_custom_types.rst
            dataspace_selections.rst
            attributes.rst
	    datasets.rst
	    links_and_paths.rst
	    classes.rst
	    adapters.rst
        )

add_sphinx_source(${SOURCES})
copy_to_current_build(${SOURCES})
