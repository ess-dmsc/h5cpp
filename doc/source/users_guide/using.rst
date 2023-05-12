=================
Using the library
=================

Using *h5cpp* with :program:`cmake`
===================================

*h5cpp* not only uses *CMake* as a build system but also provides 
a *CMake* package which makes using the library with *CMake* quite simple. 
The *CMake* package is installed below :file:`PREFIX/lib/cmake/h5cpp-0.5.1`
where :envvar:`PREFIX` expands to the installation prefix used in the 
inital cmake call of the installation procedure.   

Consider a simple project with the following directory structure 

.. code-block:: text

   h5cpp_test/
      main.cpp
      CMakeLists.txt

To build a simple C++ program like this :file:`main.cpp` 

.. code-block:: cpp

   #include <iostream>
   #include <h5cpp/hdf5.hpp>
   
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
           VERSION 0.5.1)
   set(CMAKE_CXX_STANDARD 11)
   
   find_package(h5cpp REQUIRED)
   add_executable(h5cpp_test main.cpp)
   target_link_libraries(h5cpp_test h5cpp::h5cpp)
   
Despite the C++ language standard all dependencies are provided by 
the package file via the imported target. 
You can build the code with 

.. code-block:: bash

   h5cpp_test:$ mkdir build
   h5cpp_test:$ cd build
   h5cpp_test:$ cmake -Dh5cpp_DIR=<INSTALLPREFIX>/lib/cmake/h5cpp-0.5.1 ../
   h5cpp_test:$ make

The cmake variable :envvar:`h5cpp_DIR` tells :program:`cmake` where to look 
for the package files for *h5cpp*.
