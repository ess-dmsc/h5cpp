================
The name problem
================

The objects in an HDF5 file are organized as a directed graph. Where groups and 
datasets represent the nodes which are connected via links (the edges between
the nodes). Every object within the file can be accessed via its path which 
 which is referenced by the HDF5 reference manual in some occasions as the 
 *name* of an object. 
It is a common misconception made by HDF5 users that the name (path) of an
object is something which is associated with the object itself. Instead the 
name (path) describes only a particular route taken to obtain a specific object,
 which is not necessarily unique.

Consider the following situation

.. figure:: images/name_problem.png
   :align: center


In this example there are two possible names (paths) to end up at the 
dataset instance ``obj3``

* ``/group_1/data_1`` or 
* ``/group_2/data_2``.

The fact, that the path to an object is not necessarily unique causes several 
problems 

#. we cannot ask an object for its parent object (in the above example, if 
   we would ask the dataset whose its parent is, what would it answer?)
#. if we ask an object for its name which one to choose? As the reference 
   manual for :c:func:`H5Iget_name` states: the returned name can be one of 
   many possible. Which one is not determined 
#. if we iterate over the groups of an HDF5 file, looking for instance for all
   datasets within the file, it is quite possible that we retrieve several 
   references pointing to the same object in the file. As the object can 
   be accessed by several routes the path (name) of an object is not sufficient
   to check for object equality and thus identify multiple instances 
   in such a recursive iteration.
   
Unfortunately all of theses issues are consequences of the principle design 
(using a directed graph) and thus no simple solution exists.

Pragmatic solution
==================

A reasonable approach would be to follow the intuition of the user and find 
some pragmatic solutions for this problem. 

Obtaining an objects name and parent
------------------------------------

When we ask for the name of an object we would expect to retrieve the same 
path which was used to access the object in the first place. 
For the above example this would mean: if we had opened the dataset with
``/group_2/data_2`` a potential :cpp:func:`name()` method should return this
path instead of, for instance, ``/group_1/data_1``. Independent of the types of
the links (HARD, SOFT, EXTERNAL) involved.

The same is true for an objects parent. In the above example, when using 
``/group_2/data_2`` to access the dataset a potential :cpp:func:`parent()`
method should return an instance of ``group_2`` rather than of ``group_1``
independent of the involved link types.

One possible solution for this problem would be to add some additional 
information to an instance of :cpp:class:`linkable_object_t` instance:

* an instance to the path used to open the object
* a reference to the root group via which the object was opened.

.. figure:: images/name_problem_solution.png
   :align: center

The root group can safely be used as it always must exist even in a newly 
created file.

Avoiding multiple references to the same object
-----------------------------------------------

This problem is more difficult to solve. It can be reduced to the problem
of checking two objects for equality. If it is possible to check for 
equality we could sort out all our duplicates from the list of all 
objects within an HDF5 file. 
We could consider two objects as equal if they refer to the same object 
within the HDF5 file. For obvious reasons the path to an object is not a 
suitable measure to check for equality.

The key is here to find an identifier associated with each object which 
determines the object uniquely within the file. One possible candidate for 
this would be the :c:member:`H5O_info_t::addr` field stored in the 
:c:type:`H5O_info_t` struct.

.. warning:: 

    Can the address of an object change once it has been writen to disk? 