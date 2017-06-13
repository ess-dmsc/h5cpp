===================
Working with groups
===================

.. code-block:: cpp

    h5::group_t g = root_group.create("new_group",....);

Need to find a good way how to handle group creation property lists. 

Groups should provide a STL compliant iterator interface. 

.. code-block:: cpp

    class group_iterator_t
    {
        .....
    };
    
    class recursive_group_iterator_t
    {
        .....
    };

    class group_t
    {
        public:
            
            //
            // access a direct child by its index
            //        
            object_t operator()[size_t index] const;
            //
            // returns the number of direct children below the group
            //
            size_t size() const;
            
            //
            // provides access to a child by its name
            //
            // As the name can be an arbitrary path with this method 
            // an arbitrary child can be accessed from this group.
            //           
            object_t operator()[const std::string &name] const;
            
            //
            // provides access to an arbitrary object
            //
            object_t operator()[const h5::path_t &path] const;
            
            group_iterator_t begin() const;
            group_iterator_t end() const;
            
            recursive_group_iterator_t rbegin() const;
            recursive_group_iterator_t rend() const;       
    };


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

