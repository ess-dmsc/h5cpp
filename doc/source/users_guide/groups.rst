===================
Working with groups
===================

Groups are the basic containers within an HDF5 file. The entry point to the 
HDF5 node hierarchy is the root group of a file. It can be accessed from the 
:cpp:func:`root` method of a :cpp:class:`hdf5::file::File` instance. 

.. code-block:: cpp

    using namespace hdf5;
    
    file::File f = ....;
    node::Group root_group = f.root();

Groups act like STL container in a very general sense. With an HDF5 group you 
can iterate either over the links directly attached to it or over the 
objects referenced by those links. You can access links via the publik 
:cpp:member:`hdf5::node::Group::links` member or the objects via the 
:cpp:member:`hdf5::node::Group::nodes` member. They are instances of 
:cpp:class:`hdf5::node::LinkView` and :cpp:class:`hdf5::node::LinkView` 
respectively. 


Iterating over nodes
====================

Iterating over links
====================

Accessing a groups children
===========================




Iterators
=========

Two iterator types are provided

* :cpp:class:`group_iterator_t` which iterates over the *direct* children 
  of a group. Instances can be created with the :cpp:func:`begin` and 
  :cpp:func:`end` methods of an instance of :cpp:class:`group_t`.
* :cpp:class:`recursive_group_iterator_t` which iterates recursively 
  over all children below the given group. Instances of this iterator are
  created by the :cpp:class:`rbegin` and :cpp:class:`rend` methods of 
  an instance of :cpp:class:`group_t`.
  
 Both iterator types satisfy the `C++ ForwardIterator concept`_. Thus they are 
 both read only iterators (one cannot change an object stored in the file 
 via the iterator interface). Of course it is possible to read and write 
 data to an object referenced by an iterator.

.. code-block:: cpp

    std::vector<h5::dataset_t> datasets; 
    h5::group_t g = ....;

    std::copy_if(g.begin(),g.end(),std::back_inserter(datasets),
                 [](const auto &o) { return h5::is_dataset(o); });
                 
.. _C++ FowardIterator concept: http://en.cppreference.com/w/cpp/concept/ForwardIterator 

