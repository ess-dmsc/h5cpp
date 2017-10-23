set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(Common_SRC
  ${Common_SRC}
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
  PARENT_SCOPE)

set(Common_INC
  ${Common_INC}
  ${dir}/group_test_fixtures.hpp
  PARENT_SCOPE)

