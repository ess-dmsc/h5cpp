
add_executable(basic_files basic_files.cpp)
target_link_libraries(basic_files h5cpp_shared)

add_executable(selecting_datasets selecting_datasets.cpp)
target_link_libraries(selecting_datasets h5cpp_shared)

add_executable(writing_vector writing_vector.cpp)
target_link_libraries(writing_vector h5cpp_shared)

add_executable(writing_complex writing_complex.cpp)
target_link_libraries(writing_complex h5cpp_shared)

add_executable(writing_image writing_image.cpp
                             rgbpixel.cpp)
target_link_libraries(writing_image h5cpp_shared)

add_executable(append_scalar_data append_scalar_data.cpp)
target_link_libraries(append_scalar_data h5cpp_shared)