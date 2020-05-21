
sources+=files('array.cpp', 'compound.cpp', 'datatype.cpp',
               'float.cpp', 'integer.cpp', 'string.cpp',
               'types.cpp', 'enum.cpp', 'ebool.cpp')

local_headers=files('datatype.hpp', 'factory.hpp', 'float.hpp',
                    'integer.hpp', 'type_trait.hpp', 'types.hpp',
                    'compound.hpp', 'string.hpp', 'array.hpp',
                    'enum.hpp', 'ebool.hpp')
headers+=local_headers

install_headers(local_headers, subdir: join_paths('h5cpp', 'datatype'))
