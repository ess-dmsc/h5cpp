sources=files('searchflags_test.cpp',
                    'accessflags_test.cpp',
                    'scope_test.cpp',
                    'file_test.cpp',
                    'file_image_test.cpp',
                    'file_creation_test.cpp',
                    'file_open_test.cpp',
                    'file_close_test.cpp',
                    'is_hdf5_test.cpp',
                    'driver_test.cpp')

file_test = executable('file_test', sources,
                       dependencies: [h5cpp_dep, catch2_dep])
test('run file test', file_test, workdir: meson.current_build_dir())