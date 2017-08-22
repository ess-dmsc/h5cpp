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

set(SOURCES object_handle.cpp
            datatype.cpp
            object_id.cpp
            )

add_library(h5cpp_shared SHARED ${SOURCES} ${PROPERTY_SOURCES})
target_link_libraries(h5cpp_shared ${HDF5_LIBRARIES})
target_include_directories(h5cpp_shared PUBLIC
    ${HDF5_INCLUDE_DIRS}
    Boost::filesystem)

