============
C++ concepts
============

.. _concept-read-write:

The *read-writeable* concept
============================

There are basically two ways how to read and write data to and from a dataset
(the same is true for attributes)

#. use the assignment and implicit conversion operator for writing and reading
   respectively 
#. use dedicated :cpp:func:`read` and :cpp:func:`write` methods.

Each approach has its pros and cons which should be discussed here. 

The types which are affected by this section are :cpp:class:`dataset_t`,
:cpp:class:`attribute_t`, and :cpp:class:`hyperslab_t`.

Scalar and container types
--------------------------

In both cases we have to distinguish between scalar and container types. The
former one includes all POD types provided by C++, the latter one includes all
STL container storing their data contiguously in memory. 

To distinguish between these types we could use a simple template like this 

.. code-block:: cpp

    template<typename T> is_container
    {
        static const bool value = false;
    };

    template<typename T> is_container<std::vector<T>>
    {
        static const bool value = true;
    };

    template<typename T,size_t N> is_container<std::array<T,N>>
    {
        static const bool value = true;
    };

This approach has the charming advantage that a custom container type
satisfying the requirements  could be easily integrated by a developer by 
providing a template specialization for :cpp:class:`is_container`.

.. code-block:: cpp

    //
    // This container shows the minimum interface we expect 
    // to be provided by a container type
    //
    template<typename T> my_contianer
    {
        public:
            using value_type = T;
            
            size_t size() const;
            T *data();
            const T* data() const;
    };

    template<typename T> is_container<my_container<T>>
    {
        static const bool value = true;
    };

Using methods
-------------

This is the most straight forward approach. In this case an object providing
read write support could have an interface like this 

.. code-block:: cpp

    class io_object 
    {
        public:
            
            //
            // we should support reading and writing to pointers
            //
            template<typename T> 
            void write(size_t N,const T* data);

            template<typename T>
            void read(size_t N,T *data);

            //
            // writing and reading scalars
            //
            template<
                     typename T,
                     typename std::enable_if<!is_container<T>::value,int>::type= 0
                    >
            void write(const T &data);

            template<
                     typename T,
                     typename std::enable_if<!is_container<T>::value,int>::type=0>
                    >
            void read(T &data);


            //
            // writing and reading containers
            template<
                     typename T,
                     typename = std::enable_if_t<is_container<T>::value>
                    >
            void write(const T &data);

            template<
                     typename T,
                     typename = std::enable_if_t<is_container<T>::value>
                    >
            void read(T &data);
    };


.. note::

    In this case using templates is ok as it would be too tedious to provide an
    overload for every container type and, much worser, for every possible
    :cpp:type:`value_type` of this container.

Though we may have to provide some special handing for strings this approach
has the charming property that the semantics of the methods 
:cpp:func:`read` and :cpp:func:`write` is obvious. 


.. code-block:: cpp

    io_object object = ...;
    
    double temperature;
    object.read(temperature);

    std::vector<double> velocity;
    object = ...;
    object.write(velocity)

It is immediately obvious in this code what's going one. 

.. note::

    I would personally go with this approach. Not only because the obvious
    semantics of the two methods but also for reasons I will explain in the
    next subsection.

Using operators
---------------

In particular for those who are familiar with the Python :py:mod:`h5py`
package another approach might be tempting: using assignment and implicit
conversion for reading and writing. 

I will first start here with the example code to show what I mean with this:

.. code-block:: cpp

    io_object object = ....;

    double temperature = object; //reading data (conversion)

    object = ....;
    object = std::vector<double>{...}; // writing data (assignment)

A possible way how to implement this would be

.. code-block:: cpp

    class io_object
    {   
        public:

            //
            // need to provide copy and move assignment operators 
            // but we can use at least the default implementation
            //
            io_object &operator(const io_object &o) = default;
            io_object &operator(io_object &&o) = default;

            //
            // writing scalar data
            //
            template<
                     typename T,
                     typename std::enable_if<!is_container<T>::value &&
                                             !std::is_same<T,io_object>::value,
                                             int>::type = 0
                    >
            io_object &operator=(const T &data);

            
            //
            // reading scalar data
            //
            template<
                     typename T,
                     typename std::enable_if<!is_container<T>::value,int>::type=0
                    >
            operator T();

            //
            // writing container data
            //
            template<
                     typename T,
                     typename = std::enable_if_t<is_container<T>::value &&
                                                 !std::is_same<T,io_object>::value>
                    >
            io_object &operator=(const T& data);

            //
            // reading container data
            // 
            template<
                     typename T,
                     typename = std::enable_if_t<is_container<T>::value>
                    >
            operator T();
                                                 
    };
     
Though this approach looks rather elegant in the example above as we can see
the implementation has some flaws.

#. we have to provide copy and move assignment for :cpp:class:`io_object`
   itself in order to avoid problems with the write operators. 
#. the SFINAE pattern is more elaborate in particular for the assignment
   operators
#. Finally, reading data with implicit conversion problematic in particular 
   for container types.

I want to elaborate a bit on the last point. The first problem is that we have
to extend our :cpp:class:`is_container` template. The reason for this is that
the conversion method has to create a new instance of the requested container. 
Thus we would need something like this for the :cpp:class:`is_container` 
template 

.. code-block:: cpp

    template<typename T> struct is_container<std::vector<T>>
    {
        static std::vector<T> create(const dataspace_t &space)
        {
            //create an instance of std::vector<T> here
            std::vector<T> instance = .....;
            return instance; 
        }
    };

There is also some performance concern with this approach. When we iterate over
a dataset (as will be shown latter) this would mean that we would allocate a
new region of memory any time we read from the hyperslab selection (which
should provide such an interface). 
Using the simple :cpp:func:`read` and :cpp:func:`write` function approach we
could allocate a buffer for the data once before entering the loop and reuse it
in every loop cycle.

As a final conclusion: though this approach looks elegant on the first glimpse
I would go with the simple read write method for now. 