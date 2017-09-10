set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test/file)

add_executable(file_searchflags_test searchflags_test.cpp)
target_link_libraries(file_searchflags_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::file::SearchFlags"
                 file_searchflags_test
                 ${WORKING_DIRECTORY})

add_executable(file_accessflags_test accessflags_test.cpp)
target_link_libraries(file_accessflags_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::file::AccessFlags"
                 file_accessflags_test
                 ${WORKING_DIRECTORY})
                
add_executable(file_scope_test scope_test.cpp)
target_link_libraries(file_scope_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::file::Scope"
                 file_scope_test
                 ${WORKING_DIRECTORY})                
                
add_executable(file_create_test file_creation_test.cpp)
target_link_libraries(file_create_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::file::create"
                 file_create_test
                 ${WORKING_DIRECTORY}) 
                
add_executable(file_open_test file_open_test.cpp)
target_link_libraries(file_open_test h5cpp_shared Boost::unit_test_framework)
add_logging_test("hdf5::file::open"
                 file_open_test
                 ${WORKING_DIRECTORY})                 