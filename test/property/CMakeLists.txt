set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/property)


add_executable(property_class_test class_test.cpp)
target_link_libraries(property_class_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::property::Class"
                 property_class_test
                 ${WORKING_DIRECTORY})
                 
add_executable(property_group_creation_list_test group_creation_list_test.cpp)
target_link_libraries(property_group_creation_list_test h5cpp_shared 
Boost::unit_test_framework Boost::system)
add_logging_test("hdf5::property::GroupCreationList"
                 property_group_creation_list_test
                 ${WORKING_DIRECTORY})
                 
add_executable(property_creation_order_test creation_order_test.cpp)
target_link_libraries(property_creation_order_test h5cpp_shared 
Boost::unit_test_framework Boost::system)
add_logging_test("hdf5::property::CreationOrder"
                 property_creation_order_test
                 ${WORKING_DIRECTORY})             
                 
add_executable(property_object_creation_list_test object_creation_list_test.cpp)
target_link_libraries(property_object_creation_list_test h5cpp_shared 
Boost::unit_test_framework Boost::system)
add_logging_test("hdf5::property::ObjectCreationList"
                 property_object_creation_list_test
                 ${WORKING_DIRECTORY})     
                 
add_executable(property_string_creation_list_test string_creation_list_test.cpp)
target_link_libraries(property_string_creation_list_test h5cpp_shared 
Boost::unit_test_framework Boost::system)
add_logging_test("hdf5::property::StringCreationList"
                 property_string_creation_list_test
                 ${WORKING_DIRECTORY})     
                 
add_executable(property_type_creation_list_test type_creation_list_test.cpp)
target_link_libraries(property_type_creation_list_test h5cpp_shared 
Boost::unit_test_framework Boost::system)
add_logging_test("hdf5::property::TypeCreationList"
                 property_type_creation_list_test
                 ${WORKING_DIRECTORY})         
                 
add_executable(property_link_creation_list_test link_creation_list_test.cpp)
target_link_libraries(property_link_creation_list_test h5cpp_shared 
Boost::unit_test_framework Boost::system)
add_logging_test("hdf5::property::LinkCreationList"
                 property_link_creation_list_test
                 ${WORKING_DIRECTORY})    
                 
add_executable(property_attribute_creation_list_test attribute_creation_list_test.cpp)
target_link_libraries(property_attribute_creation_list_test h5cpp_shared 
Boost::unit_test_framework Boost::system)
add_logging_test("hdf5::property::AttributeCreationList"
                 property_attribute_creation_list_test
                 ${WORKING_DIRECTORY}) 
                 
add_executable(property_file_access_list_test file_access_list_test.cpp)
target_link_libraries(property_file_access_list_test h5cpp_shared 
Boost::unit_test_framework Boost::system)
add_logging_test("hdf5::property::FileAccessList"
                 property_file_access_list_test
                 ${WORKING_DIRECTORY}) 
                 
add_executable(property_file_create_list_test file_creation_list_test.cpp)
target_link_libraries(property_file_create_list_test h5cpp_shared 
Boost::unit_test_framework Boost::system)
add_logging_test("hdf5::property::FileCreationList"
                 property_file_create_list_test
                 ${WORKING_DIRECTORY}) 