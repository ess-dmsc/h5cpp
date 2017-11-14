set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
  ${dir}/attribute.cpp
  ${dir}/attribute_iterator.cpp
  ${dir}/attribute_manager.cpp
  )

set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
