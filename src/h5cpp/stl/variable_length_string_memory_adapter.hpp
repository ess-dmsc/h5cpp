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
// Created on: Sep 8, 2019
//
#pragma once

#include <h5cpp/memory/memory_adapter.hpp>
#include <h5cpp/stl/string_types.hpp>

namespace hdf5 {
namespace memory {

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
template<>
class MemoryAdapter<type::VariableUTF8String>
{
  private:
    type::VariableUTF8String &_reference;
    std::vector<char*> _buffer;
  public:
    using InstanceType = type::VariableUTF8String;
    using DataspaceType = typename dataspace::TypeTrait<InstanceType>::DataspaceType;
    using DatatypeType = typename datatype::TypeTrait<InstanceType>::TypeClass;

    explicit MemoryAdapter(InstanceType &instance):
      _reference(instance),
      _buffer(1)
    {}

    MemoryAdapter(const MemoryAdapter<type::VariableUTF8String> &) = delete;
    MemoryAdapter(MemoryAdapter<type::VariableUTF8String> &&) = default;

    void* pointer()
    {
      return reinterpret_cast<void*>(&_reference);
    }

    const void* pointer() const
    {
      return reinterpret_cast<const void*>(&_reference);
    }


    DataspaceType dataspace() const
    {
      return dataspace::TypeTrait<InstanceType>::create(_reference);
    }

    DatatypeType datatype() const
    {
      return datatype::TypeTrait<InstanceType>::create(_reference);
    }


    static InstanceType create(const datatype::Datatype& = datatype::Datatype(),
                               const dataspace::Dataspace & = dataspace::Dataspace())
    {
      return InstanceType();
    }

    /**
     * @brief update the target data structure
     *
     * After every write operation on the buffer provided by the adapter,
     * which means after every read operation from the view point of HDF5,
     * the update method ensures that all data is copied to the original
     * data structure.
     */
    void update() {}

};


} // end of namespace memory
} // end of namespace hdf5
