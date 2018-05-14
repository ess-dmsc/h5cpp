set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(test_sources
    ${test_sources}
    ${dir}/datatype_test.cpp
    ${dir}/integer_test.cpp
    ${dir}/compound_test.cpp
    ${dir}/float_test.cpp
    ${dir}/string_test.cpp
    ${dir}/type_test.cpp
    ${dir}/type_trait_test.cpp
    ${dir}/datatype_test.cpp
    ${dir}/enum_test.cpp
    ${dir}/array_test.cpp
    ${dir}/vlen_array_test.cpp
    PARENT_SCOPE)
