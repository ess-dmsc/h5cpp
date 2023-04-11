set(test_sources
    attribute_test.cpp
    attribute_name_access_test.cpp
    attribute_management_test.cpp
    attribute_scalar_io_test.cpp
    attribute_multidim_io_test.cpp
    attribute_fixed_string_io.cpp
    attribute_variable_string_io.cpp
    )

if(WIN32)
  add_executable(attribute_test WIN32 ${test_sources})
else()
  add_executable(attribute_test ${test_sources})
endif()
target_link_libraries(
    attribute_test
    PRIVATE
        h5cpp
        hdf5::hdf5
	 Catch2::Catch2 Catch2::Catch2WithMain
)
catch_discover_tests(attribute_test)
