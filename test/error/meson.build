sources=files('descriptor_test.cpp'
              ,'h5c_error_test.cpp'
              ,'error_test.cpp')
error_test = executable('error_test', sources, dependencies: [h5cpp_dep, catch2_dep])
test('run error test', error_test, workdir: meson.current_build_dir())