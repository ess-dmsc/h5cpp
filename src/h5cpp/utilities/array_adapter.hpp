//
// (c) Copyright 2018 DESY,ESS
//
// This file is part of h5cpp.
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published
// by the Free Software Foundation; either version 2.1 of the License, or
// (at your option) any later version.
//
// This library is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty ofMERCHANTABILITY
// or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor
// Boston, MA  02110-1301 USA
// ===========================================================================
//
// Authors: Eugen Wintersberger <eugen.wintersberger@gmail.com>
//          Jan Kotanski <jan.kotanski@desy.de>
// Created on: Jul 1, 2018
//
#pragma once

#include <cstdint>
#include <vector>

#include <h5cpp/core/types.hpp>
#include <h5cpp/dataspace/type_trait.hpp>
#include <h5cpp/datatype/type_trait.hpp>

namespace hdf5 {

//!
//! \brief adapter for C-style arrays
//!
//! In order to work read or write data from and to C-style arrays a special
//! adapter is required. A native C-array does not carry all the information
//! required to construct a dataspace for HDF5 IO. It lacks the size
//! information. A dataspace and a datatype trait exist for this adapter
//! template.
//!
//! \code
//! double *data = new double[100];
//!
//! \endcode
//!
//! The ArrayAdapter<T> template does not hold ownership of the array it
//! references. So all resource management has to be done by the calling
//! instance.
//!
//! \tparam T data type of the pointer
//!
template<typename T> class ArrayAdapter
{
  private:
    T *data_;
    size_t size_;

    //!
    //! \brief reset the adapter
    //!
    //! Internal utility function which sets the pointer to nullptr and the
    //! size to 0.
    //!
    void reset() noexcept
    {
      data_ = nullptr;
      size_ = 0;
    }

  public:
    //!
    //! \brief default constructor
    //!
    ArrayAdapter():
      data_(nullptr),
      size_(0)
    {}

    //!
    //! \brief constructor
    //!
    //! \param data pointer to the data data to which to read or write data
    //! \param size number of elements referenced by the pointer
    //!
    ArrayAdapter(T *data,size_t size):
      data_(data),
      size_(size)
    {}

    //!
    //! \brief copy constructor
    //!
    ArrayAdapter(const ArrayAdapter<T> &adapter);

    //!
    //! \brief move constructor
    //!
    ArrayAdapter(ArrayAdapter<T> &&adapter);

    //!
    //! \brief copy assignment
    //!
    ArrayAdapter<T> &operator=(const ArrayAdapter<T> &adapter);

    //!
    //! \brief move assignment
    //!
    ArrayAdapter<T> &operator=(ArrayAdapter<T> &&adapter);

    size_t size() const noexcept
    {
      return size_;
    }

    T *data() noexcept
    {
      return data_;
    }

    const T *data() const noexcept
    {
      return data_;
    }
};

template<typename T>
ArrayAdapter<T>::ArrayAdapter(const ArrayAdapter<T> &adapter):
  data_(adapter.data_),
  size_(adapter.size_)
{
}

template<typename T>
ArrayAdapter<T>::ArrayAdapter(ArrayAdapter<T> &&adapter):
  data_(adapter.data_),
  size_(adapter.size_)
{
  //declare the original adapter instance as invalid
  adapter.reset();
}

template<typename T>
ArrayAdapter<T> &ArrayAdapter<T>::operator=(const ArrayAdapter<T> &adapter)
{
  if(this == &adapter)
    return *this;

  data_ = adapter.data_;
  size_ = adapter.size_;
  return *this;
}

template<typename T>
ArrayAdapter<T> &ArrayAdapter<T>::operator=(ArrayAdapter<T> &&adapter)
{
  if(this == &adapter)
    return *this;

  data_ = adapter.data_;
  size_ = adapter.size_;
  adapter.reset();

  return *this;
}


//!
//! \brief get dimensions for an array adapter instance
//!
//! This utility function returns the dimensions of a particular array adapter
//! instance.
//!
//! \tparam T type of the array elements
//! \param adapter reference to the array adapter for which to get the dimensions
//! \return Dimensions instance with the actual dimensions of the array adapter
//!
template<typename T>
Dimensions get_dimensions(const ArrayAdapter<T> adapter)
{
  return Dimensions{adapter.size()};
}


namespace datatype {

//!
//! \brief datatype type trait for array adapters
//!
//! Specizlization of the datatype type trait for ArrayAdapter types.
//!
//! \tparam T type of elements of the array reference by the array adapter
//!
template<typename T>
class TypeTrait<ArrayAdapter<T>>
{
  public:
    using TypeClass = typename TypeTrait<T>::TypeClass;

    static TypeClass create(const ArrayAdapter<T> & = ArrayAdapter<T>())
    {
      return TypeTrait<T>::create();
    }
    const static TypeClass & get(const ArrayAdapter<T> & = ArrayAdapter<T>()) {
      const static TypeClass & cref_ = create();
      return cref_;
    }

};

}

namespace dataspace {

//!
//! \brief dataspace type trait for adapters
//!
//! Specializiation of the dataspace type trait for ArrayAdpater types.
//!
//! \tparam T type of elements of the array referenced by the array adapter
//!
template<typename T>
class TypeTrait<ArrayAdapter<T>>
{
  public:
    using DataspaceType = Simple;

    static DataspaceType create(const ArrayAdapter<T> &adapter)
    {
      Dimensions adapter_dimensions = get_dimensions(adapter);
      return Simple(adapter_dimensions,adapter_dimensions);
    }

    const static DataspaceType & get(const ArrayAdapter<T> &adapter, dataspace::DataspacePool &pool) {
      return pool.getSimple(get_dimensions(adapter));
    }

    static void* ptr(ArrayAdapter<T> &adapter)
    {
      return reinterpret_cast<void*>(adapter.data());
    }

    static const void *cptr(const ArrayAdapter<T> &adapter)
    {
      return reinterpret_cast<const void*>(adapter.data());
    }

};

}

}
