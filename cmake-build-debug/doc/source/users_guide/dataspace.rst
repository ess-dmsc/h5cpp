==========
Dataspaces
==========

An important concept in HDF5 are dataspaces. A dataspace describes the layout
of dataelements (which are described by a datatype) on disk as well as 
in memory. In addition dataspaces are used to discribe selections in a
dataset.  

.. figure:: ../images/hdf5_dataspaces.svg
   :align: center
   :width: 75%
   
Currently two of the three dataspaces available in HDF5 are implemented 
in *h5cpp*

* a *scalar* dataspace (:cpp:class:`hdf5::dataspace::Scalar`)
* and a *simple* dataspace (:cpp:class:`hdf5::dataspace::Simple`). 

Dataspaces and related classes can be cound in namespace 
:cpp:any:`hdf5::dataspace`. As shown above all dataspace classes derive from 
a common base class :cpp:class:`hdf5::dataspace::Dataspace` which can be passed 
around whenever a dataspace is needed and the particular type is not relevant. 


Dataspace inquery
=================

The :cpp:class:`hdf5::dataspace::Dataspace` class provides a couple of 
common inquery methods. 

.. cpp::namespace:: hdf5::dataspace

.. cpp:class:: Dataspace

    .. cpp:function:: size_t size()
    
        returns the number of elements which can be stored in a dataspace
        independent of whether a selection has been applied or not. 
        
    .. cpp:function:: Type type() 
    
        returns the type of the dataspace instance 
            
The :cpp:enum:`hdf5::dataspace::Type` identifies the particular type of 
the dataspace there is currently 

.. cpp:enum-class:: Type

    .. cpp:enumerator:: SIMPLE 
    
        for a simple datatype
        
    .. cpp:enumerator:: SCALAR
    
        for a scalar datatype

See :ref:`dataspace-conversion` for a good example of how to use the 
:cpp:func:`Dataspace::type` and the :cpp:enum:`Type` enumeration.

.. _dataspace-scalar:

The scalar dataspace
====================

A scalar dataspace can, as the name already suggests, store a single data 
element. Its construction is thus fairly easy 

.. code-block:: cpp

    namespace hdf5;
    
    dataspace::Scalar space;
    
A valid scalar dataspace can easily instantiated using the default constructor
as there is nothing special to be set. 


.. _dataspace-simple:

The simple dataspace
====================

A simple dataspace can describe a multidimensional array of data elements. 
Such a dataspace has two basic properties 

* the *rank* of the dataspace which is the number of dimensions
* and the *dimensions* which is the number of elements along each dimension. 

In *h5cpp* a simple dataspace can be constructed using the 
:cpp:class:`hdf5::dataspace::Simple` class. There are basically three 
configurations we could use 

* a dataspace of fixed size 
* an extensible dataspace with bounded maximum dimensions
* an extensible dataspace with unbounded maximum dimensions

To create a simple dataspace with fixed dimensions use 

.. code-block:: cpp

    using namespace hdf5;
    
    dataspace::Simple space({2,3}); 
    
    Dimensions current = space.current_dimensions(); // {2,3}
    Dimensions maximum = space.maximum_dimensions(); // {2,3} too
    
.. figure:: ../images/static_dataspace.svg
   :align: center
   :width: 20%
    
which will result in a dataspace of rank 2 with 6 elements. To build  an 
extensible dataspace with fixed bounds we could use 

.. code-block:: cpp

    using namespace hdf5;
    
    dataspace::Simple space({2,3},{10,10}); 
    
    space.current_dimensions(); // {2,3}
    space.maximum_dimensions(); // {10,10}
    
.. figure:: ../images/dynamic_dataspace_bounded.svg
   :align: center
   :width: 40%
    
Finally, for an extensible dataspace with an unlimited number of elements 
along a dimension we could use 

.. code-block:: cpp

    using namespace hdf5;
    
    dataspace::Simple space({1},{dataspace::Simple::UNLIMITED}); 
    
