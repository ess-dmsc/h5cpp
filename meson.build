project('h5cpp',['cpp','c'],version:'0.3.3',
        default_options:'cpp_std=c++17')

with_mpi = get_option('with-mpi')
# check if 
if with_mpi
 mpi_dep = dependency('mpi', language:'c')
 hdf5 = dependency('hdf5', language:'c')
 add_project_arguments('-DWIHT_MPI', language: 'cpp')
else
 hdf5 = dependency('hdf5', language: 'c')
endif


boost = dependency('boost', modules:['filesystem','system'])
srcinc = include_directories('src')
catch2_dep = declare_dependency(include_directories:'subprojects/catch2/include')



subdir('src/h5cpp')
subdir('test')
install_subdir('examples',
               install_dir: join_paths(get_option('datadir'),'doc','h5cpp'))