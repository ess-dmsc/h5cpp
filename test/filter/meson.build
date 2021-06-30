sources=files('deflate_test.cpp'
		      ,'scaleoffset_test.cpp'
              ,'shuffle_test.cpp'
		      ,'szip_test.cpp'
              ,'fletcher32_test.cpp'
              ,'nbit_test.cpp'
              ,'external_filter_test.cpp'
              )
filter_test = executable('filter_test', sources, dependencies: [h5cpp_dep, catch2_dep])
test('run filter test', filter_test, workdir: meson.current_build_dir())