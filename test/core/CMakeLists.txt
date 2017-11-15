set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(test_sources
  ${test_sources}
  ${dir}/ObjectHandleDefault.cpp
  ${dir}/object_handle_test.cpp
  ${dir}/file_object_handle_test.cpp
  ${dir}/datatype_object_handle_test.cpp
  ${dir}/dataspace_object_handle_test.cpp
  ${dir}/group_object_handle_test.cpp
  ${dir}/dataset_object_handle_test.cpp
  ${dir}/attribute_object_handle_test.cpp
  ${dir}/property_objects_handle_test.cpp
  ${dir}/error_objects_handle_test.cpp
  ${dir}/test_environment.cpp
  ${dir}/iteration_index_test.cpp
  ${dir}/iteration_order_test.cpp
  ${dir}/iterator_test.cpp
  ${dir}/object_id_test.cpp
  ${dir}/path_test.cpp
  PARENT_SCOPE)

set(test_headers
  ${test_headers}
  ${dir}/object_handle_test.hpp
  PARENT_SCOPE)

