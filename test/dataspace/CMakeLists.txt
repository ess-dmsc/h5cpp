set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/dataspace)

add_executable(dataspace_scalar_test scalar_test.cpp)
target_link_libraries(dataspace_scalar_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::dataspace::Scalar"
                 dataspace_scalar_test
                 ${WORKING_DIRECTORY})
                
                
add_executable(dataspace_simple_test simple_test.cpp)
target_link_libraries(dataspace_simple_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::dataspace::Simple"
                 dataspace_simple_test
                 ${WORKING_DIRECTORY})
                
add_executable(dataspace_hyperslab_simple_test hyperslab_simple_test.cpp)
target_link_libraries(dataspace_hyperslab_simple_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::dataspace::HyperslabSimple"
                 dataspace_hyperslab_simple_test
                 ${WORKING_DIRECTORY})