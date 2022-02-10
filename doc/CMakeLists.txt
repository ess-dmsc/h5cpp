#============================================================================
# Building the API documentation using doxygen
#============================================================================
configure_file(Doxyfile.in Doxyfile @ONLY)
configure_file(users_guide.dox users_guide.dox COPYONLY)
configure_file(groups.dox groups.dox COPYONLY)
configure_file(mainpage.dox mainpage.dox COPYONLY)
configure_file(namespaces.dox namespaces.dox COPYONLY)
configure_file(index.html index.html COPYONLY)
configure_file(doxygen-bizflat.css doxygen-bizflat.css COPYONLY)
set_source_files_properties(Doxyfile groups.dox mainpage.dox namespaces.dox users_guide.dox
	PROPERTIES GENERATED TRUE)

add_custom_command(OUTPUT doxygen.stamp
                   COMMAND doxygen
                   COMMAND echo "timestamp" > doxygen.stamp
                   DEPENDS Doxyfile groups.dox mainpage.dox namespaces.dox users_guide.dox
                           ${CMAKE_DOXYGEN_BUILD_DEPENDENCIES}
                   WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/doc)

add_custom_target(api_doc DEPENDS doxygen.stamp)
add_custom_target(html)
add_dependencies(html api_doc)

#=============================================================================
# Build the users guide using sphinx
#=============================================================================
add_subdirectory(source)


#=============================================================================
# C API coverage generates RST
#=============================================================================
if(NOT WIN32)
	file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/capi_coverage)
	add_custom_target(
			capi_coverage
			COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/capi_coverage/tally.sh
			${CMAKE_SOURCE_DIR}/src
			${CMAKE_CURRENT_BINARY_DIR}/source/capi
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/capi_coverage
	)
endif(NOT WIN32)

add_custom_command(OUTPUT sphinx.stamp
    COMMAND sphinx-build -bhtml source build
    COMMAND echo "timestamp" > sphinx.stamp
    DEPENDS ${CMAKE_SPHINX_SOURCES} doxygen.stamp capi_coverage
    WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/doc
    )

add_custom_target(users_guide DEPENDS sphinx.stamp api_doc)
add_dependencies(html users_guide)

#==============================================================================
# need to remove some additional files after building the documentation
#==============================================================================
set(CLEANFILES doxygen.stamp sphinx.stamp html latex build)
set_directory_properties(PROPERTIES
    ADDITIONAL_MAKE_CLEAN_FILES ${CLEANFILES})
