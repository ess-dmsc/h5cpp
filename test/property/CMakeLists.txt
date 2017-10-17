set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(Common_SRC
  ${Common_SRC}
  ${dir}/class_test.cpp
  ${dir}/group_creation_list_test.cpp
  ${dir}/creation_order_test.cpp
  ${dir}/object_creation_list_test.cpp
  ${dir}/string_creation_list_test.cpp
  ${dir}/type_creation_list_test.cpp
  ${dir}/link_creation_list_test.cpp
  ${dir}/attribute_creation_list_test.cpp
  ${dir}/file_access_list_test.cpp
  ${dir}/file_creation_list_test.cpp
  ${dir}/link_access_list_test.cpp
  ${dir}/file_mount_list_test.cpp
  ${dir}/group_access_list_test.cpp
  ${dir}/datatype_access_list_test.cpp
  ${dir}/chunk_cache_parameters_test.cpp
  ${dir}/dataset_access_list_test.cpp
  ${dir}/dataset_creation_list_test.cpp
  ${dir}/dataset_transfer_list_test.cpp
  ${dir}/object_copy_list_test.cpp
  PARENT_SCOPE)
