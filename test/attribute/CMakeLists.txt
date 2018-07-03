set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(test_sources
    ${test_sources}
    ${dir}/attribute_test_fixtures.cpp
    ${dir}/attribute_test.cpp
    ${dir}/attribute_name_access_test.cpp
    ${dir}/attribute_management_test.cpp
    ${dir}/attribute_scalar_io_test.cpp
    ${dir}/attribute_multidim_io_test.cpp
    ${dir}/attribute_complex_io_test.cpp
    ${dir}/attribute_fixed_string_io.cpp
    ${dir}/attribute_variable_string_io.cpp
    ${dir}/attribute_h5py_bool_test.cpp
    ${dir}/attribute_pniio_bool_test.cpp
    PARENT_SCOPE)

set(test_headers
    ${test_headers}
    ${dir}/attribute_test_fixtures.hpp
    PARENT_SCOPE)
                
