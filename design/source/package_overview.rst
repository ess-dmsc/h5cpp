===============
The big picture
===============

The HDF5 tree
=============

HDF5 organizes data within a file as a directed graph consisting of *nodes* 
connected via *links*. We can roughly distinguish between to types of nodes: 
those who can contain other nodes and those who can not. We will refer to the 
former ones as *group* nodes and to the latter ones as *leaf nodes*. 

.. figure:: images/hdf5_tree.png
   :align: center
   :width: 700


Technically all node types are descendants of :cpp:class:`node_t` 

.. figure:: images/node_types.png
   :align: center
   :width: 500px
   
There are currently two types of leaf nodes: :cpp:class:`dataset_t` and 
:cpp:class:`named_datatype_t` and one group type :cpp:class:`group_t`. 
 
The links between the nodes are represented by instances of :cpp:class:`link_t`.  
We can distinguish between three types of links described by the enueration 
type :cpp:enum:`link::type_t`.

+----------------------------------------------+------------------------------+
| link type                                    | description                  |
+==============================================+==============================+
| :cpp:enumerator:`h5::link::type_t::HARD`     | typically the first link     |
|                                              | created when an object is    |
|                                              | created in the file. Every   |
|                                              | object must have a least one |
|                                              | hard link pointing to it.    |
+----------------------------------------------+------------------------------+
| :cpp:enumerator:`h5::link::type_t::SOFT`     | Comparable to a symbolic     |
|                                              | link on a file systems.      |
|                                              | Removing this link does not  |
|                                              | remove an object or makeing  |
|                                              | it inaccessible.             |
+----------------------------------------------+------------------------------+
| :cpp:enumerator:`h5::link::type_t::EXTERNAL` | References an object in a    |
|                                              | different file.              |
+----------------------------------------------+------------------------------+

Aside from *nodes* and *links* there are some more auxiliary types available 
which help to construct the tree and feed data into it. 

* :cpp:class:`id_t` - wraps an HDF5 :cpp:type:`hid_t` ID used to handle 
  objects within the library
* :cpp:class:`datatype_t` - represents an HDF5 data type. Used for IO and 
  attribute and dataset creation
* :cpp:class:`property_list_t` and its descendants are used to parametrized 
  all kinds of functions in the HDF5 C-API
* :cpp:class:`dataspace_t` - describes the rank and the number of elements 
  along each dimension of data in file or memory
* :cpp:class:`file_t` - provides access to file related functions.

There are some more types available which are not mentioned here but these 
are the most prominent ones.

 


The library namespaces
======================

.. figure:: images/package_overview.png
   :align: center
   :width: 75%
   
All objects reside in the toplevel namespace :cpp:any:`h5`. There are some
subnamespaces which contain special functions and classes usually not required
for normal operations. 

The following namespaces are available

+------------------------------+----------------------------------------+-+
| namespace                    | description                            | |
+==============================+========================================+=+
| :cpp:any:`h5`                | the top-level namespace of the library | |
+------------------------------+----------------------------------------+-+
| :cpp:any:`h5::id`            | classes and functions dealing with ID  | |
|                              | management                             | |
+------------------------------+----------------------------------------+-+
| :cpp:any:`h5::error`         | package providing error management     | |
|                              | related functions and classes.         | |
+------------------------------+----------------------------------------+-+
| :cpp:any:`h5::property_list` | property list classes and related      | |
|                              | functions                              | |
+------------------------------+----------------------------------------+-+
| :cpp:any:`h5::attribute`     | attribute related classes and          | |
|                              | functions                              | |
+------------------------------+----------------------------------------+-+
| :cpp:any:`h5::link`          | classes and functions related to links | |
+------------------------------+----------------------------------------+-+
| :cpp:any:`h5::dataspace`     | classes and functions related to       | |
|                              | HDF5 data spaces                       | |
+------------------------------+----------------------------------------+-+
| :cpp:any:`h5::utilities`     | namespace with general utilty types,   | |
|                              | and functions used throughout the      | |
|                              | the library                            | |
+------------------------------+----------------------------------------+-+
| :cpp:any:`h5::datatype`      | datatype related classes and functions | |
+------------------------------+----------------------------------------+-+
| :cpp:any:`h5::dataset`       | dataset related classes and functions  | |
+------------------------------+----------------------------------------+-+
| :cpp:any:`h5::file`          | file related classes and functions     | |
+------------------------------+----------------------------------------+-+
| :cpp:any:`h5::group`         | group related classes and functions    | |
+------------------------------+----------------------------------------+-+
| :cpp:any:`h5::node`          | classes and functions for general      | |
|                              | node management                        | |
+------------------------------+----------------------------------------+-+

The namespaces mimic in some way the organization of HDF5's C-API. 
For the sake of simplicity some of the types are made available to the 
top-level namespace :cpp:any:`h5` via aliases. 

.. code-block:: cpp

    namespace h5 {
        
        using path_t      = utilities::path_t;
        using datatype_t  = datatype::datatype_t;
        using dataspace_t = dataspace::dataspace_t;
        using hyperslab_t = dataspace::dataspace_t; 
        using dataset_t   = dataset::dataset_t;
        using file_t      = file::file_t;
        using attribute_t = attribute::attribute_t;
        using linkt_t     = link::link_t;
        using node_t      = node::node_t;
        using group_t     = group::group_t;
    
    } // end of namespace h5

