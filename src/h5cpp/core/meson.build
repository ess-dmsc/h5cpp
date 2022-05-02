sources+=files('iterator_config.cpp',
               'iterator.cpp', 'object_handle.cpp',
               'object_id.cpp', 'path.cpp', 'version.cpp')
local_headers=files('fixed_length_string.hpp',
                    'hdf5_capi.hpp',
                    'io_buffer.hpp',
                    'iterator_config.hpp',
                    'iterator.hpp',
                    'object_handle.hpp',
                    'object_id.hpp',
                    'path.hpp',
                    'variable_length_string.hpp',
                    'version.hpp',
                    'types.hpp',
                    'windows.hpp',
                    'utilities.hpp')
headers+=local_headers

install_headers(local_headers,subdir: join_paths('h5cpp','core'))