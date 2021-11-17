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
:cpp:class:`hdf5::node::LinkView` and :cpp:class:`hdf5::node::NodeView`
respectively.


Iterating over nodes
====================

There are basically two ways how to iterate over the children of a group

* simpel iteration over the *immediate* children of a group
* or recursive iteration

The former one works like expected from an STL container either with the
for-each construction

.. code-block:: cpp

   hdf5::node::Group group = ...;

   for(auto node: group.nodes)
   {
    ...
   }

or with the standard iterator interface using :cpp:func:`begin` and :cpp:func:`end`
member functions to obtain the iterators. In the following example we
collect all the datasets immediately attached to a particular group

.. code-block:: cpp

   hdf5::node::Group group = ...;
   std::vector<hdf5::node::Dataset> datasets;

   std::copy_if(group.nodes.begin(),group.nodes.end(),
                std::back_inserter(datasets),
                [](const hdf5::node::Node &node)
                {
                  return node.type()==hdf5::node::Type::Dataset;
                });

For recursive iteration we currently cannot use the for-each construction
but we can definitely use the iterator interface. To extend the above
example we look for all datasets below a particular group and its subgroups

.. code-block:: cpp

   hdf5::node::Group group = ...;
   std::vector<hdf5::node::Dataset> datasets;

   std::copy_if(hdf5::node::RecursiveNodeIterator::begin(group),
                hdf5::node::RecursiveNodeIterator::end(group),
                std::back_inserter(datasets),
                [](const hdf5::node::Node &node)
                {
                  return node.type()==hdf5::node::Type::Dataset;
                });

the major difference here is to use :cpp:class:`RecursiveNodeIterator` and
its static factory functions :cpp:func:`begin` and :cpp:func:`end`.

Iterating over links
====================

Iteration over links works pretty much the same as iteration over nodes.
In order to iterate over the links *immediately* attached to a group we could
use the following code snippet

.. code-block:: cpp

   hdf5::node::Group group = ...;

   std::for_each(group.links.begin(),group.links.end(),
                [](const hdf5::node::Link &link)
                {
                  std::cout<<link.path()<<std::endl;
                });

to print the paths of all these links. For *immediate* links we also could
have used the for-each construction

.. code-block:: cpp

   hdf5::node::Group group = ...;

   for(auto link: group.links)
   {
      std::cout<<link.path()<<std::endl;
   }

to achive the same goal. For recurive iteration we have to use the
:cpp:class:`hdf5::node::RecursiveLinkIterator` pretty much the same way as
we did for nodes in the previous section

.. code-block:: cpp

   hdf5::node::Group group = ...;

   std::for_each(hdf5::node::RecursiveLinkIterator::begin(group),
                 hdf5::node::RecursiveLinkIterator::end(group),
                 p](const hdf5::node::Link &link)
                 { std::cout<<link.path()<<std::endl; });

Accessing a groups children and links
=====================================

The immediate links and nodes of a group can be accessed either

* by their name
* or by their index

Access by name
--------------

Links and nodes can be accessed by their name. We can use the :cpp:func:`exists`
method provided by the two view classes to determine whether a link with a
particular name exists.

.. code-block:: cpp

   hdf5::node::Group group = ...;

   if(group.link.exists("data"))
   {
      std::cout<<group.link["data"].path()<<std::endl;
   }

The same procedure applies to nodes too.


Access by index
---------------

Both, the :cpp:class:`LinkView` and :cpp:class:`NodeView` class provide a
:cpp:func:`size` method which returns the number of links or nodes immediately
attached to a group. We could use this to access links or nodes by their
index

.. code-block:: cpp

   hdf5::node::Group group = ...;

   for(size_t index = 0; index<group.nodes.size();++index)
   {
      std::cout<<group.nodes[index].link().path()<<std::endl;
   }


.. todo::

   Need to write some comment about order controll for iteration and index
   access. This should go to the *advanced* topics section of the users guide.



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

 Both iterator types satisfy the `C++ ForwardIterator concept`. Thus they are
 both read only iterators (one cannot change an object stored in the file
 via the iterator interface). Of course it is possible to read and write
 data to an object referenced by an iterator.

.. code-block:: cpp

    std::vector<h5::dataset_t> datasets;
    h5::group_t g = ....;

    std::copy_if(g.begin(),g.end(),std::back_inserter(datasets),
                 [](const auto &o) { return h5::is_dataset(o); });

.. _C++ FowardIterator concept: http://en.cppreference.com/w/cpp/concept/ForwardIterator
