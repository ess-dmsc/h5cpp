#
# setting up variables and providing macros to setup looging when
# using the Google's unit test framework and gcc code coverage
#

find_package(Threads)
find_package(GTest)

option(COV "Enable code coverage test for unit tests (if possible)." OFF)

set(coverage_flags "-coverage -fprofile-generate")
set(gcovr_excl_opts "-e .*_test.cpp -e .*gtest.*.h -e .*_generated.h" )
separate_arguments(gcovr_excl_opts)

enable_testing()

set(DO_COV OFF)
mark_as_advanced(DO_COV)

set(unit_test_targets "" CACHE INTERNAL "All targets")

if (${COV})
    if (${CMAKE_COMPILER_IS_GNUCXX})
        message(STATUS "Code coverage enabled.")
        set(DO_COV ON)
        set(CMAKE_BUILD_TYPE Debug)
    else()
        message(FATAL_ERROR "Unable to enable code coverage as this functionality only works with the g++ compiler.")
    endif()
endif()

function(create_test_executable exec_name link_libraries)
    # message(STATUS ${exec_name})
    # message(STATUS ${unit_test_targets})
    add_executable(${exec_name} EXCLUDE_FROM_ALL ${${exec_name}_SRC}
                   ${${exec_name}_INC} )
    target_include_directories(${exec_name} PRIVATE ${GTEST_INCLUDE_DIRS})
    set_target_properties(${exec_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY
                          "${CMAKE_BINARY_DIR}/unit_tests")
    if(DO_COV)
        set_target_properties(${exec_name} PROPERTIES LINK_FLAGS ${coverage_flags})
        set_target_properties(${exec_name} PROPERTIES COMPILE_FLAGS "-g -O0
                              ${coverage_flags}")
        set(link_libraries ${link_libraries} gcov)
    endif()
    set(link_libraries ${link_libraries} dl)

    target_link_libraries(${exec_name} ${link_libraries} ${GTEST_LIBRARIES}
                          ${CMAKE_THREAD_LIBS_INIT})
    if(${GraylogLogger_FOUND})
        target_link_libraries(${exec_name}  ${GraylogLogger_LIBRARIES})
    endif()

    add_test(NAME regular_${exec_name} COMMAND ${exec_name}
             "--gtest_output=xml:${CMAKE_BINARY_DIR}/test_results/${exec_name}test.xml")
    set(unit_test_targets ${exec_name} ${unit_test_targets} CACHE INTERNAL "All targets")
    if (EXISTS ${VALGRIND_CMD})
        add_test(NAME memcheck_${exec_name} COMMAND ${VALGRIND_CMD} --tool=memcheck
                 --leak-check=full --verbose --xml=yes
                 --xml-file=${CMAKE_BINARY_DIR}/memcheck_res/${exec_name}test.valgrind
                 ${CMAKE_BINARY_DIR}/unit_tests/${exec_name})
    endif()
endfunction(create_test_executable)

#function(create_test_executable exec_name link_libraries)
  if (DO_COV)
      find_program(GCOV_PATH gcov)
      find_program(GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/tests)
      if (NOT GCOV_PATH OR NOT GCOVR_PATH)
          message(WARNING "Unable to enable coverage target as gcov and/or gocvr was not found.")
      else()
          message(STATUS "Generating coverage target.")
          add_custom_target(coverage COMMAND ${GCOVR_PATH}
                            "-r" "${CMAKE_SOURCE_DIR}/" "-x" ${gcovr_excl_opts}
                            "-o" "${CMAKE_BINARY_DIR}/coverage/cov.xml"
                            DEPENDS runtest)
          add_custom_target(coverage_xml COMMAND ${GCOVR_PATH}
                            "-r" "${CMAKE_SOURCE_DIR}/" "-x" ${gcovr_excl_opts}
                            "-o" "${CMAKE_BINARY_DIR}/coverage/cov.xml")
          add_custom_target(coverage_html COMMAND ${GCOVR_PATH}
                            "-r" "${CMAKE_SOURCE_DIR}/" "--html"
                            "--html-details" ${gcovr_excl_opts}
                            "-o" "${CMAKE_BINARY_DIR}/coverage/index.html")
      endif()
  endif()
#endfunction(create_test_executable)
