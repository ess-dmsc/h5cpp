# A modern C++ interface for HDF5

[![Build Status](https://jenkins.esss.dk/dm/job/ess-dmsc/job/h5cpp/job/master/badge/icon)](https://jenkins.esss.dk/dm/job/ess-dmsc/job/h5cpp/job/master/)
![github workflow](https://github.com/ess-dmsc/h5cpp/actions/workflows/cmake-build.yml/badge.svg)
[![docs](https://img.shields.io/badge/Documentation-webpages-ADD8E6.svg)](https://ess-dmsc.github.io/h5cpp/index.html)
[![Conan package](https://img.shields.io/badge/conan-package-blue)](https://github.com/ess-dmsc/conan-h5cpp)
[![DOI](https://zenodo.org/badge/99373936.svg)](https://zenodo.org/badge/latestdoi/99373936)
[![Join the chat at https://gitter.im/h5cpp/community](https://badges.gitter.im/h5cpp/community.svg)](https://gitter.im/h5cpp/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)


*h5cpp* is a modern C++ wrapper for HDF5's C-API. 

## Motivation

[HDF5](https://en.wikipedia.org/wiki/Hierarchical_Data_Format) is a powerful binary format. There is virtually nothing that cannot be stored in an HDF5 file. You can either use the C-API or one of the wrappers for a scripting language (for Python there is for instance [h5py](http://www.h5py.org/) or [pytables](http://www.pytables.org/)). To keep their interfaces simple, many of these wrappers do not provide the full functionality HDF5 has to offer. If you want to use all features available, you must use the C-API, which is, however, quite unwieldy and not conducive to modern C++ idioms. 

**h5cpp** provides a domain-agnostic and easy-to-use modern C++ interface to the full functionality of HDF5. 

We currently support:
* Linux
* Windows
* macOS

Although this and [Steven Varga's h5cpp project](https://github.com/steven-varga/h5cpp)
share the same name they are entirely unrelated.

## How to use *h5cpp*

You may bring in *h5cpp* as a [conan package](https://github.com/ess-dmsc/conan-h5cpp) or build and install the library manually [as described below](#how-to-build-h5cpp). 

In either case, you can bring it into your program by adding something like this in your `CMakeLists.txt` file:
```cmake
find_package(h5cpp REQUIRED)
.
.
.
add_executable(some_target some_code.cpp)
target_link_libraries(some_target h5cpp)
```
and adding the following:
```cpp
#include <h5cpp/hdf5.hpp>
```
to your your source file.
Here is a small example of how to make use of the library in code:

```cpp

using namespace hdf5;

// create a file
file::File f = file::create("writing_vector.h5",file::AccessFlags::Truncate);

// create a group
node::Group root_group = f.root();
node::Group my_group = root_group.create_group("my_group");

// create a dataset
using data_type = std::vector<int>;
data_type data{1,2,3,4};
node::Dataset dataset = my_group.create_dataset("data",
                                                datatype::create<data_type>(),
                                                dataspace::create(data));

// write to dataset
dataset.write(data);
```

For more, please see the full [API documentation](https://ess-dmsc.github.io/h5cpp/index.html).

## How to build *h5cpp*

The minimum requirements for building the library are:

* a C++ compiler, gcc>=4.9 should do well
* the HDF5 C library (>=1.8.13 would do but >=1.10.0 is prefered)
* cmake >= 3.10
* _either_ the boost libraries _or_ a compiler with std::filesystem or std::experimental::filesystem (and specify H5CPP_WITH_BOOST=OFF to CMake)
* [sphinx](http://www.sphinx-doc.org/en/stable/), [breathe](https://github.com/michaeljones/breathe) (with python) and  [doxygen](https://www.doxygen.nl/index.html) for the documentation build
* [catch2](https://github.com/catchorg/catch2) to build the unit tests

The external library dependencies can be acquired and built using [Conan](https://conan.io/). Conan can be installed with PyPI: 
```
pip install conan
```
Then run the following to configure required Conan repositories:
```
conan remote add ecdc https://artifactoryconan.esss.dk/artifactory/api/conan/ecdc
conan remote add bincrafters https://bincrafters.jfrog.io/artifactory/api/conan/public-conan
```
and that's it, CMake will handle the rest!

Alternatively you can manually install the dependencies to typical system locations. In this case please disable Conan by using the `-DH5CPP_CONAN=DISABLE` option when you run CMake. 

Building the library is standard cmake & make fare, out of source. For example,
in linux shell, you would do the following:

```bash
git clone https://github.com/ess-dmsc/h5cpp.git
cd h5cpp
mkdir build
cd build
cmake ..
make
```

In any case you should run the tests after the build.

```bash
$ make test
```

To install the library to system, you would follow this up with:
```bash
sudo make install
```

### Alternate install directory

If you do not wish to install *h5cpp* to your system folders you can slightly modify the
above steps. When building the library, invoke CMake with the following option:

```bash
cmake -DCMAKE_INSTALL_PREFIX=/home/user1/some/path ..
```
and accordingly, when building the client program:
```bash
cmake -Dh5cpp_DIR=/home/user1/some/path/lib/cmake/h5cpp-0.5.1 path/to/your/source
```
where version number may vary.

For OSX and Windows instructions, as well as instructions for building tests and documentation,
see the [online documentation](https://ess-dmsc.github.io/h5cpp/index.html).



