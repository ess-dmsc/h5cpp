set(dir ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(${dir}/with_boost.hpp.in ${dir}/with_boost.hpp)

set(SOURCES
  ${dir}/iterator.cpp
  ${dir}/iterator_config.cpp
  ${dir}/object_handle.cpp
  ${dir}/object_id.cpp
  ${dir}/path.cpp
  ${dir}/version.cpp
  )

set(HEADERS
  ${dir}/object_handle.hpp
  ${dir}/windows.hpp
  ${dir}/types.hpp
  ${dir}/path.hpp
  ${dir}/iterator_config.hpp
  ${dir}/iterator.hpp
  ${dir}/object_id.hpp
  ${dir}/hdf5_capi.hpp
  ${dir}/version.hpp
  ${dir}/variable_length_string.hpp
  ${dir}/fixed_length_string.hpp
  ${dir}/filesystem.hpp
  ${dir}/with_boost.hpp
  ${dir}/utilities.hpp
  )

install(FILES ${HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/core)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
