# h5cpp
C++ wrapper for the HDF5 C-library

## Compiling
This project uses CMake for setting up a build system, usually GNU Make. This is done as follows:

 * ``cd`` to the ``h5cpp`` directory.
 * Create a build directory and ``cd`` into that: ``mkdir build; cd build``.
 * Run CMake: ``cmake ..``. Note that the default build build type is *Release*. To build in debug mode, run CMake as follows: ``cmake -DCMAKE_BUILD_TYPE=Debug ..``.
 * To compile run: ``make``.

### Pull down dependencies with Conan
If you want to avoid the hassle of making sure that all the dependencies are correct, you can use conan to download and build them automatically for you. Conan is written in Python  so this assumes that a relatively recent version of *Python* (and *pip*) is installed. First install Conan if you do not already have it:
```bash
pip install conan
```

The boost dependency is not in the standard conan package receipt repository. Instead, you have add a package repository that has it.

```bash
conan remote add dmsc_packages https://api.bintray.com/conan/ess-dmsc/conan
```

Now create a CMake build directory (this assumes that you are in the root of the h5cpp repository):

```bash
mkdir build
cd build
```

Tell conan to download, build and install the required packages in the current build directory:

```bash
conan install ../ --build=missing
```

Finally, follow the regular cmake build instructions, i.e.:

```bash
cmake ..
make
```

### Code coverage
To activate the generation of code coverage information run CMake with the ``-DCOV`` argument, e.g.:
```
cmake -DCOV=TRUE ..
```

**WARNING:** Only activate code when compiling the library for running unit tests. Never install or otherwise use the library when code coverage has been activated.

### Requirements
The H5CPP library requires the [*HDF5 C-library*](https://www.hdfgroup.org) in order to build. The [*Boost*](http://www.boost.org) library is also required as it is used to implement filesystem access and to do unit testing.

In order to generate the documentation, [*Sphinx*](http://www.sphinx-doc.org/) with the [Read the Docs Sphinx Theme](https://github.com/rtfd/sphinx_rtd_theme) are required.