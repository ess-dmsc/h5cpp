=======================
User defined data types
=======================

At some point in time one may wants to write data from a user defined 
data type. Namely we want to write data from a C++ class (typically the fields 
stored as members of the class). 
In this case we have to distinguish two situations

* classes whose members are only POD types 
* classes with STL containers, strings, or any other dynamic non-POD type. 

The former case is simple the latter one rather complicated. In general, 
what we have to do is that for every type which should be used in an 
IO operation (a call to :cpp:func:`read` or :cpp:func:`write` of an 
attribute or dataset) two things must be available

* a dataspace trait
* and a datatype trait

Types with POD members only
===========================

As an example for this situation 



Typs with non-trivial members
=============================

.. todo:: 

   Need to handle this situation.
