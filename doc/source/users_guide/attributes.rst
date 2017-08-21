=======================
Working with attributes
=======================

The attributes of an object can be accessed via the public attribute 
:cpp:member:`attributes` of a group or dataset.  
:cpp:member:`attributes` is an instance of :cpp:type:`attribute_manager_t` 
providing an STL compliant  interface for attributes.

The general interface of :cpp:type:`attribute_manager_t` looks somewhat like 
this 

.. code-block:: cpp

    class attribute_manager_t
    {
        public:
            using const_iterator = ....;
            using value_type = attribute_t;

            //
            // create a new HDF5 attribute on the managers parent
            //
            // Full version with default property lists (they are included here
            // just for the sake of completeness and later usage).
            //!
            attribute_t create(const string &name,
                               const datatype_t &type,
                               const dataspace_t &space,
                               const attribute_create_plist_t &cpl = attribute_create_plist_t(),
                               const attribute_access_plist_t &apl = attribute_access_plist_t());

            // we should possible add some convenience functions to make
            // attribute creation easier


            //get attribute by index
            attribute_t operator[](size_t index) const;
            //get attribute by name
            attribute_t operator[](const string &name) const;
            
            //get the number of attributes
            size_t size() const;

            const_iterator begin() const;
            const_iterator end() const;
    };

Creating attributes
===================

.. todo::

    Still do be done - depends on the interface provided by
    :cpp:class:`attribute_manager_t`.

Accessing attributes
====================

Iterating over attributes

.. code-block:: cpp
    
    h5::group_t group = ....;

    for(auto attribute: group.attributes)
    {
        std::cout<<attribute.name()<<std::endl;
    }

or alternatively 

.. code-block:: cpp

    h5::group_t group = ....;

    std::for_each(group.attribtues.begin(),
                  group.attributes.end(),
                  [](const auto &attr) { std::cout<<attr.name()<<std::endl; });

For the time being attributes will not support partial IO (as datasets do). 
Attributes can also be accessed by index. 

.. code-block:: cpp

    h5::group_t group = ....;

    for(size_t index=0;index<group.attributes.size();index++)
    {
        std::cout<<group.attributes[index].name()<<std::endl;
    }

Reading and writing data
========================

As proposed in :ref:`design-read-write` :cpp:class:`attribute_t` provides 
:cpp:func:`read` and :cpp:func:`write` methods to read and write data. 

.. code-block:: cpp

    attribute_t attr = group.attributes["NX_class"];

    attr.write("NXdetector");

    string nx_class;
    attr.read(nx_class);


