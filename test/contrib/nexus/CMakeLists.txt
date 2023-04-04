set(test_sources attribute_h5py_bool_test.cpp
                 attribute_pniio_bool_test.cpp
                 dataset_h5py_bool_test.cpp
                 dataset_pniio_bool_test.cpp
                 ebool_test.cpp)

if(WIN32)	       
  add_executable(ebool_test WIN32 ${test_sources})
else()
  add_executable(ebool_test ${test_sources})
endif()
target_link_libraries(
    ebool_test
    PRIVATE
        h5cpp
        hdf5::hdf5
	Catch2::Catch2
)
catch_discover_tests(ebool_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
