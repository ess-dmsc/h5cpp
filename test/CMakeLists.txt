include_directories(${PROJECT_SOURCE_DIR}/src/include)
set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test)

include(${PROJECT_SOURCE_DIR}/cmake/TestCoverage.cmake)
find_package(GTest)

## Add line:
##   #include <gtest/gtest.h>
## Change these:
##   BOOST_CHECK_EQUAL( --> EXPECT_EQ(
##   BOOST_CHECK( --> EXPECT_TRUE(
##   BOOST_AUTO_TEST_CASE( --> TEST(TestName,
##
## At the end:
# int main(int argc, char **argv)
#{
#  ::testing::InitGoogleTest(&argc, argv);
#  return RUN_ALL_TESTS();
#}

set(Common_SRC 
    main.cpp
    iteration_index_test.cpp
    iteration_order_test.cpp
    object_id_test.cpp
    path_test.cpp
)
set(Common_INC
    
)

add_executable(unit_tests ${Common_SRC} ${Common_INC})
add_dependencies(unit_tests h5cpp_unit_test)
target_include_directories(unit_tests PRIVATE ${GTEST_INCLUDE_DIRS} h5cpp_unit_test)
target_link_libraries(unit_tests h5cpp_unit_test ${GTEST_LIBRARIES})

add_custom_target(run_tests COMMAND unit_tests "--gtest_output=xml:unit_tests_run.xml" DEPENDS unit_tests)

set(COVERAGE_RESULTS_PATH ${PROJECT_BINARY_DIR}/test/)

find_program(GCOV_PATH gcov)
find_program(GCOVR_PATH gcovr PATHS ${CMAKE_SOURCE_DIR}/test)
if (NOT GCOV_PATH OR NOT GCOVR_PATH)
      message(WARNING "Unable to enable coverage target as gcov and/or gocvr was not found.")
else()
    add_custom_target(generate_coverage COMMAND ${GCOVR_PATH} "-r" "${CMAKE_SOURCE_DIR}/src" "-x" "${PROJECT_BINARY_DIR}" "-o" "${COVERAGE_RESULTS_PATH}/coverage.xml" DEPENDS run_tests)
endif()

#create_test_executable(Common h5cpp_shared)

#add_library(test_common OBJECT fixture.cpp)
#target_include_directories(test_common PRIVATE ${HDF5_INCLUDE_DIRS})

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
#finalize_tests()

