
add_executable(h5ex_d_alloc h5ex_d_alloc.cpp)
target_link_libraries(h5ex_d_alloc h5cpp) 

add_executable(h5ex_d_checksum h5ex_d_checksum.cpp)
target_link_libraries(h5ex_d_checksum h5cpp)

add_executable(h5ex_d_chunk h5ex_d_chunk.cpp)
target_link_libraries(h5ex_d_chunk h5cpp)

add_executable(h5ex_d_compact h5ex_d_compact.cpp)
target_link_libraries(h5ex_d_compact h5cpp)

add_executable(h5ex_d_fillval h5ex_d_fillval.cpp)
target_link_libraries(h5ex_d_fillval h5cpp)

add_executable(h5ex_d_hyper h5ex_d_hyper.cpp)
target_link_libraries(h5ex_d_hyper h5cpp)

add_executable(h5ex_d_rdwr h5ex_d_rdwr.cpp)
target_link_libraries(h5ex_d_rdwr h5cpp)

add_executable(h5ex_d_shuffle h5ex_d_shuffle.cpp)
target_link_libraries(h5ex_d_shuffle h5cpp)

add_executable(h5ex_d_transform h5ex_d_transform.cpp)
target_link_libraries(h5ex_d_transform h5cpp)

add_executable(h5ex_d_unlimadd h5ex_d_unlimadd.cpp)
target_link_libraries(h5ex_d_unlimadd h5cpp)