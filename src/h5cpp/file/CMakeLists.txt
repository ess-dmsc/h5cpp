set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCES
  ${dir}/direct_driver.cpp
  ${dir}/file.cpp
  ${dir}/functions.cpp
  ${dir}/memory_driver.cpp
  ${dir}/mpi_driver.cpp
  ${dir}/posix_driver.cpp
  ${dir}/types.cpp
  )

set(HEADERS
  ${dir}/file.hpp
  ${dir}/functions.hpp
  ${dir}/types.hpp
  ${dir}/driver.hpp
  ${dir}/direct_driver.hpp
  ${dir}/memory_driver.hpp
  ${dir}/posix_driver.hpp
  ${dir}/mpi_driver.hpp
  )

install(FILES ${HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp/file)

set(h5cpp_headers ${h5cpp_headers} ${HEADERS} PARENT_SCOPE)
set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
