project('h5cpp',['cpp','c'],version:'0.3.3')

hdf5 = dependency('hdf5')
boost = dependency('boost', modules:['filesystem','system'])
srcinc = include_directories('src')

subdir('src/h5cpp')
subdir('test')