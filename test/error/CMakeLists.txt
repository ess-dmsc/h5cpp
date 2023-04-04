set(test_sources
    descriptor_test.cpp
    h5c_error_test.cpp
    error_test.cpp)

if(WIN32)
  add_executable(error_test WIN32 ${test_sources})
else()
  add_executable(error_test ${test_sources})
endif()
target_link_libraries(
    error_test
    PRIVATE
        h5cpp
        hdf5::hdf5
	 Catch2::Catch2WithMain
)
catch_discover_tests(error_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
