
add_executable(h5ex_g_compact h5ex_g_compact.cpp)
target_link_libraries(h5ex_g_compact h5cpp)

add_executable(h5ex_g_corder h5ex_g_corder.cpp)
target_link_libraries(h5ex_g_corder h5cpp)

add_executable(h5ex_g_create h5ex_g_create.cpp)
target_link_libraries(h5ex_g_create h5cpp)

add_executable(h5ex_g_intermediate h5ex_g_intermediate.cpp)
target_link_libraries(h5ex_g_intermediate h5cpp)

add_executable(h5ex_g_phase h5ex_g_phase.cpp)
target_link_libraries(h5ex_g_phase h5cpp)

configure_file(h5ex_g_iterate.h5 h5ex_g_iterate.h5 COPYONLY)
configure_file(h5ex_g_traverse.h5 h5ex_g_traverse.h5 COPYONLY)
configure_file(h5ex_g_visit.h5 h5ex_g_visit.h5 COPYONLY)

add_executable(h5ex_g_iterate h5ex_g_iterate.cpp)
target_link_libraries(h5ex_g_iterate h5cpp)

add_executable(h5ex_g_traverse h5ex_g_traverse.cpp)
target_link_libraries(h5ex_g_traverse h5cpp)

add_executable(h5ex_g_visit h5ex_g_visit.cpp)
target_link_libraries(h5ex_g_visit h5cpp)