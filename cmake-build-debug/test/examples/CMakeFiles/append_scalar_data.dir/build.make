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

# Include any dependencies generated for this target.
include test/examples/CMakeFiles/append_scalar_data.dir/depend.make

# Include the progress variables for this target.
include test/examples/CMakeFiles/append_scalar_data.dir/progress.make

# Include the compile flags for this target's objects.
include test/examples/CMakeFiles/append_scalar_data.dir/flags.make

test/examples/CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.o: test/examples/CMakeFiles/append_scalar_data.dir/flags.make
test/examples/CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.o: ../test/examples/append_scalar_data.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/bdv/dev/h5cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/examples/CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.o"
	cd /home/bdv/dev/h5cpp/cmake-build-debug/test/examples && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.o -c /home/bdv/dev/h5cpp/test/examples/append_scalar_data.cpp

test/examples/CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.i"
	cd /home/bdv/dev/h5cpp/cmake-build-debug/test/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/bdv/dev/h5cpp/test/examples/append_scalar_data.cpp > CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.i

test/examples/CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.s"
	cd /home/bdv/dev/h5cpp/cmake-build-debug/test/examples && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/bdv/dev/h5cpp/test/examples/append_scalar_data.cpp -o CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.s

test/examples/CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.o.requires:

.PHONY : test/examples/CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.o.requires

test/examples/CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.o.provides: test/examples/CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.o.requires
	$(MAKE) -f test/examples/CMakeFiles/append_scalar_data.dir/build.make test/examples/CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.o.provides.build
.PHONY : test/examples/CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.o.provides

test/examples/CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.o.provides.build: test/examples/CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.o


# Object files for target append_scalar_data
append_scalar_data_OBJECTS = \
"CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.o"

# External object files for target append_scalar_data
append_scalar_data_EXTERNAL_OBJECTS =

bin/append_scalar_data: test/examples/CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.o
bin/append_scalar_data: test/examples/CMakeFiles/append_scalar_data.dir/build.make
bin/append_scalar_data: lib/libh5cpp_shared.so.0.0.1
bin/append_scalar_data: /usr/local/hdf5/lib/libhdf5.so
bin/append_scalar_data: /usr/lib/x86_64-linux-gnu/libz.so
bin/append_scalar_data: /usr/lib/x86_64-linux-gnu/libdl.so
bin/append_scalar_data: /usr/lib/x86_64-linux-gnu/libm.so
bin/append_scalar_data: /usr/lib/x86_64-linux-gnu/libboost_system.so
bin/append_scalar_data: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so
bin/append_scalar_data: test/examples/CMakeFiles/append_scalar_data.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/bdv/dev/h5cpp/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/append_scalar_data"
	cd /home/bdv/dev/h5cpp/cmake-build-debug/test/examples && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/append_scalar_data.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/examples/CMakeFiles/append_scalar_data.dir/build: bin/append_scalar_data

.PHONY : test/examples/CMakeFiles/append_scalar_data.dir/build

test/examples/CMakeFiles/append_scalar_data.dir/requires: test/examples/CMakeFiles/append_scalar_data.dir/append_scalar_data.cpp.o.requires

.PHONY : test/examples/CMakeFiles/append_scalar_data.dir/requires

test/examples/CMakeFiles/append_scalar_data.dir/clean:
	cd /home/bdv/dev/h5cpp/cmake-build-debug/test/examples && $(CMAKE_COMMAND) -P CMakeFiles/append_scalar_data.dir/cmake_clean.cmake
.PHONY : test/examples/CMakeFiles/append_scalar_data.dir/clean

test/examples/CMakeFiles/append_scalar_data.dir/depend:
	cd /home/bdv/dev/h5cpp/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/bdv/dev/h5cpp /home/bdv/dev/h5cpp/test/examples /home/bdv/dev/h5cpp/cmake-build-debug /home/bdv/dev/h5cpp/cmake-build-debug/test/examples /home/bdv/dev/h5cpp/cmake-build-debug/test/examples/CMakeFiles/append_scalar_data.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/examples/CMakeFiles/append_scalar_data.dir/depend

