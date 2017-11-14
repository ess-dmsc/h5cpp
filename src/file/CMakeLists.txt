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

set(h5cpp_sources ${h5cpp_sources} ${SOURCES} PARENT_SCOPE)
