set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(test_sources
    ${test_sources}
    ${dir}/vector_memory_adapter_test.cpp
    ${dir}/complex_datatype_trait_test.cpp
    ${dir}/string_types_test.cpp
    PARENT_SCOPE)
