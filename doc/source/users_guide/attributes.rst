=======================
Working with attributes
=======================

Every node can be augumented with attributes. Attributes behave a bit like 
datasets but lack some of the features the latter provides 

* there is no partial IO on attributes
* attribute data cannot be compressed. 
* you cannot use virtual datasets or SWMR on attributes. 

Attributes can be accessed via the :cpp:class:`hdf5::attribute::Manager` interface
exposed by the :cpp:member:`attributes` member of every :cpp:class:`hdf5::node::Node` 
instance. :cpp:class:`hdf5::attribute::Manager` provides an STL compliant 
container interface to attributes which is somehow similar to that of 
:cpp:class:`hdf5::node::LinkView` or :cpp:class:`hdf5::node::NodeView`. 

An attribute itself is represented by an instance of 
:cpp:class:`hdf5::attribute::Attribute`. 

Basic attribute management
==========================

Creating attributes
-------------------

Attribute creation is done via the :cpp:func:`create` member function 
of the attribute manager interface. 
To create a simple scalar string attribute you could use 

.. code-block:: cpp

   using hdf5::attribute::Attribute; 
   hdf5::node::Dataset dataset = ...;
   
   Attribute attribute = dataset.attributes.create<std::string>("author"); 
   
A multidimensional attribute can be created using 

.. code-block:: cpp

   Attribute attribute = dataset.attributes.create<float>("orientation_matrix",{3,3});
   
which would lead to a 3x3 matrix attribute of type :cpp:type:`float`. 
There exists also a non template version of :cpp:func:`create` which 
exposes all the flexibility HDF5 provides. So we could write the last 
example also with 

.. code-block:: cpp

   hdf5::dataspace::Simple space{{3,3}};
   auto type = hdf5::datatype::create<float>(); 
   Attribute attr = dataset.attributes.create("orientation_matrix",type,space);
   


Removing attributes
-------------------

Attributes can be removed using the :cpp:func:`remove` member functions of 
:cpp:class:`hdf5::attribute::Manager`. This function takes either the index 
of the name of an attribute as its key 

.. code-block:: cpp

   hdf5::node::Dataset dataset = ... ;
   
   dataset.attributes.remove(1); //remove attribute with index 1
   dataset.attributes.remove("temperature"); //remove attribute "temperature"
   
Both methods throw :cpp:class:`std::runtime_error` in the case of a failure. 


Attribute inquery
-----------------

If we would like to know how many attributes are attached to a node we could
use the :cpp:func:`size` member function of the manager interface. 

.. code-block:: cpp

   hdf5::node::Group group = ...;
   std::cout<<"Number of attributes: "<<group.attributes.size()<<std::endl; 
   
the :cpp:func:`exists` method checks for the existence of a particular 
attribute with a given name

.. code-block:: cpp

   hdf5::node::Group group = ...;
   
   if(group.attributes.exists("NX_class"))
   {
    ....
   }
   



Accessing attributes
====================

Element wise access
-------------------

Like nodes or links, attributes can be either accessed via their name 
or by their index. 

.. code-block:: cpp

   hdf5::node::Dataset dataset = ...;
   
   std::cout<<dataset.attributes["temperature"].name()<<std::endl;
   std::cout<<dataset.attributes[1].name()<<std::endl; 

Iteartor access
---------------

Iterating over attributes

.. code-block:: cpp
    
    hdf5::node::Group group = ....;

    for(auto attribute: group.attributes)
    {
        std::cout<<attribute.name()<<std::endl;
    }

or alternatively 

.. code-block:: cpp

    hdf5::node::Group group = ....;

    std::for_each(group.attribtues.begin(),
                  group.attributes.end(),
                  [](const hdf5::attribute::Attribute &attr) 
                  { std::cout<<attr.name()<<std::endl; });


Reading and writing data
========================

As proposed in :ref:`design-read-write` :cpp:class:`attribute_t` provides 
:cpp:func:`read` and :cpp:func:`write` methods to read and write data. 

.. code-block:: cpp

    attribute_t attr = group.attributes["NX_class"];

    attr.write("NXdetector");

    string nx_class;
    attr.read(nx_class);


