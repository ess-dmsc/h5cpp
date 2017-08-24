
set(SOURCE ObjectHandleDefault.cpp
           object_handle_test.cpp
           file_object_handle_test.cpp
           datatype_object_handle_test.cpp
           dataspace_object_handle_test.cpp
           group_object_handle_test.cpp
           dataset_object_handle_test.cpp
           attribute_object_handle_test.cpp
           property_objects_handle_test.cpp
           error_objects_handle_test.cpp
           test_environment.cpp)


add_executable(ObjectHandleTest ${SOURCE})
add_coverage(ObjectHandleTest)
target_link_libraries(ObjectHandleTest 
  ${HDF5_LIBRARIES} h5cpp_shared Boost::unit_test_framework)


add_logging_test("ObjectHandle::Test"
                 ObjectHandleTest
                 ${PROJECT_BINARY_DIR}/test/ObjectHandle)
