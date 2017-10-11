#
# setting up variables and providing macros to setup looging when
# using the Google's unit test framework
#

find_package(Threads)
find_package(GTest)

#
# set the path where all the test reports and logs will be stored
#
set(TEST_RESULTS_PATH    ${PROJECT_BINARY_DIR}/test/logs)

#
# macro adding a test including all command line options to write logging files
#
macro (add_glogging_test test_name test_target working_dir)
    set(TEST_RESULTS_FILE    ${TEST_RESULTS_PATH}/${test_target}_test.xml)

    #we need to create separate options configurations depending on the Boost
    #version installed
    set(LOG_OPTIONS --gtest_output=xml:${TEST_RESULTS_FILE})

    add_test(NAME "${test_name}"
             COMMAND ${test_target} #${LOG_OPTIONS}
             WORKING_DIRECTORY ${working_dir})
    #in all cases we have to remove the log and report files
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${TEST_RESULTS_FILE})

endmacro()

set(unit_test_targets "" CACHE INTERNAL "All targets")
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
