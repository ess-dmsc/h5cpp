sources+=files('property_class.cpp', 'property_list.cpp',       
               'attribute_creation.cpp', 'creation_order.cpp',
               'dataset_access.cpp', 'dataset_creation.cpp',
               'dataset_transfer.cpp', 'datatype_access.cpp',
               'file_access.cpp', 'file_creation.cpp',
               'file_mount.cpp', 'group_access.cpp',
               'group_creation.cpp', 'link_access.cpp',
               'link_creation.cpp', 'object_copy.cpp',
               'object_creation.cpp', 'string_creation.cpp',
               'type_creation.cpp', 'virtual_data_map.cpp')

local_headers=files('property_class.hpp', 'property_list.hpp',
                    'attribute_creation.hpp', 'creation_order.hpp',
                    'dataset_access.hpp', 'dataset_creation.hpp',
                    'dataset_transfer.hpp', 'datatype_access.hpp',
                    'file_access.hpp', 'file_creation.hpp',
                    'file_mount.hpp', 'group_access.hpp',
                    'group_creation.hpp', 'link_access.hpp',
                    'link_creation.hpp', 'object_copy.hpp',
                    'object_creation.hpp', 'string_creation.hpp',
                    'type_creation.hpp', 'virtual_data_map.hpp') 
headers+=local_headers

install_headers(local_headers, subdir: join_paths('h5cpp', 'property'))