gtest_dep = dependency('gtest')

# ---------------------------------------------------------------------
# copy required data files to the build directory
# ---------------------------------------------------------------------
configure_file(input: 'h5py_test_data.h5',
               output: 'h5py_test_data.h5', copy:true)
configure_file(input: 'h5py_test_boolattr.h5',
               output: 'h5py_test_boolattr.h5', copy:true)
configure_file(input: 'pniio_test_boolattr.h5',
               output: 'pniio_test_boolattr.h5', copy:true)


test_sources = files('fixture.cpp', 'main.cpp')
test_headers = files('fixture.hpp', 'h5cpp_test_helpers.hpp')

subdir('attribute')
subdir('core')
subdir('dataspace')
subdir('datatype')
subdir('error')
subdir('file')
subdir('filter')
subdir('node')
subdir('property')
subdir('utilities')

test=executable('unit_test', test_sources,
                dependencies: [h5cpp_dep, gtest_dep])
test('run unit tests', test,
     workdir: meson.current_build_dir())