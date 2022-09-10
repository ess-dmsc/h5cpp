pkg = import('pkgconfig')
sources=[]
headers=files('hdf5.hpp')

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

# reamarks:
# - symbolic links to the so version are onl made when using the soversio
#   argument
# - mode must be given explicitely to avoid the library to be installed as 
#   executable
# - we carefully have to distinguish between soversion and library version.
#   however, if both are set properly all symbolic links are created correclty
#   during installation 
h5cpp_lib = library('h5cpp',sources,
                    dependencies:h5cpp_dependencies,
                    include_directories:[srcinc],
                    version: '0.5.1',
                    soversion:'1',
                    install:true,
                    install_mode:'r--r--r--')
h5cpp_dep = declare_dependency(link_with: h5cpp_lib,
                               dependencies: h5cpp_dependencies,
                               include_directories:[srcinc])
install_headers('hdf5.hpp', subdir:'h5cpp')

pkg.generate(h5cpp_lib,
             libraries: h5cpp_dependencies,
             install_dir: join_paths(get_option('libdir'),'pkgconfig'))