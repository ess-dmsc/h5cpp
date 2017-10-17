set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(Common_SRC
  ${Common_SRC}
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
  )

set(Common_INC
  ${Common_INC}
  ${dir}/object_handle_test.hpp
  )

set(Common_SRC ${Common_SRC} PARENT_SCOPE)
set(Common_INC ${Common_INC} PARENT_SCOPE)

