set(test_sources
    datatype_test.cpp
    integer_test.cpp
    compound_test.cpp
    float_test.cpp
    string_test.cpp
    type_test.cpp
    type_trait_test.cpp
    datatype_test.cpp
    array_test.cpp
    vlen_array_test.cpp
    enum_test.cpp)

add_executable(datatype_test ${test_sources}) 
target_link_libraries(
    datatype_test
    PRIVATE
        h5cpp
        hdf5::hdf5
)
catch_discover_tests(datatype_test
                     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME datatype_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMAND datatype_test)
