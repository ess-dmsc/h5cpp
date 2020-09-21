
set(test_sources 
    #ObjectHandleDefault.cpp
    #object_handle_test.cpp
    #file_object_handle_test.cpp
    #datatype_object_handle_test.cpp
    #dataspace_object_handle_test.cpp
    #group_object_handle_test.cpp
    #dataset_object_handle_test.cpp
    #attribute_object_handle_test.cpp
    #property_objects_handle_test.cpp
    #error_objects_handle_test.cpp
    #test_environment.cpp
    iteration_index_test.cpp
    #iteration_order_test.cpp
    #iterator_test.cpp
    #object_id_test.cpp
    path_test.cpp
    version_test.cpp)


add_executable(core_test ${test_sources})
target_link_libraries(core_test h5cpp)
add_test(NAME "testing core components" COMMAND core_test)
#set(test_headers
#  ${test_headers}
#  ${dir}/object_handle_test.hpp
#  PARENT_SCOPE)

