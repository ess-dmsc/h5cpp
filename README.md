# h5cpp
C++ wrapper for the HDF5 C-library

## Compiling
This project uses CMake for setting up a build system, usually GNU Make. This is done as follows:

 * ``cd`` to the ``h5cpp`` directory.
 * Create a build directory and ``cd`` into that: ``mkdir build; cd build``.
 * Run CMake: ``cmake ..``. Note that the default build build type is *Release*. To build in debug mode, run CMake as follows: ``cmake -DCMAKE_BUILD_TYPE=Debug ..``.
 * To compile run: ``make``.

### Requirements
This library requires the *HDF5 C* library and the *Boost* library.