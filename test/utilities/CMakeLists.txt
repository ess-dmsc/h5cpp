if(WIN32)
  add_executable(utilities_test WIN32  array_adapter_test.cpp)
else()
  add_executable(utilities_test array_adapter_test.cpp)
endif()
target_link_libraries(
    utilities_test
    PRIVATE
        h5cpp
        hdf5::hdf5
	 Catch2::Catch2 Catch2::Catch2WithMain
)
catch_discover_tests(utilities_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
