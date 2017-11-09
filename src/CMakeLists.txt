add_subdirectory(include)

set(PROPERTY_SOURCES
  property/property_class.cpp
  property/creation_order.cpp
  property/property_list.cpp
  property/file_creation.cpp
  property/file_access.cpp
  property/file_mount.cpp
  property/dataset_access.cpp
  property/dataset_creation.cpp
  property/dataset_transfer.cpp
  property/group_creation.cpp
  property/group_access.cpp
  property/object_creation.cpp
  property/object_copy.cpp
  property/string_creation.cpp
  property/type_creation.cpp
  property/datatype_access.cpp
  property/link_creation.cpp
  property/link_access.cpp
  property/attribute_creation.cpp
  )

set(DATATYPE_SOURCES
  datatype/datatype.cpp
  datatype/integer.cpp
  datatype/float.cpp
  datatype/types.cpp
  datatype/compound.cpp
  datatype/string.cpp
  datatype/array.cpp
  )

set(DATASPACE_SOURCES
  dataspace/dataspace.cpp
  dataspace/scalar.cpp
  dataspace/simple.cpp
  dataspace/selection.cpp
  dataspace/selection_manager.cpp
  dataspace/type.cpp
  )

set(FILE_SOURCES
  file/types.cpp
  file/file.cpp
  file/functions.cpp
  file/direct_driver.cpp
  file/memory_driver.cpp
  file/posix_driver.cpp
  file/mpi_driver.cpp
  )

set(ERROR_SOURCES
  error/error.cpp
  )

set(NODE_SOURCES
  node/types.cpp
  node/group_view.cpp
  node/node_view.cpp
  node/link_view.cpp
  node/node.cpp
  node/link.cpp
  node/group.cpp
  node/utilities.cpp
  node/dataset.cpp
  node/functions.cpp
  node/node_iterator.cpp
  node/link_iterator.cpp
  )

set(ATTRIBUTE_SOURCES
  attribute/attribute.cpp
  attribute/attribute_manager.cpp
  attribute/attribute_iterator.cpp
  )

set(FILTER_SOURCES 
    filter/filter.cpp
    filter/deflate.cpp
    filter/fletcher32.cpp
    filter/shuffle.cpp
    )

set(SOURCES
  object_handle.cpp
  object_id.cpp
  path.cpp
  iterator_config.cpp
  iterator.cpp
  )


add_library(h5cpp_shared SHARED
  ${SOURCES}
  ${PROPERTY_SOURCES}
  ${DATATYPE_SOURCES}
  ${DATASPACE_SOURCES}
  ${ERROR_SOURCES}
  ${FILE_SOURCES}
  ${NODE_SOURCES}
  ${ATTRIBUTE_SOURCES}
  ${FILTER_SOURCES}
  )

target_compile_definitions(h5cpp_shared PRIVATE DLL_BUILD)
set(H5CPP_LINKS ${HDF5_LIBRARIES} Boost::filesystem ${MPI_CXX_LIBRARIES})
target_include_directories(h5cpp_shared
	PRIVATE  
	${PROJECT_SOURCE_DIR}/src/include
	PUBLIC 
	${HDF5_INCLUDE_DIRS} ${MPI_CXX_INCLUDE_PATH}
	INTERFACE 
	$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

#
# THIS IS BAD
# NEED TO GET RID OF THIS
if(WITH_MPI) 
target_compile_definitions(h5cpp_shared PUBLIC WITH_MPI)
endif()

set_target_properties(h5cpp_shared 
    PROPERTIES 
    VERSION ${PROJECT_VERSION}
    SO_VERSION 0
    CXX_STANDARD_REQUIRED ON
)

if (${COV})
    if (${CMAKE_CXX_COMPILER_ID} STREQUAL Clang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)
        set(cov_compile_flags "-g -O0 -fprofile-instr-generate -fcoverage-mapping")
        set(cov_link_flags "-g -O0 -fprofile-instr-generate -fcoverage-mapping")
    elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
        set(cov_compile_flags "-coverage -fprofile-generate -ftest-coverage")
        set(cov_link_flags "-g -O0 -coverage -fprofile-generate -ftest-coverage")
        set(H5CPP_LINKS ${H5CPP_LINKS} gcov)
    else()
        message(FATAL_ERROR "Unable to generate code coverage for this compiler (${CMAKE_CXX_COMPILER_ID}).")
    endif()
    set_target_properties(h5cpp_shared PROPERTIES LINK_FLAGS ${cov_link_flags})
    set_target_properties(h5cpp_shared PROPERTIES COMPILE_FLAGS ${cov_compile_flags})
endif()

target_link_libraries(h5cpp_shared PUBLIC ${H5CPP_LINKS})

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



