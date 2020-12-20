set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
  ${dir}/deflate.cpp
  ${dir}/filter.cpp
  ${dir}/fletcher32.cpp
  ${dir}/nbit.cpp
  ${dir}/scaleoffset.cpp
  ${dir}/shuffle.cpp
  ${dir}/szip.cpp
  ${dir}/external_filter.cpp
  )

set(HEADERS
  ${dir}/filter.hpp
  ${dir}/types.hpp
  ${dir}/deflate.hpp
  ${dir}/fletcher32.hpp
  ${dir}/nbit.hpp
  ${dir}/scaleoffset.hpp
  ${dir}/shuffle.hpp
  ${dir}/szip.hpp
  ${dir}/external_filter.hpp
  )

install(FILES ${HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/filter)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
