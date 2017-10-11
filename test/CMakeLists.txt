include_directories(${PROJECT_SOURCE_DIR}/src/include)
set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test)

include(${PROJECT_SOURCE_DIR}/cmake/BoostTestLogConfig.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/GoogleTestLogConfig.cmake)

#add_library(test_common OBJECT fixture.cpp)
#target_include_directories(test_common PRIVATE ${HDF5_INCLUDE_DIRS})

#add_executable(object_id_test object_id_test.cpp)
#target_link_libraries(object_id_test h5cpp_shared Boost::unit_test_framework)
#add_logging_test("hdf5::ObjectId"
#                 object_id_test
#                 ${WORKING_DIRECTORY})

set(PathTest_SRC
  gpath_test.cpp)
#set(PathTest_INC)
create_test_executable(PathTest h5cpp_shared)

#add_executable(gpath_test gpath_test.cpp)
#target_link_libraries(gpath_test h5cpp_shared ${GTEST_BOTH_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
#add_glogging_test("hdf5::GPath"
#                  gpath_test
#                  ${WORKING_DIRECTORY})

#add_executable(hdf5_path_test path_test.cpp)
#target_link_libraries(hdf5_path_test h5cpp_shared Boost::unit_test_framework)
#add_logging_test("hdf5::Path"
#                 hdf5_path_test
#                 ${WORKING_DIRECTORY})
                
#add_executable(iteration_order_test iteration_order_test.cpp)
#target_link_libraries(iteration_order_test h5cpp_shared Boost::unit_test_framework)
#add_logging_test("hdf5::IterationOrder"
#                 iteration_order_test
#                 ${WORKING_DIRECTORY})
                
#add_executable(iteration_index_test iteration_index_test.cpp)
#target_link_libraries(iteration_index_test h5cpp_shared Boost::unit_test_framework)
#add_logging_test("hdf5::IterationIndex"
#                 iteration_index_test
#                 ${WORKING_DIRECTORY})

#add_subdirectory(ObjectHandle)
#add_subdirectory(property)
#add_subdirectory(datatype)
#add_subdirectory(dataspace)
#add_subdirectory(logs)
#add_subdirectory(file)
#add_subdirectory(node)
#add_subdirectory(attribute)
#add_subdirectory(examples)

#
#  These commands must be at the end of this file
#
set(gcovr_excl_opts "-e .*_test.cpp -e .*gtest.*.h -e .*_generated.h" )
separate_arguments(gcovr_excl_opts)
add_custom_target(runtest COMMAND ${CMAKE_CTEST_COMMAND} -V -R regular_* DEPENDS ${unit_test_targets})
add_custom_target(valgrind COMMAND ${CMAKE_CTEST_COMMAND} -R memcheck_*  DEPENDS ${unit_test_targets})
if (DO_COV)
    find_program(GCOV_PATH gcov)
    find_program(GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/tests)
    if (NOT GCOV_PATH OR NOT GCOVR_PATH)
        message(WARNING "Unable to enable coverage target as gcov and/or gocvr was not found.")
    else()
        message(STATUS "Generating coverage target.")
        add_custom_target(coverage COMMAND ${GCOVR_PATH} "-r" "${CMAKE_SOURCE_DIR}/" "-x" ${gcovr_excl_opts} "-o" "${CMAKE_BINARY_DIR}/coverage/cov.xml" DEPENDS runtest)
        add_custom_target(coverage_xml COMMAND ${GCOVR_PATH} "-r" "${CMAKE_SOURCE_DIR}/" "-x" ${gcovr_excl_opts} "-o" "${CMAKE_BINARY_DIR}/coverage/cov.xml")
        add_custom_target(coverage_html COMMAND ${GCOVR_PATH} "-r" "${CMAKE_SOURCE_DIR}/" "--html" "--html-details" ${gcovr_excl_opts} "-o" "${CMAKE_BINARY_DIR}/coverage/index.html")
    endif()
endif()
