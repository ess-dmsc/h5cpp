set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
  )

set(HEADERS
  ${dir}/array_adapter.hpp
  )

install(FILES ${HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/utilities)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
