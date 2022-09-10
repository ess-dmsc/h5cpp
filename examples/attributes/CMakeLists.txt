add_executable(attribute_creation attribute_creation.cpp)
target_link_libraries(attribute_creation PRIVATE h5cpp::h5cpp)

add_executable(attribute_iteration attribute_iteration.cpp)
target_link_libraries(attribute_iteration PRIVATE h5cpp::h5cpp)

add_executable(attribute_io attribute_io.cpp)
target_link_libraries(attribute_io PRIVATE h5cpp::h5cpp)