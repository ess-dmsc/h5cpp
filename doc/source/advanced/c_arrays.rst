==============
C-style arrays
==============

In many applications we have to deal with legacy software where data is 
still stored in C-style arrays which basically come in two flavors

1. either as static arrays `double velocity[3]` or 
2. as dynamically allocated data referenced by a pointer `double *data`.

The basic mechanisms behind this wrapper using type traits to construct
the dataspace do not work in connection with these C-style constructions due 
to the fact that they do not carray any size information once constructed. 
To handle such situations *h5cpp* provides an adapter template which 
can be used to overcome this problem. The adapter is declared in the 
:file:`h5cpp/utilities/array_adapter.hpp` header file. 
In order to use it add the following code to your source file

.. code-block:: cpp

   #include <h5cpp/hdf5.hpp>
   #include <h5cpp/utilities/array_adapter.hpp>

The adapter works for datasets as well as for attributes. 
In order to write data an instance of the adapter can be created on the fly 

.. code-block:: cpp

   using DoubleArrayAdapter = ArrayAdapter<double>;
   Dataset dataset(...);
   double *data;
   data = new double[1024];
   
   dataset.write(DoubleArrayAdapter(data,1024));
   
   
Reading data to a C-style array

.. code-block:: cpp

   double *data;
   data = new double[1024];
   
   DoubleArrayAdapter adapter(data,1024);
   dataset.read(adapter);   
   
   
.. attention::

   The :cpp:class:`ArrayAdapter` class does not perform any resource management
   tasks. So the memory referenced by the pointer passed to it has to be 
   managed by the calling program. 
   
.. note::

   Using he adapter might feels a little bit uncomfortable in comparison with 
   using STL containers. The adapter was designed with the intention to support
   legacy code where plain old C structures like pointers are still used. 
   We do not want to encourage users to use such style or programming as these
   data structures are a constant source of resource leakage problems. 