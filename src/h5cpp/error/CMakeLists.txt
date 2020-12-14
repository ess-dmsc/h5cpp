set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
  ${dir}/descriptor.cpp
  ${dir}/error.cpp
  )

set(HEADERS
  ${dir}/descriptor.hpp
  ${dir}/error.hpp
  ${dir}/h5c_error.hpp
  )

install(FILES ${HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/error)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
