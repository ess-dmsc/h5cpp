set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
  ${dir}/array.cpp
  ${dir}/compound.cpp
  ${dir}/datatype.cpp
  ${dir}/float.cpp
  ${dir}/integer.cpp
  ${dir}/string.cpp
  ${dir}/types.cpp
  )

set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
