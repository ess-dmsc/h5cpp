include_directories(${PROJECT_SOURCE_DIR}/src/include)

set(PROPERTY_SOURCES  property/class.cpp
					  property/creation_order.cpp
            		  property/list.cpp
            		  property/file_creation.cpp	  
            		  property/file_access.cpp
            		  property/file_mount_list.cpp
            		  property/dataset_access_list.cpp
                      property/group_creation.cpp
                      property/group_access.cpp
                      property/object_creation.cpp
                      property/string_creation_list.cpp
                      property/type_creation_list.cpp
                      property/datatype_access_list.cpp
                      property/link_creation_list.cpp
                      property/link_access_list.cpp
                      property/attribute_creation_list.cpp)
                     
set(DATATYPE_SOURCES datatype/datatype.cpp
	datatype/copy_native_type.cpp
	datatype/integer.cpp
	datatype/float.cpp
	)

set(DATASPACE_SOURCES dataspace/dataspace.cpp
                      dataspace/scalar.cpp
                      dataspace/simple.cpp
                      dataspace/selection.cpp
                      dataspace/selection_manager.cpp)

set(SOURCES object_handle.cpp
            object_id.cpp
            path.cpp
            )

add_library(h5cpp_shared SHARED ${SOURCES} ${PROPERTY_SOURCES} 
			${DATATYPE_SOURCES} ${DATASPACE_SOURCES})
target_link_libraries(h5cpp_shared ${HDF5_LIBRARIES} Boost::filesystem)
target_compile_definitions(h5cpp_shared PRIVATE DLL_BUILD)
target_include_directories(h5cpp_shared PUBLIC ${HDF5_INCLUDE_DIRS})

