sources=files('datatype_test.cpp'
              ,'integer_test.cpp'
              ,'compound_test.cpp'
              ,'float_test.cpp'
              ,'string_test.cpp'
               #,'type_test.cpp'
               #,'type_trait_test.cpp'
               #,'datatype_test.cpp'
               #,'array_test.cpp'
               #,'vlen_array_test.cpp'
               #,'enum_test.cpp'
               )

datatype_test = executable('datatype_test', sources,
    dependencies: [catch2_dep, h5cpp_dep])
test('run datatype tests', datatype_test, workdir: meson.current_build_dir())