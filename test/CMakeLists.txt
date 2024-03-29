#
# We definitely need a better solution for this!
#
if (CMAKE_CXX_COMPILER_ID MATCHES MSVC)
  add_definitions(/wd4251 /wd4275)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL Clang)
  # suppress warnings from Catch2 macros
  add_definitions(-Wno-reserved-identifier -Wno-unknown-warning-option)
endif ()
if (H5CPP_CATCH2_V2)
  add_compile_definitions(H5CPP_CATCH2_V2)
endif()
# ----------------------------------------------------------------------------
# include the modules required to use Catch2
# ----------------------------------------------------------------------------

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${HDF5_INCLUDE_DIRS})

configure_file(h5py_test_data.h5 h5py_test_data.h5 COPYONLY)
configure_file(h5py_test_boolattr.h5 h5py_test_boolattr.h5 COPYONLY)
configure_file(pniio_test_boolattr.h5 pniio_test_boolattr.h5 COPYONLY)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(examples)
add_subdirectory(error)
add_subdirectory(core)
add_subdirectory(property)
add_subdirectory(datatype)
add_subdirectory(dataspace)
add_subdirectory(attribute)
add_subdirectory(filter)
add_subdirectory(node)
add_subdirectory(file)
add_subdirectory(utilities)

if(H5CPP_ENABLE_NEXUS)
    add_subdirectory(contrib/nexus)
endif()
