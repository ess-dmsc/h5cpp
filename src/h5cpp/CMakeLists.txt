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
add_subdirectory(utilities)

add_doxygen_source_deps(${h5cpp_headers})

add_library(h5cpp
  ${h5cpp_sources}
  ${h5cpp_headers}
  )

add_doxygen_source_deps(${h5cpp_headers})

if (H5CPP_BUILD_SHARED OR BUILD_SHARED_LIBS)
	target_compile_definitions(h5cpp PRIVATE H5CPP_EXPORTS PUBLIC H5CPP_BUILD_SHARED)
endif()

set(H5CPP_LINKS ${MPI_CXX_LIBRARIES})
if(H5CPP_WITH_BOOST)
  list(APPEND H5CPP_LINKS Boost::filesystem Boost::system)
else()
    # Link stdc++fs or c++experimental to get std::experimental::filesystem when necessary
    target_compile_features(h5cpp PUBLIC cxx_std_17)
    list(APPEND H5CPP_LINKS $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>)
    list(APPEND H5CPP_LINKS $<$<AND:$<CXX_COMPILER_ID:AppleClang>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,11.0>>:c++fs>)
endif()

target_include_directories(h5cpp
  PRIVATE ${PROJECT_SOURCE_DIR}/src
  INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>
  INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
  )

#
# THIS IS BAD
# NEED TO GET RID OF THIS
if (H5CPP_WITH_MPI)
  target_compile_definitions(h5cpp PUBLIC H5CPP_WITH_MPI)
endif ()

set_target_properties(h5cpp
  PROPERTIES
  VERSION ${PROJECT_VERSION}
  SO_VERSION 0
  CXX_STANDARD_REQUIRED ON
  OUTPUT_NAME h5cpp
  )

enable_coverage(h5cpp)

target_link_libraries(h5cpp
  PUBLIC 
    ${H5CPP_LINKS}
  PRIVATE ${COVERAGE_LIBRARIES}
    hdf5::hdf5
    hdf5::hdf5_hl
  INTERFACE ${H5CPP_INTERFACE_LIBS})

include(GNUInstallDirs) #Required for CMAKE_INSTALL_XXX

install(TARGETS h5cpp
  EXPORT h5cpp_targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  COMPONENT runtime
  )

install(EXPORT h5cpp_targets
  DESTINATION ${CMAKE_INSTALL_PACKAGEDIR}
  COMPONENT development)
