set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(test_sources
    ${test_sources}
    ${dir}/descriptor_test.cpp
    ${dir}/h5c_error_test.cpp
    ${dir}/error_test.cpp
    PARENT_SCOPE)
