              #'attribute_complex_io_test.cpp',
              #'attribute_pniio_bool_test.cpp') 'attribute_test_fixtures.cpp',
sources=files('attribute_test.cpp',
              'attribute_scalar_io_test.cpp',
              'attribute_multidim_io_test.cpp',
              'attribute_fixed_string_io.cpp',
              'attribute_management_test.cpp',
              'attribute_variable_string_io.cpp',
              'attribute_h5py_bool_test.cpp',
              'attribute_name_access_test.cpp'
             )
headers=files('attribute_test_fixtures.hpp')

attributes_test = executable('attribute_tests', sources,
dependencies: [catch2_dep, h5cpp_dep])
test('run attribute tests', attributes_test, workdir: meson.current_build_dir())