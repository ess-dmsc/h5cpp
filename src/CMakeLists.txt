set(SOURCES object_handle.cpp
            datatype.cpp
            property_list_class.cpp)

add_library(h5cpp_shared ${SOURCES})
target_link_libraries(h5cpp_shared ${HDF5_LIBRARIES})
target_include_directories(h5cpp_shared PUBLIC
    ${HDF5_INCLUDE_DIRS})

