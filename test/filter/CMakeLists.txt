set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(Common_SRC
  ${Common_SRC}
  ${dir}/deflate_test.cpp
  ${dir}/shuffle_test.cpp
  ${dir}/fletcher32_test.cpp
  PARENT_SCOPE)