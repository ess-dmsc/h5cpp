set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(Common_SRC
  ${Common_SRC}
  ${dir}/dataspace_test.cpp
  ${dir}/scalar_test.cpp
  ${dir}/simple_test.cpp
  ${dir}/hyperslab_simple_test.cpp
  ${dir}/type_trait_test.cpp
  ${dir}/selection_operator_set.cpp
  ${dir}/view_test.cpp
  PARENT_SCOPE)
