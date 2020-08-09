sources+=files('direct_driver.cpp', 'file.cpp', 'functions.cpp',
               'memory_driver.cpp', 'mpi_driver.cpp',
               'posix_driver.cpp', 'types.cpp')

local_headers=files('file.hpp', 'functions.hpp', 'types.hpp',
                    'driver.hpp', 'direct_driver.hpp', 
                    'memory_driver.hpp', 'posix_driver.hpp',
                    'mpi_driver.hpp')
headers+=local_headers

install_headers(local_headers, subdir: join_paths('h5cpp', 'file'))
