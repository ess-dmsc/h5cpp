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

add_library(h5cpp SHARED
  ${h5cpp_sources}
  ${h5cpp_headers}
  )

add_doxygen_source_deps(${h5cpp_headers})

target_compile_definitions(h5cpp PRIVATE DLL_BUILD)
set(H5CPP_LINKS Boost::filesystem Boost::system ${MPI_CXX_LIBRARIES})

#
# remove the absolute path from the library name
#
set(H5CPP_INTERFACE_LIBS)
set(H5CPP_PRIVATE_LIBS ${HDF5_LIBRARIES})
foreach(HDF5_LIBRARY ${HDF5_LIBRARIES})
    get_filename_component(LIB_NAME ${HDF5_LIBRARY} NAME)
    list(APPEND  H5CPP_INTERFACE_LIBS ${LIB_NAME})  
endforeach()


target_include_directories(h5cpp
  PRIVATE ${PROJECT_SOURCE_DIR}/src
  PRIVATE ${HDF5_INCLUDE_DIRS}
  PUBLIC ${MPI_CXX_INCLUDE_PATH}
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
  PUBLIC ${H5CPP_LINKS}
  PRIVATE ${COVERAGE_LIBRARIES} ${H5CPP_PRIVATE_LIBS}
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
 
# 
# Build the pkg-config file 
# 
function(GET_LIBRARY_NAME LIB)
	
	if(TARGET "${LIB}")
		get_target_property(LIBNAME "${LIB}" LOCATION)
		get_filename_component(LIBNAME "${LIBNAME}" NAME_WE)
		get_filename_component(LIBPATH "${LIBNAME}" DIRECTORY)
		set(LIBPATH "${LIBPATH}" PARENT_SCOPE)
	else()
		set(LIBNAME "${LIB}")		
	endif()

	string(REPLACE "${CMAKE_SHARED_LIBRARY_PREFIX}" "" LIBNAME "${LIBNAME}")
	string(REPLACE "${CMAKE_SHARED_LIBRARY_SUFFIX}" "" LIBNAME "${LIBNAME}") 
	set(LIBNAME "${LIBNAME}" PARENT_SCOPE)
	
endfunction(GET_LIBRARY_NAME)
	
set(PKGCONFIG_LIBS)
set(PKGCONFIG_LIBPATHS)
foreach(LIB ${H5CPP_LINKS})
	GET_LIBRARY_NAME("${LIB}")
	set(PKGCONFIG_LIBS "${PKGCONFIG_LIBS} -l${LIBNAME}")
	set(PKGCONFIG_LIBPATHS "${PKGCONFIG_LIBPATHS} -L${LIBPATH}")
endforeach()

foreach(LIB ${H5CPP_INTERFACE_LIBS})
	GET_LIBRARY_NAME("${LIB}")
	set(PKGCONFIG_LIBPATHS "${PKGCONFIG_LIBPATHS} -L${LIBPATH}")
	set(PKGCONFIG_LIBS "${PKGCONFIG_LIBS} -l${LIBNAME}")	
endforeach()

message("Linke libraries: ${PKGCONFIG_LIBS}")
message("Library paths: ${PKGCONFIG_LIBPATHS}")m

 
configure_file(h5cpp.pc.in h5cpp.pc @ONLY)
install(FILES h5cpp.pc
	    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
	    COMPONENT development)




