set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/attribute)

add_executable(attribute_attribute_test attribute_test.cpp
                                        attribute_test_fixtures.cpp
                                        attribute_name_access_test.cpp
                                        attribute_management_test.cpp)
target_link_libraries(attribute_attribute_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::attribute::Attribute"
                 attribute_attribute_test
                 ${WORKING_DIRECTORY})
                
                