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
#include <complex>
#include <h5cpp/stl/complex_datatype_trait.hpp>


namespace hdf5 {
namespace memory {


/**
 * @brief memory adapter for a complex number
 */
template<typename T>
class MemoryAdapter<std::complex<T>>
{
  private:
    /**
     * reference to the actual value
     */
    std::complex<T> &_reference;
  public:
    using Type = std::complex<T>;
    using BaseType = T;
    using DataspaceType = dataspace::Scalar;
    using DatatypeType = datatype::Compound;


    /**
     * @brief constructor
     *
     * @param instance reference to the complex number instance
     */
    explicit MemoryAdapter(Type &instance):
      _reference(instance)
    {}

    MemoryAdapter(const MemoryAdapter<Type> &) = delete;
    MemoryAdapter(MemoryAdapter<Type> &&) = default;

    /**
     * @brief return read/write pointer
     */
    void* pointer()
    {
      return reinterpret_cast<void*>(&_reference);
    }

    /**
     * @brief return read-only pointer
     */
    const void* pointer() const
    {
      return reinterpret_cast<const void*>(&_reference);
    }

    /**
     * @brief create a dataspace for a complex number
     */
    DataspaceType dataspace() const
    {
      return dataspace::Scalar();
    }

    /**
     * @brief create an HDF5 datatype for a complex number
     *
     * A complex number is stored in a compound data type
     *
     * @return compound datatype to store a complex number
     */
    DatatypeType datatype() const
    {
      return datatype::Trait<Type>::create();
    }


    static std::complex<T> create(const datatype::Datatype &type,
                                  const dataspace::Dataspace &space)
    {
      return Type();
    }

};

} // end of namespace memory
} // end of namespace hdf5
