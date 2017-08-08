
set(SOURCE ObjectHandleDefault.cpp)


add_executable(ObjectHandleTest ${SOURCE})
target_link_libraries(ObjectHandleTest 
  ${HDF5_LIBRARIES} h5cpp_shared Boost::unit_test_framework)


add_logging_test("ObjectHandle::Test"
                 ObjectHandleTest
                 ${PROJECT_BINARY_DIR}/test/ObjectHandle)
