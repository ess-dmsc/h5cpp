sources=files(#'ObjectHandleDefault.cpp',
              #'object_handle_test.cpp',
              #'file_object_handle_test.cpp',
              #'datatype_object_handle_test.cpp',
              #'dataspace_object_handle_test.cpp',
              #'group_object_handle_test.cpp',
              #'dataset_object_handle_test.cpp',
              #'attribute_object_handle_test.cpp',
              #'property_objects_handle_test.cpp',
              #'error_objects_handle_test.cpp',
              #'test_environment.cpp',
              'iteration_index_test.cpp',
              'iteration_order_test.cpp',
              'iterator_test.cpp',
              'object_id_test.cpp',
              'path_test.cpp',
              'version_test.cpp')

headers=files('object_handle_test.hpp')

core_test = executable('core_test', sources,
                       dependencies: [catch2_dep,h5cpp_dep])
test('run core test', core_test, workdir: meson.current_build_dir())
