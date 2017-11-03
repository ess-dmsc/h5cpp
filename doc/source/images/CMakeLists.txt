set(IMAGES attribute_manager_uml.png
           base_classes_uml.png
           hyperslab_uml.png
           property_lists_uml.png
           selection_classes.png
           hdf5_attributes.svg
           hdf5_basic_tree.svg
           hdf5_links.svg
           )

add_sphinx_source(${IMAGES})
copy_to_current_build(${IMAGES})
