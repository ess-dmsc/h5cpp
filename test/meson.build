# ---------------------------------------------------------------------
# copy required data files to the build directory
# ---------------------------------------------------------------------
configure_file(input: 'h5py_test_data.h5',
               output: 'h5py_test_data.h5', copy:true)
configure_file(input: 'h5py_test_boolattr.h5',
               output: 'h5py_test_boolattr.h5', copy:true)
configure_file(input: 'pniio_test_boolattr.h5',
               output: 'pniio_test_boolattr.h5', copy:true)



subdir('examples')
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