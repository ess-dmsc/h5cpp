//
// (c) Copyright 2019 DESY,ESS
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Sep 1, 2019
//
#pragma once

#include <h5cpp/hdf5.hpp>


namespace hdf5 {
namespace memory {


template<typename T>
class MemoryAdapter<std::vector<T>>
{
  private:
    std::vector<T> &_reference;
  public:
    using BaseType = T;
    using DataspaceType = dataspace::Simple;
    using DatatypeType = typename datatype::TypeTrait<BaseType>::TypeClass;


    explicit MemoryAdapter(std::vector<T> &instance):
      _reference(instance)
    {}

    MemoryAdapter(const MemoryAdapter<std::vector<T>> &) = default;
    MemoryAdapter(MemoryAdapter<std::vector<T>> &&) = default;

    void* pointer()
    {
      return reinterpret_cast<void*>(_reference.data());
    }

    const void* pointer() const
    {
      return reinterpret_cast<const void*>(_reference.data());
    }


    DataspaceType dataspace() const
    {
      return dataspace::Simple({_reference.size()});
    }

    DatatypeType datatype() const
    {
      return datatype::TypeTrait<BaseType>::create();
    }


    static std::vector<T> create(const datatype::Datatype &type,
                                 const dataspace::Dataspace &space)
    {
      return std::vector<T>(space.size());
    }

};

} // end of namespace memory
} // end of namespace hdf5
