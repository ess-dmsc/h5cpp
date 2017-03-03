=============
Design issues
=============

This chapter deals with some of the issues the C++ wrapper tries to solve. 

In some places the HDF5 C-API shows some interesting and unexpected behavior.
One of the goals of this C++ wrapper is to fix this issues by providing 
an interface which behaves intuitively. However, this section will also show
some conceptual *problems* which cannot be solved at all but are rather 
a consequence of the overall design of the library and the underlying 
data structures.

.. toctree::
   :maxdepth: 1
   
   name_problem
   thread_safety
   
   