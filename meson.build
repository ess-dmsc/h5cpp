project('h5cpp',['cpp','c'],version:'0.3.3', default_options:'cpp_std=c++17')

hdf5 = dependency('hdf5', language: 'c')
boost = dependency('boost', modules:['filesystem','system'])
srcinc = include_directories('src')

subdir('src/h5cpp')
subdir('test')
install_subdir('examples',
               install_dir: join_paths(get_option('datadir'),'doc','h5cpp'))