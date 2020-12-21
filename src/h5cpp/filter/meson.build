sources+=files('deflate.cpp', 'filter.cpp', 'fletcher32.cpp', 'nbit.cpp',
               'scaleoffset.cpp', 'shuffle.cpp', 'szip.cpp', 'external_filter.cpp')
local_headers=files('filter.hpp', 'types.hpp', 'deflate.hpp', 'nbit.hpp',
                    'fletcher32.hpp',  'scaleoffset.cpp', 'shuffle.hpp', 'szip.hpp',
                    'external_filter.hpp')
headers+=local_headers

install_headers(local_headers, subdir: join_paths('h5cpp', 'filter'))