include_directories(${PROJECT_SOURCE_DIR}/src/include)
set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test)

#include(${PROJECT_SOURCE_DIR}/cmake/GoogleTestLogConfig.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/TestCoverage.cmake)

#add_library(test_common OBJECT fixture.cpp)
#target_include_directories(test_common PRIVATE ${HDF5_INCLUDE_DIRS})

## Add line:
##   #include <gtest/gtest.h>
## Change these:
##   BOOST_CHECK( --> EXPECT_TRUE(
##   BOOST_CHECK_EQUAL( --> EXPECT_EQ(
##   BOOST_AUTO_TEST_CASE( --> TEST(TestName,
##
## At the end:
# int main(int argc, char **argv)
#{
#  ::testing::InitGoogleTest(&argc, argv);
#  return RUN_ALL_TESTS();
#}

#add_executable(object_id_test object_id_test.cpp)
#target_link_libraries(object_id_test h5cpp_shared Boost::unit_test_framework)
#add_logging_test("hdf5::ObjectId"
#                 object_id_test
#                 ${WORKING_DIRECTORY})

set(Path_SRC path_test.cpp
  ../src/path.cpp)
set(Path_INC
  ../src/include/h5cpp/path.hpp)
create_test_executable(Path h5cpp_shared)

set(IterationOrder_SRC iteration_order_test.cpp
  ../src/iterator.cpp
  ../src/iterator_config.cpp)
set(IterationOrder_INC
  ../src/include/h5cpp/iterator.hpp
  ../src/include/h5cpp/iterator_config.hpp)
create_test_executable(IterationOrder h5cpp_shared)

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
finalize_tests()

