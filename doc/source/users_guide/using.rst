=================
Using the library
=================


Installation
============

To install the following tools are required 

* cmake
* a reasonable new GCC or VisualStudio installation (support for C++11)
* sphinx to build the documentation
* doxygen for the API documentation

in addition you need the following libraries 

* boost (only the filesystem library is needed)
* HDF5 (only the C library with its header files)

A short installation how to install the library from sources. As there are not releases right now
we have to work with the git repository. To ceck out the sources use 

.. code-block:: bash

   $ git clone https://github.com/ess-dmsc/h5cpp.git
   
create a build directory and run cmake 

.. code-block:: bash 

   $ mkdir h5cpp-build
   $ cd h5cpp-build
   $ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=<wherever> ../h5cpp
   
a subsequent :command:`make` and :command:`make install` should install the software.
In case you have Boost and HDF5 in non standard locations you may also have to define 
:envvar:`HDF5_ROOT` and :envvar:`Boost_ROOT` variables when running cmake.

After the installation the library creates the following directory structure

.. code-block:: text

   PREFIX/include 
   PREFIX/lib
   PREFIX/lib/cmake/h5cpp-0.0.1
   
In particular the last directory is of importance as it contains the cmake package files 
for the C++ wrapper. 


Linking with `h5cpp`
====================

Consider a simple project with the following directory structure 

.. code-block:: text

   h5cpp_test/
      main.cpp
      CMakeLists.txt

To build a simple C++ program like this :file:`main.cpp` 

.. code-block:: cpp

   #include <iostream>
   #include <h5cpp/datatype/type_trait.hpp>
   
   int main()
   {
   	 auto type = hdf5::datatype::TypeTrait<int>::create();
   	 std::cout<<type.get_class()<<std::endl;
   	 
   	 return 0;
   }

the following :file:`CMakeLists.txt` fiel is sufficient 

.. code-block:: cmake

   cmake_minimum_required(VERSION 3.5.0)
   project(h5cpp_test 
           LANGUAGES C CXX
           VERSION 0.0.1)
   set(CMAKE_CXX_STANDARD 11)
   
   find_package(h5cpp REQUIRED)
   add_executable(h5cpp_test main.cpp)
   target_link_libraries(h5cpp_test h5cpp_shared)
   
is totally sufficient. Despite the C++ standard all dependencies are provided by 
the package file and the imported target. 
You can build the code with 

.. code-block:: bash

   h5cpp_test:$ mkdir build
   h5cpp_test:$ cd build
   h5cpp_test:$ cmake -Dh5cpp_DIR=<INSTALLPREFIX>/lib/cmake/h5cpp-0.0.1 ../
   h5cpp_test:$ make

The cmake variable :envvar:`h5cpp_DIR` tells :program:`cmake` where to look 
for the package files for *h5cpp*.