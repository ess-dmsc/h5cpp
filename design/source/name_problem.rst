================
The name problem
================

The objects in an HDF5 file are organized as a directed graph. Where groups and 
datasets represent the nodes which are connected via links (the edges between 
the nodes).
It is a common misconception of users that every object is associated with a 
name. This is plain wrong. The name of an object is determined by the name 
of the link which points to it. Node objects themselves have no name tag 
attached to them. Consequently the name of an object in HDF5 is always 
the absolute path to this particular object. 

Unfortunately this path is not unique as alternative routes to an object can 
be created by means of symbolic links. In addition it is possible to 
created several hard links to a particular object. Hence, there is no 
unqiue path to a particular object in general. 
As the reference manual for :c:func:`H5Iget_name` states: the returned name 
can be one of many possible. Which one is not determined.  

Pragmatic solution
==================

Since this is a conceptual problem there is no simple solution to it. 
A reasonable approach would be to follow the intuition of the user. 
When accessing a particular object the user has to provide a path 
to this object. This is what he or she expects to be the name of the object. 
Since this path may includes symbolic links it is rather uncertain that 
:c:func:`H5Iget_name` will return the correct path (the one the user has 
provided). Thus, in order to solve this problem an instance of 
every object must include the path information used to open the object. 