==================
The parent problem
==================

A common requirement to an interface for a HDF5 group or dataset would be how 
to obtain the parent object of a particular group or dataset instance. 
This is a rather complicated issue which does not have a good solution 
at all. 

Consider the following structure within an HDF5 file


It is clear from this situation that there are obviously two possible parent 
objects from which we could choose. Though one could maybe claim that the 
*entry_2* is the parent as it is connected to the dataset via a hard link. 
However, in principle it is possible to construct several hard links to 
a particular object. Thus the hard link is not a criteria for being the 
parent object. 

.. admonition:: Conclusion

    This problem cannot be solved. Due to the graph structure of the objects
    within a file it is not possible to determine a unique parent for a 
    particular object. It does not even make sense to ask for it. 
    This has implications on the logic of applications using this interface 
    which should be taken into account. 
    
Possible solution on library level
==================================

There is obviously no exact solution for this issue. However, one could think
about a more pragmatic solution. 

    
    
Possible solutions for applications
===================================

Though we cannot obtain the parent of an object from the object itself (at 
least not in a unique way), we could obtain the path to the parent 
object from the path used to access the original object. 
This is why the :cpp:class:`path_t` utility type was introduced. Being 
easily  
