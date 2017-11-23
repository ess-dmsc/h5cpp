set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(test_sources
  ${test_sources}
  ${dir}/node_test.cpp
  ${dir}/group_test_fixtures.cpp
  ${dir}/type_test.cpp
  ${dir}/link_type_test.cpp
  ${dir}/link_test.cpp
  ${dir}/group_test.cpp
  ${dir}/group_node_iteration_test.cpp
  ${dir}/group_link_iteration_test.cpp
  ${dir}/dataset_test.cpp
  ${dir}/dataset_extent_test.cpp
  ${dir}/dataset_partial_io_test.cpp
  ${dir}/dataset_array_type_io.cpp
  ${dir}/dataset_vlen_array_io.cpp
  ${dir}/dataset_fixed_string_io.cpp
  ${dir}/dataset_variable_string_io.cpp
  ${dir}/virtual_dataset_test.cpp
  ${dir}/get_test.cpp
  ${dir}/chunked_dataset_test.cpp
  ${dir}/recursive_node_iterator_test.cpp
  ${dir}/recursive_link_iterator_test.cpp
  ${dir}/symbolic_link_creation_test.cpp
  ${dir}/is_group_test.cpp
  ${dir}/is_dataset_test.cpp
  ${dir}/get_group_test.cpp
  ${dir}/get_dataset_test.cpp
  PARENT_SCOPE)

set(test_headers
  ${test_headers}
  ${dir}/group_test_fixtures.hpp
  PARENT_SCOPE)

