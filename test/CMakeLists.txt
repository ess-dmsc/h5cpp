include_directories(${PROJECT_SOURCE_DIR}/src)

find_package(GTest)

if (NOT GTest_FOUND)
  if (CMAKE_SYSTEM_NAME MATCHES Linux AND NOT WITH_CONAN)

    find_program(LSB_RELEASE lsb_release)
    execute_process(COMMAND ${LSB_RELEASE} -is
      OUTPUT_VARIABLE LINUX_DISTRIBUTION
      OUTPUT_STRIP_TRAILING_WHITESPACE)

    if (LINUX_DISTRIBUTION MATCHES "Debian" OR LINUX_DISTRIBUTION MATCHES "Ubuntu")
      message(STATUS "Attempting to apply Debian fix for googletest")
      include(${PROJECT_SOURCE_DIR}/cmake/DebianGTestFix.cmake)
    else ()
      message(FATAL_ERROR "GTest not found and no fix available")
    endif ()

  else ()
    message(FATAL_ERROR "GTest not found and no fix available")
  endif ()
endif ()

find_package(Threads REQUIRED)

#
# We definitely need a better solution for this!
#
if (CMAKE_CXX_COMPILER_ID MATCHES MSVC)
  add_definitions(/wd4251 /wd4275)
endif ()


set(dir ${CMAKE_CURRENT_SOURCE_DIR})

set(test_sources
  ${dir}/main.cpp
  ${dir}/fixture.cpp
  )

set(test_headers
  ${dir}/fixture.hpp
  )

add_subdirectory(core)
add_subdirectory(attribute)
add_subdirectory(dataspace)
add_subdirectory(datatype)
add_subdirectory(error)
add_subdirectory(file)
add_subdirectory(filter)
add_subdirectory(node)
add_subdirectory(property)

add_executable(unit_tests
  EXCLUDE_FROM_ALL
  ${test_sources}
  ${test_headers})
add_dependencies(unit_tests h5cpp_shared)
enable_coverage(unit_tests)
target_include_directories(unit_tests
  PRIVATE ${GTEST_INCLUDE_DIRS}
  PRIVATE h5cpp_shared)
target_link_libraries(unit_tests
  h5cpp_shared
  ${GTEST_LIBRARIES}
  ${CMAKE_THREAD_LIBS_INIT}
  ${COVERAGE_LIBRARIES})

add_custom_target(run_tests
  COMMAND unit_tests "--gtest_output=xml:unit_tests_run.xml"
  DEPENDS unit_tests)
add_test(NAME "RunGoogleTests" COMMAND run_tests)

create_coverage_targets(
  generate_coverage
  run_tests
  ${PROJECT_BINARY_DIR}
  ${CMAKE_SOURCE_DIR}/src/h5cpp
  ${PROJECT_BINARY_DIR}/coverage)

