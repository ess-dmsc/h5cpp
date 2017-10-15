#
# setting up variables and providing macros to setup looging when
# using the Google's unit test framework and gcc code coverage
#

enable_testing()

option(COV "Enable code coverage test for unit tests (if possible)." OFF)

set(TEST_BINARIES_PATH ${PROJECT_BINARY_DIR}/tests/bin)
set(MEMCHECK_RESULTS_PATH ${PROJECT_BINARY_DIR}/tests/memcheck)
set(COVERAGE_RESULTS_PATH ${PROJECT_BINARY_DIR}/tests/coverage)

set(unit_test_targets "" CACHE INTERNAL "All targets")

find_package(Threads)
find_package(GTest)

set(coverage_flags "-coverage -fprofile-generate")
set(gcovr_excl_opts "-e .*_test.cpp -e .*gtest.*.h" )
separate_arguments(gcovr_excl_opts)


find_program(VALGRIND_CMD valgrind)
if(EXISTS ${VALGRIND_CMD})
    message(STATUS "Valgrind found.")
else()
    message(STATUS "Valgrind not found. Unable to run memory check.")
endif()
mark_as_advanced(VALGRIND_CMD)

set(DO_COV OFF)
mark_as_advanced(DO_COV)
if (${COV})
  if (${CMAKE_COMPILER_IS_GNUCXX})
    message(STATUS "Code coverage enabled.")
    set(DO_COV ON)
    set(CMAKE_BUILD_TYPE Debug)
  else()
    message(FATAL_ERROR "Unable to enable code coverage as this functionality only works with the g++ compiler.")
  endif()
endif()

if (DO_COV)
  find_program(GCOV_PATH gcov)
  find_program(GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/tests)
  if (NOT GCOV_PATH OR NOT GCOVR_PATH)
    message(WARNING "Unable to enable coverage target as gcov and/or gocvr was not found.")
  else()
    message(STATUS "Generating coverage target.")
    add_custom_target(coverage_base COMMAND ${GCOVR_PATH} "-r" "${CMAKE_SOURCE_DIR}/" "-x" ${gcovr_excl_opts} "-o" "${COVERAGE_RESULTS_PATH}/coverage.xml" DEPENDS runtest)
    add_custom_target(coverage_xml COMMAND ${GCOVR_PATH} "-r" "${CMAKE_SOURCE_DIR}/" "-x" ${gcovr_excl_opts} "-o" "${COVERAGE_RESULTS_PATH}/coverage.xml" DEPENDS runtest)
    add_custom_target(coverage_html COMMAND ${GCOVR_PATH} "-r" "${CMAKE_SOURCE_DIR}/" "--html" "--html-details" ${gcovr_excl_opts} "-o" "${COVERAGE_RESULTS_PATH}/index.html" DEPENDS runtest)
    add_custom_target(coverage COMMAND DEPENDS coverage_base coverage_xml coverage_html)
  endif()
endif()

function(create_test_executable test_name link_libraries)
  set(exec_name ${test_name}_test)

  add_executable(${exec_name} EXCLUDE_FROM_ALL ${${test_name}_SRC} ${${test_name}_INC} )
  target_include_directories(${exec_name} PRIVATE ${GTEST_INCLUDE_DIRS})
  set_target_properties(${exec_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
    "${TEST_BINARIES_PATH}")
  if(DO_COV)
    set_target_properties(${exec_name} PROPERTIES LINK_FLAGS ${coverage_flags})
    set_target_properties(${exec_name} PROPERTIES COMPILE_FLAGS "-g -O0 ${coverage_flags}")
    set(link_libraries ${link_libraries} gcov)
  endif()
  set(link_libraries ${link_libraries} dl)

  target_link_libraries(${exec_name} ${link_libraries} ${GTEST_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT})
  if(${GraylogLogger_FOUND})
    target_link_libraries(${exec_name}  ${GraylogLogger_LIBRARIES})
  endif()

  add_test(NAME regular_${exec_name} COMMAND ${exec_name}
    "--gtest_output=xml:${COVERAGE_RESULTS_PATH}/${exec_name}.xml")
  set(unit_test_targets ${exec_name} ${unit_test_targets} CACHE INTERNAL "All targets")
  if (EXISTS ${VALGRIND_CMD})
    add_test(NAME memcheck_${exec_name} COMMAND ${VALGRIND_CMD} --tool=memcheck --leak-check=full --verbose --xml=yes --xml-file=${MEMCHECK_RESULTS_PATH}/${exec_name}.valgrind ${TEST_BINARIES_PATH}/${exec_name})
  endif()
endfunction(create_test_executable)

function(finalize_tests)
  add_custom_target(runtest COMMAND ${CMAKE_CTEST_COMMAND} -V -R regular_* DEPENDS ${unit_test_targets})
  if (EXISTS ${VALGRIND_CMD})
    file(MAKE_DIRECTORY ${MEMCHECK_RESULTS_PATH})
    add_custom_target(memcheck COMMAND ${CMAKE_CTEST_COMMAND} -R memcheck_* DEPENDS ${unit_test_targets})
  endif()
endfunction(finalize_tests)