.. figure:: ../images/dynamic_dataspace_unbounded.svg
   :align: center
   :width: 30%
    
The initial size of the dataspace  would be 1. However, we could extend it 
as much as we want (basically can). We will see later how to use this feature
along with datasets. 

A simple dataspace can be completely modified during the lifetime of an 
instance. For instance 

.. code-block:: cpp

    using namespace hdf5;
    
    dataspace::Simple space({3}); // rank=1,size=3
    space.dimensions({2,3},{5,10}); // rank=2,size=6 
    
    


.. _dataspace-conversion: 

Dataspace conversion
====================

For all dataspace classes it is possible to construct a new instance from 
an instance of :cpp:class:`hdf5::dataspace::Dataspace` as they provide a 
special conversion copy constructor 

.. code-block:: cpp

    using namespace hdf5;

    dataspace::Dataspace &general_dataspace = ...;
    dataspace::Simple simple_dataspace(general_dataspace);
    
Using the inquery functions one could for instance use this along with an 
STL container to obtain all simple dataspaces in a collection sdfsdfsf 

.. code-block:: cpp

    using namespace hdf5::dataspace;

    std::vector<Dataspace> all_dataspaces = ...;
    std::vector<Simple> simple_dataspaces; 
    
    std::copy_if(all_dataspaces.begin(),all_dataspaces.end(),
                 std::back_inserter(simple_dataspaces),
                 [](const Dataspace &space)
                 {
                    return space.type() == Type::SIMPLE;
                 });
                 
Dataspace type trait
====================

When working with user defined types a new type trait to create a dataspace 
must be provided if something else than a scalar dataspace should be 
returned for this type. 

As an example we consider here a trait for a 3x3 matrix type. The C++ class
template for such a class could look like this 

.. code-block:: cpp

    template<typename T> class Matrix
    {
      private:
        std::array<T,9> data_; 
      public:
      
        T *data();
        const T *data() const;
    }; 

Now as a dataspace for such a type we would like to have a simple dataspace 
of shape 3x3 and fixed size. The type trait which must be provided could 
look like this 

.. code-block:: cpp

    #include <h5cpp/hdf5.cpp>
    
    namespace hdf5 {
    namespace dataspace {
    
    
    template<> class TypeTrait<Matrix>
    {
      public:
        using DataspaceType = Simple;
        static DataspaceType create(const Matrix &)
        {
          return Simple({3,3});
        }
    
        static void *ptr(Matrix &value)
        {
          return reinterpret_cast<void*>(value.data());
        }
    
        static const void*cptr(const Matrix &value)
        {
          return reinterpret_cast<const void*>(value.data());
        }
    };
    }
    }
    
Selections
==========

Selections in HDF5 allow the user to read or write only specific data to or 
from a file. This is particularly useful if the total size of a dataset 
is too large to fit into memory or only the specific data is required 
to performa particular action. 


.. figure:: ../images/hdf5_selections.svg
   :align: center
   :width: 60%
   
HDF5 provides two types of selections 

* *hyperslabs* (:cpp:class:`hdf5::dataspace::Hyperslab`) which are 
  multidimensional selections that maybe can be compared to the complex array 
  slicing and indexing features that numpy arrays allow in Python 
* *point selections* (:cpp:class:`hdf5::dataspace::Points`) which allow picking 
  individual elements from a dataset. 
  
All selections derive from :cpp:class:`hdf5::dataspace::Selection`. This 
class basically provides a single method to apply a selection on a dataspace. 

  
.. attention::

    Currently only hyperslabs are implemented in *h5cpp*.
    
    
Applying a selection
--------------------

To apply a selection you need to

.. figure:: ../images/hdf5_selection_manager.svg
   :align: center
   :width: 75%
   
.. todo:: finish this section

Hyperslab selections
--------------------

.. todo:: write this section

Point selections
----------------

.. todo:: write this section


