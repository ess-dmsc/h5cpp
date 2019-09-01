//
// (c) Copyright 2019 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Sep 1, 2019
//
#pragma once

#include <type_traits>
#include <h5cpp/hdf5.hpp>

namespace hdf5 {
namespace memory {


template<bool is_const_type>
struct VoidType {
    using type = void;
};

template<> struct VoidType<true>
{
    using type = const void;
};


//! \brief the basic memory adapter template
//!
//! Memory adapters are the corner stones of h5cpp's IO system. They provide
//! access to the memory occupied by an instance of a particular datatype.
//! Unlike the trait classes which have been there since the beginning
//! these templates allow to store state and thus could be used to provide
//! intermediate buffers required by some in-memory structures not compatible
//! with HDF5.
//!
//! \tparam T the type parameters
//!
template<typename T>
class MemoryAdapter
{
  private:
    T &_reference;
  public:
    using BaseType = typename std::remove_cv<T>::type;
    using DataspaceType = typename dataspace::TypeTrait<BaseType>::DataspaceType;
    using DatatypeType = typename datatype::TypeTrait<BaseType>::TypeClass;
    using VoidPtrType = typename VoidType<std::is_const<T>::value>::type*;

    explicit MemoryAdapter(T &instance):
      _reference(instance)
    {}

    MemoryAdapter(const MemoryAdapter<T> &) = delete;
    MemoryAdapter(MemoryAdapter<T> &&) = default;

    VoidPtrType pointer()
    {
      return reinterpret_cast<VoidPtrType>(&_reference);
    }

//    VoidPtrType pointer() const
//    {
//      return reinterpret_cast<VoidPtrType>(&_reference);
//    }


    DataspaceType dataspace() const
    {
      return dataspace::TypeTrait<BaseType>::create(_reference);
    }

    DatatypeType datatype() const
    {
      return datatype::TypeTrait<BaseType>::create(_reference);
    }


    static BaseType create(const datatype::Datatype& = datatype::Datatype(),
                    const dataspace::Dataspace & = dataspace::Dataspace())
    {
      return BaseType();
    }

};


template<typename T>
MemoryAdapter<T> make_adapter(T &instance)
{
  return MemoryAdapter<T>(instance);
}


} // end of namespace memory
} // end of namespace hdf5
