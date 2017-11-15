set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
  ${dir}/iterator.cpp
  ${dir}/iterator_config.cpp
  ${dir}/object_handle.cpp
  ${dir}/object_id.cpp
  ${dir}/path.cpp
  )

set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
