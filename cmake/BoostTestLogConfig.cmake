#
# setting up variables and providing macros to setup looging when
# using the Boost unit test framework
#

if(NOT Boost_VERSION)
    message(FATAL_ERROR "Cannot setup Boost test logging as long as Boost is not configured!")
endif()

#
# set the path where all the test reports and logs will be stored
#
set(TEST_LOG_PATH    ${PROJECT_BINARY_DIR}/test/logs)
set(TEST_REPORT_PATH ${PROJECT_BINARY_DIR}/test/logs)

#
# macro adding a test including all command line options to write logging files
#
macro (add_logging_test test_name test_target working_dir)
    set(TEST_LOG_FILE    ${TEST_LOG_PATH}/${test_target}.log.xml)
    set(TEST_REPORT_FILE ${TEST_REPORT_PATH}/${test_target}.report.xml)

    #we need to create separate options configurations depending on the Boost
    #version installed
    if(Boost_VERSION EQUAL 106200)
        message(STATUS "Setting up test for Boost Unit test version 1.62")
        message(STATUS " .. Due to a bug in 1.62 there will be no reporting but only logs")
        if(NOT (CMAKE_HOST_SYSTEM_NAME MATCHES Windows))
            set(LOG_OPTIONS --logger=XML,all,${TEST_LOG_FILE})
        endif()
        #set(REPORT_OPTIONS --report_level=detailed --report_format=XML --report_sink=${TEST_REPORT_FILE})
    else()
        set(LOG_OPTIONS --log_level=all --log_sink=${TEST_LOG_FILE})
        set(REPORT_OPTIONS --report_level=detailed --report_sink=${TEST_REPORT_FILE})
        if(Boost_VERSION LESS 106000)
            list(APPEND LOG_OPTIONS "--log_format=xml")
            list(APPEND REPORT_OPTIONS "--report_format=xml")
        else()
            list(APPEND LOG_OPTIONS "--log_format=XML")
            list(APPEND LOG_OPTIONS "--report_format=XML")
        endif()
    endif()

    add_test(NAME "${test_name}"
             COMMAND ${test_target} ${LOG_OPTIONS} ${REPORT_OPTIONS}
             WORKING_DIRECTORY ${working_dir})
    #in all cases we have to remove the log and report files
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
    ${TEST_LOG_FILE} ${TEST_REPORT_FILE})

endmacro()
