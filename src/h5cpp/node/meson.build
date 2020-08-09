sources+=files('dataset.cpp', 'functions.cpp', 'group.cpp',
               'group_view.cpp', 'link.cpp', 'link_iterator.cpp',
               'link_view.cpp', 'node.cpp', 'node_iterator.cpp',
               'node_view.cpp', 'types.cpp', 'virtual_dataset.cpp',
               'chunked_dataset.cpp', 'recursive_node_iterator.cpp',
               'recursive_link_iterator.cpp')

local_headers=files('dataset.hpp', 'group_view.hpp','group.hpp',
                    'link_view.hpp', 'link.hpp', 'node.hpp',
                    'node_iterator.hpp', 'link_iterator.hpp', 
                    'node_view.hpp', 'functions.hpp', 'types.hpp',
                    'virtual_dataset.hpp', 'chunked_dataset.hpp',
                    'recursive_node_iterator.hpp',
                    'recursive_link_iterator.hpp')
headers+=local_headers

install_headers(local_headers, subdir: join_paths('h5cpp', 'node'))