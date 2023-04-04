set(test_sources
  deflate_test.cpp
  scaleoffset_test.cpp
  shuffle_test.cpp
  szip_test.cpp
  fletcher32_test.cpp
  nbit_test.cpp
  external_filter_test.cpp)

if(WIN32)
  add_executable(filter_test WIN32 ${test_sources})
else()
  add_executable(filter_test ${test_sources})
endif()
target_link_libraries(
    filter_test
    PRIVATE
        h5cpp
        hdf5::hdf5
	Catch2::Catch2 Catch2::Catch2WithMain
)
catch_discover_tests(filter_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
