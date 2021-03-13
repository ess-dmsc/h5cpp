project('h5cpp',['cpp','c'],version:'0.4.0',
        default_options:'cpp_std=c++17')

h5cpp_dependencies = []
# -----------------------------------------------------------------------------
# check if the with mpi option was set
# -----------------------------------------------------------------------------
if get_option('with-mpi')
 mpi_cxx = dependency('mpi-cxx', method: 'pkg-config')
 h5cpp_dependencies += [mpi_cxx]
 add_project_arguments('-DWITH_MPI', language: 'cpp')
endif

# -----------------------------------------------------------------------------
# setting up the HDF5 dependency
# -----------------------------------------------------------------------------
hdf5 = dependency('hdf5', language: 'c')
h5cpp_dependencies += [hdf5]

# -----------------------------------------------------------------------------
# setting up the boost dependencies
# -----------------------------------------------------------------------------
boost = dependency('boost', modules:['filesystem','system'])
srcinc = include_directories('src')

catch2_dep = declare_dependency(include_directories:'subprojects/catch2/include')

h5cpp_dependencies += [boost]



subdir('src/h5cpp')
subdir('test')
install_subdir('examples',
               install_dir: join_paths(get_option('datadir'),'doc','h5cpp'))