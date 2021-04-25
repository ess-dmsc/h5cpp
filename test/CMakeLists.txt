#
# We definitely need a better solution for this!
#
if (CMAKE_CXX_COMPILER_ID MATCHES MSVC)
  add_definitions(/wd4251 /wd4275)
endif ()
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

set(dir ${CMAKE_CURRENT_SOURCE_DIR})

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


# Link stdc++fs or c++experimental to get std::experimental::filesystem when necessary
# target_link_libraries(unit_tests h5cpp $<$<AND:$<CXX_COMPILER_ID:GNU>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,9.0>>:stdc++fs>)
#    target_link_libraries(unit_tests h5cpp $<$<AND:$<CXX_COMPILER_ID:AppleClang>,$<VERSION_LESS:$<CXX_COMPILER_VERSION>,11.0>>:c++fs>)


#create_coverage_targets(
#  generate_coverage
#  run_tests
#  ${PROJECT_BINARY_DIR}
#  ${CMAKE_SOURCE_DIR}/src/h5cpp
#  ${PROJECT_BINARY_DIR}/coverage)
