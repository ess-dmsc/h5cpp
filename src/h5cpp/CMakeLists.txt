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

target_compile_definitions(h5cpp PRIVATE DLL_BUILD)
set(H5CPP_LINKS ${MPI_CXX_LIBRARIES})
if(WITH_BOOST)
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
if (WITH_MPI)
  target_compile_definitions(h5cpp PUBLIC WITH_MPI)
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
  	HDF5::HDF5
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

# =============================================================================
# Build the pkg-config file
#
# basically the target provides all the information required to link against
# it via all the INTERFACE properties.
# =============================================================================
function(GET_LIBRARY_NAME LIB)

	message(STATUS "Dealing with library ${LIB}")
	if(TARGET "${LIB}")
	    #set(LIBTMP $<TARGET_FILE:LIB>)
		get_property(LIBTMP TARGET ${LIB} PROPERTY IMPORTED_LOCATION)
	else()
		set(LIBTMP "${LIB}")
	endif()

	get_filename_component(LIBNAME "${LIBTMP}" NAME_WE)
	get_filename_component(LIBPATH "${LIBTMP}" DIRECTORY)

	string(REPLACE "${CMAKE_SHARED_LIBRARY_PREFIX}" "" LIBNAME "${LIBNAME}")
	string(REPLACE "${CMAKE_SHARED_LIBRARY_SUFFIX}" "" LIBNAME "${LIBNAME}")
	message("Found: ${LIBNAME} in ${LIBPATH}")

	if(DEFINED PKG_CONFIG_LIBS)
		list(APPEND PKG_CONFIG_LIBS "${LIBNAME}")
		set(PKG_CONFIG_LIBS ${PKG_CONFIG_LIBS} PARENT_SCOPE)
	else()
		set(PKG_CONFIG_LIBS "${LIBNAME}" PARENT_SCOPE)
	endif()

	if(DEFINED PKG_CONFIG_LIBDIRS)
		list(APPEND PKG_CONFIG_LIBDIRS "${LIBPATH}")
		set(PKG_CONFIG_LIBDIRS ${PKG_CONFIG_LIBDIRS} PARENT_SCOPE)
	else()
		set(PKG_CONFIG_LIBDIRS "${LIBPATH}" PARENT_SCOPE)
	endif()

endfunction(GET_LIBRARY_NAME)

if(${CONAN} MATCHES "DISABLE")

  get_target_property(LIBRARIES h5cpp INTERFACE_LINK_LIBRARIES)
  get_target_property(DEFINITIONS h5cpp INTERFACE_COMPILE_DEFINITIONS)
  get_target_property(INCLUDE_DIRS h5cpp INTERFACE_INCLUDE_DIRECTORIES)

  foreach(LIB ${LIBRARIES})
    GET_LIBRARY_NAME("${LIB}")
  endforeach()

  foreach(LIB ${HDF5_LIBRARIES})
    GET_LIBRARY_NAME("${LIB}")
  endforeach()

  list(REMOVE_DUPLICATES PKG_CONFIG_LIBS)
  list(REMOVE_DUPLICATES PKG_CONFIG_LIBDIRS)

  if(${CMAKE_VERSION} VERSION_LESS "3.13.0")
    message("Please consider to switch to CMake 3.13.0")
  else()
    target_link_directories(h5cpp PUBLIC ${PKG_CONFIG_LIBDIRS})
  endif()

  set(PKG_CONFIG_LINKFLAGS)
  foreach(DIR ${PKG_CONFIG_LIBDIRS})
    set(PKG_CONFIG_LINKFLAGS "${PKG_CONFIG_LINKFLAGS} -L${DIR}")
  endforeach()
  foreach(LIB ${PKG_CONFIG_LIBS})
    set(PKG_CONFIG_LINKFLAGS "${PKG_CONFIG_LINKFLAGS} -l${LIB}")
  endforeach()

  set(PKG_CONFIG_CFLAGS)

  foreach(DEF ${DEFINITIONS})
    if(NOT (DEF MATCHES ".*NOTFOUND"))
      set(PKG_CONFIG_CFLAGS "${PKG_CONFIG_CFLAGS} -D${DEF}")
    endif()
  endforeach()
  foreach(INCDIR ${INCLUDE_DIRS})
    if(NOT (INCDIR MATCHES "\\$<.*"))
      set(PKG_CONFIG_CFLAGS "${PKG_CONFIG_CFLAGS} -I${INCDIR}")
    endif()
  endforeach()


  message("Linke libraries: ${PKG_CONFIG_LIBS}")
  message("Library paths: ${PKG_CONFIG_LINKFLAGS}")


  configure_file(h5cpp.pc.in h5cpp.pc @ONLY)
  install(FILES ${CMAKE_CURRENT_BINARY_DIR}/h5cpp.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
    COMPONENT development)

endif()
