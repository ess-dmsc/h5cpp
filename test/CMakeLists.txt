include_directories(${PROJECT_SOURCE_DIR}/src/include)
set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test)

include(${PROJECT_SOURCE_DIR}/cmake/TestCoverage.cmake)

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

set(Common_SRC main.cpp
  ../src/path.cpp
  ../src/iterator.cpp
  ../src/iterator_config.cpp)
set(Common_INC
  path_test.hpp
  iteration_order_test.hpp
  ../src/include/h5cpp/path.hpp
  ../src/include/h5cpp/iterator.hpp
  ../src/include/h5cpp/iterator_config.hpp)
create_test_executable(Common h5cpp_shared)

#add_library(test_common OBJECT fixture.cpp)
#target_include_directories(test_common PRIVATE ${HDF5_INCLUDE_DIRS})

#add_executable(object_id_test object_id_test.cpp)
#target_link_libraries(object_id_test h5cpp_shared Boost::unit_test_framework)
#add_logging_test("hdf5::ObjectId"
#                 object_id_test
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

