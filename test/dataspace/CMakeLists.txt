set(test_sources
    dataspace_test.cpp
    scalar_test.cpp
    simple_test.cpp
    hyperslab_simple_test.cpp
    points_simple_test.cpp
    type_trait_test.cpp
    selection_operator_set.cpp
    selection_manager_test.cpp
    view_test.cpp
    type_test.cpp
    )

add_executable(dataspace_test ${test_sources})
target_link_libraries(
    dataspace_test
    PRIVATE
        h5cpp
        hdf5::hdf5
)
catch_discover_tests(dataspace_test 
                     WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
add_test(NAME dataspace_test WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR} COMMAND dataspace_test)