set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(test_sources
  ${test_sources}
  ${dir}/searchflags_test.cpp
  ${dir}/accessflags_test.cpp
  ${dir}/imageflags_test.cpp
  ${dir}/scope_test.cpp
  ${dir}/file_test.cpp
  ${dir}/file_creation_test.cpp
  ${dir}/file_image_test.cpp
  ${dir}/file_open_test.cpp
  ${dir}/file_close_test.cpp
  ${dir}/is_hdf5_test.cpp
  ${dir}/driver_test.cpp
  PARENT_SCOPE)
