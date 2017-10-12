include_directories(${PROJECT_SOURCE_DIR}/src/include)
set(WORKING_DIRECTORY ${PROJECT_BINARY_DIR}/test)

#include(${PROJECT_SOURCE_DIR}/cmake/GoogleTestLogConfig.cmake)
include(${PROJECT_SOURCE_DIR}/cmake/TestCoverage.cmake)

#add_library(test_common OBJECT fixture.cpp)
#target_include_directories(test_common PRIVATE ${HDF5_INCLUDE_DIRS})

#add_executable(object_id_test object_id_test.cpp)
#target_link_libraries(object_id_test h5cpp_shared Boost::unit_test_framework)
#add_logging_test("hdf5::ObjectId"
#                 object_id_test
#                 ${WORKING_DIRECTORY})

set(PathTest_SRC
  gpath_test.cpp
  ../src/path.cpp)
set(PathTest_INC
    ../src/include/h5cpp/path.hpp)
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
finalize_tests()

