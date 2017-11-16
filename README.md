# C++ wrapper for the HDF5 C-library

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

## How to build and using *h5cpp*

Here is a little example of how to use the library on Linux. In order to build the code on Linux you need 

* a C++ compiler, gcc>=4.8 should do well
* the boost libraries
* the HDF5 C library (>=1.8.13 would do but >=1.10.0 is prefered)
* cmake >= 3.5
* doxygen and sphinx to build the documentation.

Lets start with a top level test directory and create a source directory in it
```bash
mkdir h5cpp_test
cd h5cpp_test
mkdir src
cd src
```
Now clone the *h5cpp* code from this repository in the source directory 

```bash
git clone https://github.com/ess-dmsc/h5cpp.git
```
and create a build directory in which you call cmake
```bash
mkdir h5cpp_build
cd h5cpp_build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PWD/../../ ../h5cpp
```
Once the configuration is done you simply run `make` and `make run_tests` to build the code
```bash
make -j4
make run_tests
```
Finally to install the code use 
```bash
make install
```
Our overall project directory should look now somehow like this 
```text
h5cpp_test/
   include/
   lib/
   src/
     h5cpp/
     h5cpp_build/
```
Now lets create a small project in the source directory with 
```bash
    src/
      h5test/
        CMakeLists.txt
        h5test.cpp
```
where the `CMakeLists.txt` looks like this 
```cmake
cmake_minimum_required(VERSION 3.5.0)
project(h5cpp_test 
        LANGUAGES C CXX
        VERSION 0.0.1)
set(CMAKE_CXX_STANDARD 11)


find_package(h5cpp REQUIRED)

add_executable(h5test h5test.cpp)
target_link_libraries(h5test h5cpp_shared)
```
and `h5test.cpp`
```cpp
#include <iostream>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

int main()
{
  file::File f = file::create("h5test.h5",file::AccessFlags::TRUNCATE);

  return 0;
}
```
Finally we can create a build directory for the test program and build the code
```bash
mkdir h5test_buid
cmake -DCMAKE_BUILD_TYPE=Release -Dh5cpp_DIR=$PWD/../../lib/cmake/h5cpp-0.0.1 ../h5test
make
./h5test
```
The imporant part here is the `h5cpp_DIR` variable which should point to the directory 
with the package files for *h5cpp*.

For OSX and Windows instructions see the [online documentation](https://ess-dmsc.github.io/h5cpp/index.html).

