#
# We definitely need a better solution for this!
#
if (CMAKE_CXX_COMPILER_ID MATCHES MSVC)
  add_definitions(/wd4251 /wd4275)
endif ()

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
