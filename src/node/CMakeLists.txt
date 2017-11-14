set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
  ${dir}/dataset.cpp
  ${dir}/functions.cpp
  ${dir}/group.cpp
  ${dir}/group_view.cpp
  ${dir}/link.cpp
  ${dir}/link_iterator.cpp
  ${dir}/link_view.cpp
  ${dir}/node.cpp
  ${dir}/node_iterator.cpp
  ${dir}/node_view.cpp
  ${dir}/types.cpp
  ${dir}/utilities.cpp
  ${dir}/utilities.hpp
  )

set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
