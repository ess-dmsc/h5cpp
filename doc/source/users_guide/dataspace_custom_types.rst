==================================
Using dataspaces with custom types
==================================

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
