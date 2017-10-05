//
// (c) Copyright 2017 DESY,ESS
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
// Created on: Sep 7, 2017
//

#include <vector>
#include <array>

#include "dataspace.hpp"
#include "scalar.hpp"
#include "simple.hpp"
#include "../types.hpp"


namespace hdf5 {
namespace dataspace {

//!
//! \brief type trait for dataspace construction
//!
//! This trait provides a static function creating a new dataspace for a particular
//! instance of T.
//! To integrate new types just add a specialization of this trait.
//!
//! \tparam T type for which to construct a dataspace
//!
template<typename T>
class TypeTrait
{
  public:
    using DataspaceType = Scalar;
    static DataspaceType create(const T &)
    {
      return Scalar();
    }

    static void *ptr(T &value)
    {
      return reinterpret_cast<void*>(&value);
    }

    static const void*cptr(const T &value)
    {
      return reinterpret_cast<const void*>(&value);
    }
};

template<typename T>
class TypeTrait<std::vector<T>>
{
  public:
    using DataspaceType = Simple;

    static DataspaceType create(const std::vector<T> &value)
    {
      return Simple(hdf5::Dimensions{value.size()},hdf5::Dimensions{value.size()});
    }

    static void *ptr(std::vector<T> &data)
    {
      return reinterpret_cast<void*>(data.data());
    }

    static const void *cptr(const std::vector<T> &data)
    {
      return reinterpret_cast<const void*>(data.data());
    }
};

template<typename T,size_t N>
class TypeTrait<std::array<T,N>>
{
  public:
    using DataspaceType = Simple;

    static DataspaceType create(const std::array<T,N> &value)
    {
      return Simple(hdf5::Dimensions{N},hdf5::Dimensions{N});
    }

    static void *ptr(std::array<T,N> &value)
    {
      return reinterpret_cast<void*>(value.data());
    }

    static const void *cptr(const std::array<T,N> &value)
    {
      return reinterpret_cast<const void *>(value.data());
    }
};


//!
//! \brief factory function for dataspaces
//!
//! This factory function uses TypeTrait to create a new dataspace for a
//! particular instance of T.
//!
//! \tparam T type for which to construct a dataspace
//!
//! \param value instance of T
//! \return an instance of the appropriate dataspace type
//!
template<typename T>
typename TypeTrait<T>::DataspaceType create(const T &value)
{
  return TypeTrait<T>::create(value);
}

template<typename T>
void *ptr(T &value)
{
  return TypeTrait<T>::ptr(value);
}

template<typename T>
const void *cptr(const T &value)
{
  return TypeTrait<T>::cptr(value);
}





} // namespace dataspace
} // namespace hdf5


