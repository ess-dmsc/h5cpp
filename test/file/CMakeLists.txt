set(test_sources
  searchflags_test.cpp
  accessflags_test.cpp
  scope_test.cpp
  file_test.cpp
  file_creation_test.cpp
  file_image_test.cpp
   file_open_test.cpp
   file_close_test.cpp
   is_hdf5_test.cpp
   driver_test.cpp
  )

add_executable(file_test ${test_sources})
target_link_libraries(file_test h5cpp)
# target_compile_definitions(file_test PRIVATE CATCH_CONFIG_MAIN)
catch_discover_tests(file_test 
                     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

