set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/datatype)


add_executable(datatype_integer_test integer_test.cpp)
target_link_libraries(datatype_integer_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::datatype::Integer"
                 datatype_integer_test
                 ${WORKING_DIRECTORY})
                 
