set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/datatype)


add_executable(datatype_integer_test integer_test.cpp)
target_link_libraries(datatype_integer_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::datatype::Integer"
                 datatype_integer_test
                 ${WORKING_DIRECTORY})

add_executable(datatype_compound_test compound_test.cpp ../examples/rgbpixel.cpp)
target_link_libraries(datatype_compound_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::datatype::Compound"
                 datatype_compound_test
                 ${WORKING_DIRECTORY})
                
add_executable(datatype_float_test float_test.cpp)
target_link_libraries(datatype_float_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::datatype::Float"
                 datatype_float_test
                 ${WORKING_DIRECTORY})
                 
add_executable(datatype_type_trait_test type_trait_test.cpp)
target_link_libraries(datatype_type_trait_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::datatype::TypeTrait"
                 datatype_type_trait_test
                 ${WORKING_DIRECTORY})
