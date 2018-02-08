set(SOURCES index.rst
            namespace_hdf5.rst
            namespace_attribute.rst
            namespace_dataspace.rst
            namespace_datatype.rst
            namespace_file.rst
            namespace_filter.rst
            namespace_node.rst
            namespace_property.rst)

add_sphinx_source(${SOURCES})
copy_to_current_build(${SOURCES})