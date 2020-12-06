sources=files('array_adapter_test.cpp')

utilities_test = executable('utilities_test', sources,
                            dependencies: [catch2_dep, h5cpp_dep])
test('run utilties test', utilities_test, workdir: meson.current_build_dir())