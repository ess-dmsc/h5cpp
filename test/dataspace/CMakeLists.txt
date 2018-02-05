set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(test_sources
    ${test_sources}
    ${dir}/dataspace_test.cpp
    ${dir}/scalar_test.cpp
    ${dir}/simple_test.cpp
    ${dir}/hyperslab_simple_test.cpp
    ${dir}/type_trait_test.cpp
    ${dir}/selection_operator_set.cpp
    ${dir}/selection_manager_test.cpp
    ${dir}/view_test.cpp
    ${dir}/type_test.cpp
    PARENT_SCOPE)
