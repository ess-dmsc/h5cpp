=====================================
Adapters and the return value problem
=====================================

The return value problem
========================

A group in HDF5 can be considered as a container for other groups and 
datasets. This raises a simple question: what to return from a method of 
:cpp:class:`group_t` which provides access to the children of the group?

.. code-block:: cpp

    h5::group_t group = ....;
    
    ???? child = group["sensors"];

The return value could be either a dataset or a group. However, as the true 
nature of a child can only be determined at runtime it is virtually impossible 
to pin down the required data type at compile time.

We can, however, pin down some general statements about the returned object

* it is either a *group* or a *dataset*, it cannot be both 
* 

There are several options how to deal with this issue which shall be discussed 
in this chapter.

Inheritance
===========

Variants
========
 

Adapters
========
