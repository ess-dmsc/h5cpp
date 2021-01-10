sources = files('hklpoint.cpp')

example_lib = library('h5cpp-examples',sources)

#
# assemble dependencies
#
example_dep = declare_dependency(
    link_with: example_lib,
    include_directories: include_directories('..')
)
