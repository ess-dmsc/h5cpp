
add_executable(property_list_class_test property_list_class_test.cpp)
target_link_libraries(property_list_class_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::property_list:Class"
                 property_list_class_test
                 ${PROJECT_BINARY_DIR}/test/property_list)