set(test_sources
  deflate_test.cpp
  scaleoffset_test.cpp
  shuffle_test.cpp
  szip_test.cpp
  fletcher32_test.cpp
  nbit_test.cpp
  external_filter_test.cpp)

add_executable(filter_test ${test_sources})
target_link_libraries(
    filter_test
    PRIVATE
        h5cpp
        hdf5::hdf5
)
catch_discover_tests(filter_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME filter_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMAND filter_test)