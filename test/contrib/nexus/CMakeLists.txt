set(SOURCES attribute_h5py_bool_test.cpp
            attribute_pniio_bool_test.cpp
            dataset_h5py_bool_test.cpp
            dataset_pniio_bool_test.cpp
            ebool_test.cpp)

add_executable(ebool_test ${SOURCES})
target_link_libraries(ebool_test h5cpp $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,11.0>>:stdc++fs>)

catch_discover_tests(ebool_test
                     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME ebool_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMAND ebool_test)
