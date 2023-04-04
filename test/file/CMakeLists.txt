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

if(WIN32)
  add_executable(file_test WIN32 ${test_sources})
else()
  add_executable(file_test ${test_sources})
endif()
target_link_libraries(
    file_test
    PRIVATE
        h5cpp
        hdf5::hdf5_hl
        hdf5::hdf5
	 Catch2::Catch2WithMain
)
catch_discover_tests(file_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
