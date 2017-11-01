======================
Installing the library
======================

This chapter describes the installation of *h5cpp* from sources. 

Requirements
------------

In order to build the code you need 

* a C++ compiler with reasonable C++11 support (gcc>=4.9,Micrsoft Developer Studio >= 2015)
* the Boost libraries
* the HDF5 C library
* googletest to build the unit tests
* sphinx (with python) and doxygen for the documentation build
* cmake >= 3.0

Getting the code
----------------

You can either obtain one of the release tar balls from the `release site`_ of the 
project on GitHub or clone the master branch of the repository. 
In the first case you get a source tree with 

.. code-block:: bash

	$ tar -xzf h5cpp-*.tar.gz
	
while in the latter you may want to use 

.. code-block:: bash

	$ git clone https://github.com/ess-dmsc/h5cpp.git
	
*h5cpp* uses :program:`CMake` to build the code in which case an out of 
source build is recommended. 

_release site: https://github.com/ess-dmsc/h5cpp/releases



Building and testing 
--------------------

Installation
------------