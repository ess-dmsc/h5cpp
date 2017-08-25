include_directories(${PROJECT_SOURCE_DIR}/src/include)
set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test)

include(${PROJECT_SOURCE_DIR}/cmake/BoostTestLogConfig.cmake)

add_subdirectory(ObjectHandle)
add_subdirectory(property)
add_subdirectory(datatype)
add_subdirectory(dataspace)
add_subdirectory(logs)

add_executable(hdf5_path_test path_test.cpp)
target_link_libraries(hdf5_path_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::Path"
                 hdf5_path_test
                 ${WORKING_DIRECTORY})