configure_file(conf.py.in conf.py @ONLY)
configure_file(index.rst.in index.rst @ONLY)

set(RSTFILES classes.rst
             guidelines.rst
             attributes.rst
             datasets.rst
             files.rst
             general_design.rst
             groups.rst)
foreach(RSTFILE ${RSTFILES})
    configure_file(${RSTFILE} ${RSTFILE} COPYONLY)
endforeach()

add_subdirectory(_static)
add_subdirectory(_templates)
add_subdirectory(images)


                   


