===============
Design overview
===============

In this chapter we will have a brief view on the design of *h5cpp*. We will 
not dive into the details here but hopfully provide enough insight into the 
concepts behind *h5cpp*. 

.. attention::

    If you are new to *h5cpp* please read this chapter carefully as it is the 
    basement for everthing else in this manual. If you do not understand the 
    terminology introduced by this chapter it is most probably difficult 
    to understand the rest of the manual. 
    
       
A high level view on HDF5
=========================

An HDF5 tree can be considered a tree of objects connected by links. 

.. figure:: ../images/hdf5_basic_tree.svg
   :align: center
   :width: 75%
   
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
   :width: 75%

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

   
Nodes and links
===============
