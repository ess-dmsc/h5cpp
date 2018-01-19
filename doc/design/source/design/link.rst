.. _namespace-link:

=====================================
Links (namespace :cpp:any:`h5::link`)
=====================================

Links are the glue between the nodes in an HDF5 object tree.

.. figure:: ../images/links_and_linkables.png
   :align: center
   :width: 800px

 


.. figure:: ../images/link_t_details.png
   :align: center
   :width: 500px

.. _link-iterators:

Iterators and views
===================


.. figure:: ../images/link_iterators.png
   :align: center
   :width: 400px
   
Both iterators satisfy the *ForwardIterator* concept as defined by the 
C++ standard (see `ForwardIterator concept`_ for details).
Creation of the iterators works the same as for node iterators (
see :ref:`node-iterators` for details).
Instances of these iterators are created by the appropriate *begin* and *end*
functions of the :cpp:class:`link::view_t` view class.

.. figure:: ../images/link_view_t_details.png
   :align: center
   :width: 300px

.. _ForwardIterator concept: http://en.cppreference.com/w/cpp/concept/ForwardIterator
   
   
   

