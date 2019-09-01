set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(test_sources
    ${test_sources}
    ${dir}/basic_traits_test.cpp
    ${dir}/vector_trait_test.cpp
    PARENT_SCOPE)
