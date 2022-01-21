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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 7, 2017
//
#pragma once

#include <vector>
#include <array>
#include <map>

#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/dataspace/scalar.hpp>
#include <h5cpp/dataspace/simple.hpp>
#include <h5cpp/dataspace/pool.hpp>
#include <h5cpp/core/types.hpp>

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
class TypeTrait {
 public:
  using DataspaceType = Scalar;
  static DataspaceType create(const T &) {
    return Scalar();
  }

  const static DataspaceType & get(const T &, DataspacePool &) {
    const static DataspaceType & cref_ = Scalar();
    return cref_;
  }

  static void *ptr(T &value) {
    return reinterpret_cast<void *>(&value);
  }

  static const void *cptr(const T &value) {
    return reinterpret_cast<const void *>(&value);
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
typename TypeTrait<T>::DataspaceType create(const T &value) {
  return TypeTrait<T>::create(value);
}

//!
//! \brief factory function for dataspace const references
//!
//! This factory function uses TypeTrait to create
//! a new dataspace const reference for a particular instance of T.
//!
//! \tparam T type for which to construct a dataspace
//!
//! \param value instance of T
//! \param pool dataspace pool
//! \return a const reference of the appropriate dataspace type
//!
template<typename T>
const typename dataspace::Dataspace & get(const T &value, DataspacePool & pool) {
  return TypeTrait<T>::get(value, pool);
}

template<typename T>
void *ptr(T &value) {
  return TypeTrait<T>::ptr(value);
}

template<typename T>
const void *cptr(const T &value) {
  return TypeTrait<T>::cptr(value);
}

//!
//! @brief data space object holder
//!
class DLL_EXPORT DataspaceHolder
{
  public:

  //!
  //! \brief default constructor
  //!
  //! The default constructor. The dataspace pool is created internally
  //!
  DataspaceHolder() : pool_ref(pool_) {}
  //!
  //! \brief constructor
  //!
  //! \param pool dataspace pool
  //!
  DataspaceHolder(DataspacePool & pool) : pool_ref(pool) {}
  //!
  //! \brief factory holder method for getting reference of data spaces
  //!
  //! Returns data space reference for static data space object if available.
  //! Otherwise it creates a new data space object and returns its reference.
  //!
  //! @param v provided dataspace data
  //! @return data space reference for data space object
  //!
  template<typename T>
    const Dataspace & get(const T & v);

 private:
      Dataspace instance;
      DataspacePool pool_;
      DataspacePool & pool_ref;
};

template<typename T>
const Dataspace & DataspaceHolder::get(const T & v)
{
  auto & space = hdf5::dataspace::get(v, pool_ref);
  if(static_cast<hid_t>(space))
    return space;

  if (!static_cast<hid_t>(instance))
    instance = hdf5::dataspace::create(v);
  return instance;
}


} // namespace dataspace
} // namespace hdf5
