set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/property_list)


add_executable(property_list_class_test property_list_class_test.cpp)
target_link_libraries(property_list_class_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::property_list:Class"
                 property_list_class_test
                 ${WORKING_DIRECTORY})
                 
add_executable(group_create_plist_test group_creation_property_list_test.cpp)
target_link_libraries(group_create_plist_test h5cpp_shared 
Boost::unit_test_framework Boost::system)
add_logging_test("hdf5::property_list::GroupCreation"
                 group_create_plist_test
                 ${WORKING_DIRECTORY})
                 
add_executable(link_creation_order_test link_creation_order_test.cpp)
target_link_libraries(link_creation_order_test h5cpp_shared 
Boost::unit_test_framework Boost::system)
add_logging_test("hdf5::property_list::LinkCreationOrder"
                 link_creation_order_test
                 ${WORKING_DIRECTORY})             
                 
add_executable(object_creation_plist_test object_creation_property_list_test.cpp)
target_link_libraries(object_creation_plist_test h5cpp_shared 
Boost::unit_test_framework Boost::system)
add_logging_test("hdf5::property_list::ObjectCreation"
                 object_creation_plist_test
                 ${WORKING_DIRECTORY})                      