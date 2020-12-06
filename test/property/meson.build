test_sources=files('property_class_test.cpp',
                   #,'property_list_test.cpp'
                   #,'creation_order_test.cpp'
                   #,'object_creation_test.cpp'
                   #,'dataset_creation_test.cpp'
                   #,'type_creation_test.cpp'
                   #,'group_creation_test.cpp'
                   #,'file_creation_test.cpp'
                   #,'link_access_test.cpp'
                   #,'chunk_cache_parameters_test.cpp'
                   #,'dataset_access_test.cpp'
                   #,'datatype_access_test.cpp'
                   #,'group_access_test.cpp'
                   #,'string_creation_test.cpp'
                   #,'attribute_creation_test.cpp'
                   #,'link_creation_test.cpp'
                   #,'dataset_transfer_test.cpp'
                   #,'file_access_test.cpp'
                   #,'file_mount_test.cpp'
                   #,'object_copy_test.cpp'
                   )

properties_test = executable('properties_test', test_sources,
                            dependencies: [catch2_dep, h5cpp_dep])
test('run properties test', properties_test, workdir: meson.current_build_dir())