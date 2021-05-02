#
# We definitely need a better solution for this!
#
if (CMAKE_CXX_COMPILER_ID MATCHES MSVC)
  add_definitions(/wd4251 /wd4275)
endif ()

# ----------------------------------------------------------------------------
# include the modules required to use Catch2
# ----------------------------------------------------------------------------
include(Catch)

include_directories(${PROJECT_SOURCE_DIR}/src
                    ${HDF5_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/subprojects/catch2/include)

foreach(HDF5_LIB ${HDF5_LIBRARIES})
    get_filename_component(LIB_PATH ${HDF5_LIB} DIRECTORY)
    link_directories(${LIB_PATH})
endforeach()
foreach(HDF5_LIB ${HDF5_HL_LIBRARIES})
    get_filename_component(LIB_PATH ${HDF5_LIB} DIRECTORY)
    link_directories(${LIB_PATH})
endforeach()

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
