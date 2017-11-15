set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS
  ${dir}/object_handle.hpp
  ${dir}/windows.hpp
  ${dir}/types.hpp
  ${dir}/path.hpp
  ${dir}/iterator_config.hpp
  ${dir}/iterator.hpp
  ${dir}/object_id.hpp
  ${dir}/hdf5_capi.hpp
  )

install(FILES ${HEADERS}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/core)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
