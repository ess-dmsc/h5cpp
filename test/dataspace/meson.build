sources=files('dataspace_test.cpp'
               ,'scalar_test.cpp'
               ,'simple_test.cpp'
               ,'hyperslab_simple_test.cpp'
               ,'points_simple_test.cpp'
               ,'type_trait_test.cpp'
               ,'selection_operator_set.cpp'
               ,'selection_manager_test.cpp'
               ,'view_test.cpp'
               ,'type_test.cpp'
               )
dataspace_test = executable('dataspace_test', sources,
                            dependencies: [catch2_dep, h5cpp_dep])
test('run dataspace test', dataspace_test, workdir: meson.current_build_dir())