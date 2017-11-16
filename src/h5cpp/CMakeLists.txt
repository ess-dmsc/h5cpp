set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(HEADERS ${dir}/hdf5.hpp)
install(FILES ${HEADERS}
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/h5cpp)

set(h5cpp_headers ${HEADERS})
set(h5cpp_sources )
add_subdirectory(core)
add_subdirectory(attribute)
add_subdirectory(dataspace)
add_subdirectory(datatype)
add_subdirectory(error)
add_subdirectory(file)
add_subdirectory(filter)
add_subdirectory(node)
add_subdirectory(property)

add_doxygen_source_deps(${h5cpp_headers})

add_library(h5cpp_shared SHARED
  ${h5cpp_sources}
  ${h5cpp_headers}
  )

target_compile_definitions(h5cpp_shared PRIVATE DLL_BUILD)
set(H5CPP_LINKS ${HDF5_LIBRARIES} Boost::filesystem ${MPI_CXX_LIBRARIES})
target_include_directories(h5cpp_shared
  PRIVATE ${PROJECT_SOURCE_DIR}/src
  PUBLIC ${HDF5_INCLUDE_DIRS} ${MPI_CXX_INCLUDE_PATH}
  INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )

#
# THIS IS BAD
# NEED TO GET RID OF THIS
if (WITH_MPI)
  target_compile_definitions(h5cpp_shared PUBLIC WITH_MPI)
endif ()

set_target_properties(h5cpp_shared
  PROPERTIES
  VERSION ${PROJECT_VERSION}
  SO_VERSION 0
  CXX_STANDARD_REQUIRED ON
  )

enable_coverage(h5cpp_shared)

target_link_libraries(h5cpp_shared
  PUBLIC ${H5CPP_LINKS}
  PRIVATE ${COVERAGE_LIBRARIES})

include(GNUInstallDirs) #Required for CMAKE_INSTALL_XXX

install(TARGETS h5cpp_shared
  EXPORT h5cpp_shared_targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  COMPONENT runtime
  )

install(EXPORT h5cpp_shared_targets
  DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
  COMPONENT development)



