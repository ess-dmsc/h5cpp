set(IMAGES attribute_manager_uml.png
           base_classes_uml.png
           hyperslab_uml.png
           property_lists_uml.png
           )

foreach(IMAGE ${IMAGES})
    configure_file(${IMAGE} ${IMAGE} COPYONLY)
endforeach()
