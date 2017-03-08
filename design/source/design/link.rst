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

Iterators
=========


.. figure:: ../images/link_iterators.png
   :align: center
   :width: 400px
   
Both iterators satisfy the *ForwardIterator* concept as defined by the 
C++ standard (see `ForwardIterator concept`_ for details).
Creation of the iterators works the same as for node iterators (
see :ref:`node-iterators` for details).

.. code-block:: cpp

    namespace h5 {
    namespace link {
        
        iterator_t begin(const h5::group::group_t &group,
                         h5::utilities::iter_index_t &index,
                         h5::utilities::iter_dir_t &direction);
        iterator_t end(const h5::gruop::group_t &group);
        
        recursive_iterator_t begin_recursive(const h5::group::group_t &group,
                                             h5::utilities::iter_index_t &index,
                                             h5::utilities::iter_dir_t &direction);
        recursive_iterator_t end_recursive(const h5::group::group_t &group);
    
    }   // end of namespace node
    }   // end of namespace h5


.. _ForwardIterator concept: http://en.cppreference.com/w/cpp/concept/ForwardIterator
   
   
   

