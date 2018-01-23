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
  ${dir}/virtual_dataset.cpp
  ${dir}/chunked_dataset.cpp
  ${dir}/recursive_node_iterator.cpp
  ${dir}/recursive_link_iterator.cpp
  )

set(HEADERS
  ${dir}/dataset.hpp
  ${dir}/group_view.hpp
  ${dir}/group.hpp
  ${dir}/link_view.hpp
  ${dir}/link.hpp
  ${dir}/node.hpp
  ${dir}/node_iterator.hpp
  ${dir}/link_iterator.hpp
  ${dir}/node_view.hpp
  ${dir}/functions.hpp
  ${dir}/types.hpp
  ${dir}/virtual_dataset.hpp
  ${dir}/chunked_dataset.hpp
  ${dir}/recursive_node_iterator.hpp
  ${dir}/recursive_link_iterator.hpp
  )

install(FILES ${HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/node)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
