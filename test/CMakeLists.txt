#
# We definitely need a better solution for this!
#
if (CMAKE_CXX_COMPILER_ID MATCHES MSVC)
  add_definitions(/wd4251 /wd4275)
endif ()

include_directories(${PROJECT_SOURCE_DIR}/src ${HDF5_INCLUDE_DIRS})
foreach(HDF5_LIB ${HDF5_LIBRARIES})
    get_filename_component(LIB_PATH ${HDF5_LIB} DIRECTORY)
    link_directories(${LIB_PATH})
endforeach()

configure_file(h5py_test_data.h5 h5py_test_data.h5 COPYONLY)
configure_file(h5py_test_boolattr.h5 h5py_test_boolattr.h5 COPYONLY)
configure_file(pniio_test_boolattr.h5 pniio_test_boolattr.h5 COPYONLY)

set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(test_sources ${dir}/main.cpp)
set(test_headers ${dir}/h5cpp_test_helpers.hpp)

set(test_sources
    ${test_sources}
    ${dir}/fixture.cpp)

set(test_headers
    ${test_headers}
    ${dir}/fixture.hpp
    )

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
add_subdirectory(type)
add_subdirectory(memory)

add_executable(unit_tests
  EXCLUDE_FROM_ALL
  ${test_sources}
  ${test_headers})
add_dependencies(unit_tests h5cpp)
target_include_directories(unit_tests
  PRIVATE ${GTEST_INCLUDE_DIRS}
  PRIVATE h5cpp)
target_link_libraries(unit_tests
  h5cpp
  ${GTEST_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  ${Boost_LIBRARIES}
  ${COVERAGE_LIBRARIES})
enable_coverage(unit_tests)

add_custom_target(run_tests
  COMMAND ${PROJECT_BINARY_DIR}/bin/unit_tests "--gtest_output=xml:unit_tests_run.xml"
  DEPENDS unit_tests)
add_test(NAME "RunGoogleTests" COMMAND run_tests)

create_coverage_targets(
  generate_coverage
  run_tests
  ${PROJECT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src/h5cpp
  ${PROJECT_BINARY_DIR}/coverage)
