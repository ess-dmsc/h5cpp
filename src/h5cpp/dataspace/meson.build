
sources+=files('hyperslab.cpp','dataspace.cpp', 'scalar.cpp',
               'selection.cpp', 'selection_manager.cpp', 'simple.cpp',
               'type.cpp', 'view.cpp', 'points.cpp', pool.cpp)

local_headers=files('hyperslab.hpp', 'dataspace.hpp', 'scalar.hpp',
                    'selection_manager.hpp', 'selection.hpp', 'simple.hpp',
                    'type.hpp', 'type_trait.hpp', 'view.hpp', 'points.hpp', 'pool.hpp')
headers+=local_headers

install_headers(headers, subdir:join_paths('h5cpp', 'dataspace'))
