set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
  ${dir}/deflate.cpp
  ${dir}/filter.cpp
  ${dir}/fletcher32.cpp
  ${dir}/shuffle.cpp
  )

set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
