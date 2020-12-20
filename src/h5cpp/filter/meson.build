sources+=files('deflate.cpp', 'filter.cpp', 'fletcher32.cpp', 'nbit.cpp',
               'shuffle.cpp', 'external_filter.cpp')
local_headers=files('filter.hpp', 'types.hpp', 'deflate.hpp', 'nbit.hpp',
                    'fletcher32.hpp', 'shuffle.hpp',
                    'external_filter.hpp')
headers+=local_headers

install_headers(local_headers, subdir: join_paths('h5cpp', 'filter'))