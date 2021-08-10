# C++ wrapper for the HDF5 C-library

[![docs](https://img.shields.io/badge/Documentation-webpages-ADD8E6.svg)](https://ess-dmsc.github.io/h5cpp/index.html) [![DOI](https://zenodo.org/badge/99373936.svg)](https://zenodo.org/badge/latestdoi/99373936) [![Join the chat at https://gitter.im/h5cpp/community](https://badges.gitter.im/h5cpp/community.svg)](https://gitter.im/h5cpp/community?utm_source=badge&utm_medium=badge&utm_campaign=pr-badge&utm_content=badge)


*h5cpp* is a new C++ wrapper for HDF5s C-API. 

## Motivation

HDF5 is a powerful binary file format. There is virtually nothing that cannot 
be stored within an HDF5 file. To read and write data from and to an HDF5 file
you can either use the C-API or one of the wrappers for a scripting language 
(for Python there is for instance [h5py](http://www.h5py.org/) or 
[pytables](http://www.pytables.org/)). However, to keep their interfaces 
simple, many of these wrappers do not provide the full functionality HDF5 
has to offer. If you want to use all features available the C-API is most 
probably the safest way to go. 

*h5cpp* wants to provide both, an easy to use modern C++ interface but at the 
same time give you access to the full functionality HDF5 has to offer. 

Although this and [Steve Vagras' h5cpp project](https://github.com/steven-varga/h5cpp)
share the same name they are entirely unreleated.


### Complete and domain agnostic 

Many HDF5 wrappers which are currently around have to major issues:

1. they do not provide the full functionality of the C-API
2. they are specifically made for a particular field of application

Our goal is to keep *h5cpp* as much as application agnostic as possible and 
provide the full functionality of the C-API. 

### Easy to use 

HDF5 is a rather powerful file format and thus the C-API is rather complex. 
*h5cpp*s approach to this degree of complexity can be best described by a quote 
of [Alan Kay](http://startupquote.com/post/5626579141)

    Simple things should be simple, complex things should be possible.
    
That's what we try to achieve and hopefully we succeeded in it. 

### Support for major platforms 

We currently support the following operating systems 

* Linux
* Windows 
* OSX

Since we are using `cmake` to build *h5cpp* and also provide a `cmake` package 
for the library, using it should be the same on each of these platforms.  

## How to build *h5cpp*

The minimum requirements for building the library are:

* a C++ compiler, gcc>=4.8.1 should do well
* the HDF5 C library (>=1.8.13 would do but >=1.10.0 is prefered)
* cmake >= 3.0
* _either_ the boost libraries _or_ a compiler with std::filesystem or std::experimental::filesystem (and specify H5CPP_WITH_BOOST=OFF to CMake)

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

## How to use *h5cpp*

With the library installed as above, you can bring it into your program by adding something
like this to your `CMakeLists.txt` file: 
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

## Alternate install directory

If you do not wish to install *h5cpp* to your system folders you can slightly modify the
above steps. When building the library, invoke CMake with the following option:

```bash
cmake -DCMAKE_INSTALL_PREFIX=/home/user1/some/path ..
```
and accordingly, when building the client program:
```bash
cmake -Dh5cpp_DIR=/home/user1/some/path/lib/cmake/h5cpp-0.4.1 path/to/your/source
```
where version number may vary.

For OSX and Windows instructions, as well as instructions for building tests and documentation,
see the [online documentation](https://ess-dmsc.github.io/h5cpp/index.html).



