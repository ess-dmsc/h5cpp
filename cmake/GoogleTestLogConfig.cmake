
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

