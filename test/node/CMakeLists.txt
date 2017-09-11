set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/node)

add_executable(node_type_test type_test.cpp)
target_link_libraries(node_type_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::node::Type"
                 node_type_test
                 ${WORKING_DIRECTORY})

