======================
Installing the library
======================

This chapter describes the installation of *h5cpp* from sources. We discuss 
here the installation on a Linux (OSX should be quite similar). Installation 
on Windows is beyond this scope of this chapter and will be described in the 
advanced topics section of this manual. 

Requirements
------------

In order to build the code you need 

* a C++ compiler with reasonable C++11 support 
  (gcc>=4.9,Micrsoft Developer Studio >= 2015)
* the `Boost`_ libraries
* the `HDF5`_ C library
* `googletest`_ to build the unit tests
* `sphinx`_ (with python) and  `doxygen`_ for the documentation build
* `cmake`_ >= 3.0

.. _cmake: https://cmake.org/
.. _sphinx: http://www.sphinx-doc.org/en/stable/
.. _HDF5: https://support.hdfgroup.org/HDF5/
.. _Boost: http://www.boost.org/
.. _doxygen: http://www.stack.nl/~dimitri/doxygen/index.html
.. _googletest: https://github.com/google/googletest

Getting the code
----------------

You can either obtain one of the release tar balls from the `release site`_ of 
the project on GitHub or clone the master branch of the repository. 
In the first case you get a source tree with 

.. code-block:: bash

	$ tar -xzf h5cpp-*.tar.gz
	
while in the latter case you may want to use 

.. code-block:: bash

	$ git clone https://github.com/ess-dmsc/h5cpp.git
	
In either case you end up with a directory :file:`h5cpp` in your current 
directory. 

.. _release site: https://github.com/ess-dmsc/h5cpp/releases


Building and testing
--------------------

*h5cpp* users :program:`cmake` for building, thus, after unpacking or cloning 
the sources you should create a build directory

.. code-block:: bash

    $ make h5cpp-build
    $ cd h5cpp-build
    
and call cmake from there. In the simplest case just call 

.. code-block:: bash

    $ cmake -DCMAKE_BUILD_TYPE=Release ../h5cpp 
    
which should do the job provided that all dependencies are installed in 
standard locations. We strongly recommend to set the particular build 
configuration with the :envvar:`CMAKE_BUILD_TYPE` variable.   

On a Linux system the default build system used is 
:program:`make`. Thus, in the build directory, just run make 

.. code-block:: bash

    $ make 
    
and to build and run the unittests

.. code-block:: bash

    $ make run_tests
    
Installation
------------
    
A subsequent 

.. code-block:: bash

    $ make install
    
should finally install the code. The default installation prefix is 
:file:`/usr/local`. If you want to change this set the 
:envvar:`CMAKE_INSTALL_PREFIX` at the initial call to :program:`cmake` to the 
desired installation location. 

