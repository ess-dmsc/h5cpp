set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
  ${dir}/dataspace.cpp
  ${dir}/scalar.cpp
  ${dir}/selection.cpp
  ${dir}/selection_manager.cpp
  ${dir}/simple.cpp
  ${dir}/type.cpp
  ${dir}/view.cpp
  )

set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
