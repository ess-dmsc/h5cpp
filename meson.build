project('h5cpp',['cpp','c'],version:'0.4.1', default_options:'cpp_std=c++17')

h5cpp_dependencies = []
# -----------------------------------------------------------------------------
# check if the with mpi option was set
# -----------------------------------------------------------------------------
if get_option('with-mpi')
 h5cpp_dependencies += dependency('mpi-cxx', method: 'pkg-config')
 add_project_arguments('-DH5CPP_WITH_MPI', language: 'cpp')
endif

# -----------------------------------------------------------------------------
# setting up the HDF5 dependency
# -----------------------------------------------------------------------------
h5cpp_dependencies += dependency('hdf5', language: 'c')

# -----------------------------------------------------------------------------
# setting up the boost dependencies
# -----------------------------------------------------------------------------
boost_modules = ['system']
if get_option('with-boostfilesystem') 
  boost_modules += 'filesystem'
  add_project_arguments('-DH5CPP_WITH_BOOST', language: 'cpp')
  summary()
endif

h5cpp_dependencies += dependency('boost', modules:boost_modules)
srcinc = include_directories('src')

catch2_dep = declare_dependency(include_directories:'subprojects/catch2/include')




subdir('src/h5cpp')
subdir('test')
install_subdir('examples',
               install_dir: join_paths(get_option('datadir'),'doc','h5cpp'))
