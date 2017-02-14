============================
Dealing with links and paths
============================

An HDF5 file can be considered as a collection of *objects* (*groups* and 
*datasts*), connected via a network of *links*.
Objects themselves have no name, it is the link to a particular object which 
determines its name, at least from the point of the user. The same 
object can appear under an entirely different name when using 


Problem of parenthood
=====================

A common problem is how to determine the parent of a given object. 