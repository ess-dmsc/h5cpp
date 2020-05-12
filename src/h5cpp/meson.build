sources=[]
headers=[]

subdir('attribute')
subdir('core')
subdir('dataspace')
subdir('datatype')
subdir('error')
subdir('file')
subdir('filter')
subdir('node')
subdir('property')

h5cpp_lib = library('h5cpp',sources,
                    dependencies:[hdf5,boost],
                    include_directories:[srcinc])
h5cpp_dep = declare_dependency(link_with: h5cpp_lib,
                               dependencies: [hdf5,boost],
                               include_directories:[srcinc])