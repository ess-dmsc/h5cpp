set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(test_sources
  ${test_sources}
  ${dir}/deflate_test.cpp
  ${dir}/shuffle_test.cpp
  ${dir}/fletcher32_test.cpp
  ${dir}/external_filter_test.cpp
  PARENT_SCOPE)
