add_executable(h5ex_t_array h5ex_t_array.cpp)
target_link_libraries(h5ex_t_array h5cpp) 

add_executable(h5ex_t_arrayatt h5ex_t_arrayatt.cpp)
target_link_libraries(h5ex_t_arrayatt h5cpp) 

add_executable(h5ex_t_cmpd h5ex_t_cmpd.cpp measurement.cpp)
target_link_libraries(h5ex_t_cmpd h5cpp) 

add_executable(h5ex_t_enum h5ex_t_enum.cpp phase.cpp)
target_link_libraries(h5ex_t_enum h5cpp) 