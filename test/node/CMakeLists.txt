set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/node)

add_executable(node_test node_test.cpp)
target_link_libraries(node_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::node::Node"
                 node_test
                 ${WORKING_DIRECTORY})

add_executable(node_type_test type_test.cpp)
target_link_libraries(node_type_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::node::Type"
                 node_type_test
                 ${WORKING_DIRECTORY})

add_executable(node_link_type_test link_type_test.cpp)
target_link_libraries(node_link_type_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::node::LinkType"
                 node_link_type_test
                 ${WORKING_DIRECTORY})
                
                
add_executable(node_link_test link_test.cpp)
target_link_libraries(node_link_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::node::Link"
                 node_link_test
                 ${WORKING_DIRECTORY})

add_executable(node_group_test group_test.cpp group_test_fixtures.cpp
                               group_node_iteration_test.cpp
                               group_link_iteration_test.cpp)
target_link_libraries(node_group_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::node::Group"
                 node_group_test
                 ${WORKING_DIRECTORY})
