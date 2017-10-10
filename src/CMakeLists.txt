add_subdirectory(include)

set(PROPERTY_SOURCES  property/class.cpp
					  property/creation_order.cpp
            		  property/list.cpp
            		  property/file_creation.cpp	  
            		  property/file_access.cpp
            		  property/file_mount_list.cpp
            		  property/dataset_access_list.cpp
            		  property/dataset_creation_list.cpp
            		  property/dataset_transfer_list.cpp
                      property/group_creation.cpp
                      property/group_access.cpp
                      property/object_creation.cpp
                      property/object_copy_list.cpp
                      property/string_creation_list.cpp
                      property/type_creation_list.cpp
                      property/datatype_access_list.cpp
                      property/link_creation_list.cpp
                      property/link_access_list.cpp
                      property/attribute_creation_list.cpp)
                     
set(DATATYPE_SOURCES datatype/datatype.cpp
	datatype/integer.cpp
	datatype/float.cpp
	datatype/types.cpp
	datatype/compound.cpp
	)

set(DATASPACE_SOURCES dataspace/dataspace.cpp
                      dataspace/scalar.cpp
                      dataspace/simple.cpp
                      dataspace/selection.cpp
                      dataspace/selection_manager.cpp
                      dataspace/type.cpp)
                     
set(FILE_SOURCES file/types.cpp
	             file/file.cpp
	             file/functions.cpp
)

set(NODE_SOURCES node/types.cpp
	             node/group_view.cpp
	             node/node_view.cpp
	             node/link_view.cpp
	             node/node.cpp
	             node/link.cpp
	             node/group.cpp
	             node/utilities.cpp
	             node/dataset.cpp
               node/functions.cpp
               node/node_iterator.cpp
	             node/link_iterator.cpp
)

set(ATTRIBUTE_SOURCES attribute/attribute.cpp
	                  attribute/attribute_manager.cpp
	                  attribute/attribute_iterator.cpp
)

set(SOURCES object_handle.cpp
            object_id.cpp
            path.cpp
            iterator_config.cpp
            iterator.cpp
            )

add_library(h5cpp_shared SHARED ${SOURCES} ${PROPERTY_SOURCES} 
			${DATATYPE_SOURCES} ${DATASPACE_SOURCES}
		    ${FILE_SOURCES} ${NODE_SOURCES} ${ATTRIBUTE_SOURCES})
target_link_libraries(h5cpp_shared PUBLIC ${HDF5_LIBRARIES} Boost::filesystem)
target_compile_definitions(h5cpp_shared PRIVATE DLL_BUILD)
target_include_directories(h5cpp_shared
	PRIVATE  
	${PROJECT_SOURCE_DIR}/src/include
	PUBLIC 
	${HDF5_INCLUDE_DIRS}
	INTERFACE 
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

set_target_properties(h5cpp_shared 
	                  PROPERTIES 
	                  VERSION ${PROJECT_VERSION}
	                  SO_VERSION 0
	                  CXX_STANDARD_REQUIRED ON
	                                         )


install(TARGETS h5cpp_shared 
	    EXPORT h5cpp_shared_targets
	    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	    COMPONENT runtime
	    )
	   
install(EXPORT h5cpp_shared_targets
	    DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
	    COMPONENT development)



