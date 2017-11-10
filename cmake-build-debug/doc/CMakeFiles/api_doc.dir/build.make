# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/bdv/software/clion-2017.2.3/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/bdv/software/clion-2017.2.3/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/bdv/dev/h5cpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/bdv/dev/h5cpp/cmake-build-debug

# Utility rule file for api_doc.

# Include the progress variables for this target.
include doc/CMakeFiles/api_doc.dir/progress.make

doc/CMakeFiles/api_doc: doc/doxygen.stamp


doc/doxygen.stamp: doc/Doxyfile
doc/doxygen.stamp: ../doc/groups.dox
doc/doxygen.stamp: ../doc/mainpage.dox
doc/doxygen.stamp: ../doc/namespaces.dox
doc/doxygen.stamp: ../src/include/h5cpp/object_handle.hpp
doc/doxygen.stamp: ../src/include/h5cpp/windows.hpp
doc/doxygen.stamp: ../src/include/h5cpp/types.hpp
doc/doxygen.stamp: ../src/include/h5cpp/path.hpp
doc/doxygen.stamp: ../src/include/h5cpp/iterator_config.hpp
doc/doxygen.stamp: ../src/include/h5cpp/iterator.hpp
doc/doxygen.stamp: ../src/include/h5cpp/object_id.hpp
doc/doxygen.stamp: ../src/include/h5cpp/hdf5.hpp
doc/doxygen.stamp: ../src/include/h5cpp/hdf5_capi.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/attribute_creation_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/class.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/creation_order.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/dataset_access_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/dataset_creation_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/dataset_transfer_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/datatype_access_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/file_access_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/file_creation_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/file_mount_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/group_access_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/group_creation_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/link_access_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/link_creation_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/object_creation_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/string_creation_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/type_creation_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/property/object_copy_list.hpp
doc/doxygen.stamp: ../src/include/h5cpp/dataspace/dataspace.hpp
doc/doxygen.stamp: ../src/include/h5cpp/dataspace/scalar.hpp
doc/doxygen.stamp: ../src/include/h5cpp/dataspace/selection_manager.hpp
doc/doxygen.stamp: ../src/include/h5cpp/dataspace/selection.hpp
doc/doxygen.stamp: ../src/include/h5cpp/dataspace/simple.hpp
doc/doxygen.stamp: ../src/include/h5cpp/dataspace/type.hpp
doc/doxygen.stamp: ../src/include/h5cpp/dataspace/type_trait.hpp
doc/doxygen.stamp: ../src/include/h5cpp/datatype/datatype.hpp
doc/doxygen.stamp: ../src/include/h5cpp/datatype/factory.hpp
doc/doxygen.stamp: ../src/include/h5cpp/datatype/float.hpp
doc/doxygen.stamp: ../src/include/h5cpp/datatype/integer.hpp
doc/doxygen.stamp: ../src/include/h5cpp/datatype/type_trait.hpp
doc/doxygen.stamp: ../src/include/h5cpp/datatype/types.hpp
doc/doxygen.stamp: ../src/include/h5cpp/datatype/compound.hpp
doc/doxygen.stamp: ../src/include/h5cpp/datatype/string.hpp
doc/doxygen.stamp: ../src/include/h5cpp/datatype/array.hpp
doc/doxygen.stamp: ../src/include/h5cpp/node/dataset.hpp
doc/doxygen.stamp: ../src/include/h5cpp/node/group_view.hpp
doc/doxygen.stamp: ../src/include/h5cpp/node/group.hpp
doc/doxygen.stamp: ../src/include/h5cpp/node/link_view.hpp
doc/doxygen.stamp: ../src/include/h5cpp/node/link.hpp
doc/doxygen.stamp: ../src/include/h5cpp/node/node.hpp
doc/doxygen.stamp: ../src/include/h5cpp/node/node_iterator.hpp
doc/doxygen.stamp: ../src/include/h5cpp/node/link_iterator.hpp
doc/doxygen.stamp: ../src/include/h5cpp/node/node_view.hpp
doc/doxygen.stamp: ../src/include/h5cpp/node/functions.hpp
doc/doxygen.stamp: ../src/include/h5cpp/node/types.hpp
doc/doxygen.stamp: ../src/include/h5cpp/file/file.hpp
doc/doxygen.stamp: ../src/include/h5cpp/file/functions.hpp
doc/doxygen.stamp: ../src/include/h5cpp/file/types.hpp
doc/doxygen.stamp: ../src/include/h5cpp/file/driver.hpp
doc/doxygen.stamp: ../src/include/h5cpp/file/direct_driver.hpp
doc/doxygen.stamp: ../src/include/h5cpp/file/memory_driver.hpp
doc/doxygen.stamp: ../src/include/h5cpp/file/posix_driver.hpp
doc/doxygen.stamp: ../src/include/h5cpp/file/mpi_driver.hpp
doc/doxygen.stamp: ../src/include/h5cpp/attribute/attribute_iterator.hpp
doc/doxygen.stamp: ../src/include/h5cpp/attribute/attribute_manager.hpp
doc/doxygen.stamp: ../src/include/h5cpp/attribute/attribute.hpp
doc/doxygen.stamp: ../src/include/h5cpp/error/error.hpp
doc/doxygen.stamp: ../src/include/h5cpp/filter/filter.hpp
doc/doxygen.stamp: ../src/include/h5cpp/filter/types.hpp
doc/doxygen.stamp: ../src/include/h5cpp/filter/deflate.hpp
doc/doxygen.stamp: ../src/include/h5cpp/filter/fletcher32.hpp
doc/doxygen.stamp: ../src/include/h5cpp/filter/shuffle.hpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/bdv/dev/h5cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Generating doxygen.stamp"
	cd /home/bdv/dev/h5cpp/cmake-build-debug/doc && doxygen
	cd /home/bdv/dev/h5cpp/cmake-build-debug/doc && echo timestamp > doxygen.stamp

api_doc: doc/CMakeFiles/api_doc
api_doc: doc/doxygen.stamp
api_doc: doc/CMakeFiles/api_doc.dir/build.make

.PHONY : api_doc

# Rule to build all files generated by this target.
doc/CMakeFiles/api_doc.dir/build: api_doc

.PHONY : doc/CMakeFiles/api_doc.dir/build

doc/CMakeFiles/api_doc.dir/clean:
	cd /home/bdv/dev/h5cpp/cmake-build-debug/doc && $(CMAKE_COMMAND) -P CMakeFiles/api_doc.dir/cmake_clean.cmake
.PHONY : doc/CMakeFiles/api_doc.dir/clean

doc/CMakeFiles/api_doc.dir/depend:
	cd /home/bdv/dev/h5cpp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bdv/dev/h5cpp /home/bdv/dev/h5cpp/doc /home/bdv/dev/h5cpp/cmake-build-debug /home/bdv/dev/h5cpp/cmake-build-debug/doc /home/bdv/dev/h5cpp/cmake-build-debug/doc/CMakeFiles/api_doc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : doc/CMakeFiles/api_doc.dir/depend

