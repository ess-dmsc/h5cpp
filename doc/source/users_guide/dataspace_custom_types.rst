==================================
Using dataspaces with custom types
==================================

*h5cpp* makes some default assumptions about which dataspace to use for a
particular type

* for the container templates  :cpp:class:`std::vector` and 
  :cpp:class:`std::array` a :cpp:class:`Simple` dataspace of rank 1 is used
* for everything else :cpp:class:`hdf5::dataspace::Scalar` is used.  

However, in the case of user defined data types the user has to provide 
a type trait to tell *h5cpp* what dataspace to use for the type. 

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

The most natural choice for a dataspace for such a type would be a simple 
dataspace of shape 3x3 with fixed dimensions. To achive this we have to provide
a type trait as follows

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
