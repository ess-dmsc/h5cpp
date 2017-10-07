
add_executable(basic_files basic_files.cpp)
target_link_libraries(basic_files h5cpp_shared)

add_executable(selecting_datasets selecting_datasets.cpp)
target_link_libraries(selecting_datasets h5cpp_shared)

