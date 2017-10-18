set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(Common_SRC
  ${Common_SRC}
  ${dir}/searchflags_test.cpp
  ${dir}/accessflags_test.cpp
  ${dir}/scope_test.cpp
  ${dir}/file_creation_test.cpp
  ${dir}/file_open_test.cpp
  ${dir}/is_hdf5_test.cpp
  PARENT_SCOPE)
