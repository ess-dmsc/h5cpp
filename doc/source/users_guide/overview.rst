.. _design-overview:

===============
Design overview
===============

.. sectionauthor:: Eugen Wintersberger <eugen.wintersberger@desy.de>

This chapter provides a brief overview over the design of *h5cpp* and the 
underlying assumptins and concepts. It is not a full design documentation 
but will introduce all terms required to read the users guide as well as
to read the API documentation. 
    
       
A high level view on HDF5
=========================

Nodes and Links
---------------

An HDF5 tree can be considered a tree of objects connected by links. 

.. figure:: ../images/hdf5_basic_tree.svg
   :align: center
   :width: 60%
   
From a very high level point of view we can assume that there are two kind 
of objects 

1. container objects which can store links to other object 
2. leafe like objects which cannot hold links to other objects

There is only one container type, a *Group*. For the leaf type of objects there
are only two: *Datasets* and *commited Datatypes*. We can collect all theses
objects under one master term: a *node*. From that point of view an HDF5 file 
is a tree of nodes connected by links. 

In addition each node can be augumented with attributes which can store 
additional metadata about an objects

.. figure:: ../images/hdf5_attributes.svg
   :align: center
   :width: 50%

Attributes can be accessed via their name. Lets have a closer look on the 
links. 

.. figure:: ../images/hdf5_links.svg
   :align: center
   :width: 75%
   
There are actually three kinds of links connecting objects within a file 

* *hard links* which are created when a new object is created in a file
* *soft links* which can be used liks symbolic links on a file system to 
  provide alternative means of access to an object
* *external links* providing a means to reference objects from a different 
  file.
  
This concept introduces some kind of ambiguity as can be seen from the 
figure above. There are basically three tracks which lead to the same 
*Dataset* instance. This is a known problem in the HDF5 library and *h5cpp* 
has taken a rather pragmatic approach how to solve it as will be shown later. 

Furthermore it is important to note that *Nodes* in an HDF5 file do not have 
names. This is an unfortunate widespread misconception about HDF5. *Nodes* 
can be accessed via a list of links which have names but the *Nodes* 
themeselfes have no idea about a name. Which would not even make sense if 
we take the ambiguity shown above into account. Which of the three link chains
leading to the *Dataset* instance would be the correct name of the *Dataset*?
  


   
Paths
-----

An important concept throughout *h5cpp* is a *Path*. A *Path* is used to 
reference a particular *Node* within an HDF5 file. Essentially it is the 
list of *Link* names used to access an object. 
As we have already seen the path to a *Node* is by no means unique. It is 
possible to access the same *Node* via different paths. 

The string representation of a path looks quite like a Unix filesystem path. 
It is the list of names separated by `/`. In the above example two possible 
paths to the *Dataset* would be 

.. code-block:: text

    /sensors/temp
    /plot/y 
    
Node IDs
--------

In the figure above we have seen that there are many paths that could lead to 
the same object. Now, if we do a recursive traversal over all nodes in a file 
we would face the problem that we get a copy of the same node several times. 
One for each path which leads to this object. 
We thus introduced the concept of a unique ID which is associated with every 
node. This ID identifies an object uniquely even over file boundaries and 
remains constant once a node has been created within a particular file.

.. attention::

    If you are familiar with HDF5s C-API do not confuse the unique ID 
    introduced by *h5cpp* with the :cpp:type:`hid_t` used in the C-API 
    to reference an instance of an object. The latter one is rather a handler 
    than an unqiue ID. IDs in *h5cpp* identify nodes uniquely even over 
    file boundaries at least within the context of a program. 
    While the value of :cpp:type:`hid_t` can change after closing and 
    re-opening the same object *h5cpp*s unique ID remains always the same. 
    
.. important::

    What you should take from this section are 
    
    * an HDF5 file constists of *Nodes* which are  
        - *Groups*
        - *Datasets*
        - *commited Datatypes*
        
    * which are connected via *Links* from which there are three kinds
        - *hard links*
        - *soft links*
        - and *external links*
        
    * nodes can be augumented with *Attributes* which can be used to 
      store additional metadata about a *Node*.
    * *Nodes* do not have names, *Links* have.
    * *Paths* are lists of link names referencing a node within a file
    * every *Node* is associated with a unique ID which remains unique 
      even over file boundaries

*h5cpp* a C++ wrapper for *HDF5*
================================

Including a single header file is enough to use *h5cpp* in your code 

.. code-block:: cpp

    #include <h5cpp/hdf5.hpp>
    
This will pull in everything you need. The entire library is organized in 
several namespaces with a top level namespace :cpp:any:`hdf5`

.. figure:: ../images/hdf5_package_overview.svg
   :align: center
   :width: 85%
   
The most important classes in the top-level namspace might be  
:cpp:class:`hdf5::Dimensions` and :cpp:class:`hdf5::Path`. 
The former one is merely a type alias 

.. code-block:: cpp

    using Dimensions = std::vector<hsize_t>;
    
in order to get rid of the rather nasty 

.. code-block:: cpp

    hsize_t *dims; 
    
which is heavily used throughout the C-API and thus a rather potential source 
for memory leaks. Using :cpp:class:`std::vector` for this thus solves a lot 
of problems and makes life just easy. 

:cpp:class:`Path` as the name already suggests represents an HDF5 path to 
reference a node within a file. We will discuss this class in more detail later.

+----------------------------+------------------------------------------------+ 
| namespace                  | description                                    |
+============================+================================================+
| :cpp:any:`hdf5::property`  | namespace with property list implementations.  |
+----------------------------+------------------------------------------------+
| :cpp:any:`hdf5::attribute` | contains all classes related to attributes and |
|                            | attribute management.                          |
+----------------------------+------------------------------------------------+
| :cpp:any:`hdf5::datatype`  | datatypes and related utility functions. The   |
|                            | classes in this namespace should not be        |
|                            | confused with *commited datatypes* which are   |
|                            | indeed nodes.                                  |
+----------------------------+------------------------------------------------+
| :cpp:any:`hdf5::node`      | the most imporant namespace providing all      |
|                            | functionality to deal with nodes.              |
+----------------------------+------------------------------------------------+
| :cpp:any:`hdf5::dataspace` | dataspaces and related utilities               |
+----------------------------+------------------------------------------------+
| :cpp:any:`hdf5::error`     | error management and exceptions                |
+----------------------------+------------------------------------------------+
| :cpp:any:`hdf5::file`      | everything releated to files                   |
+----------------------------+------------------------------------------------+

Nodes
-----

All classes representing nodes are located in the :cpp:any:`hdf5::node`
namespace. The most prominent ones are 

.. figure:: ../images/hdf5_node_types.svg
   :align: center
   :width: 75%
   
As you can see all node classes have a common parent class 
:cpp:class:`hdf5::node::Node`. 


