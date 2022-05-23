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
// Created on: Aug 28, 2017
//
#pragma once

#include <h5cpp/datatype/type_trait.hpp>

namespace hdf5 {
namespace datatype {

//!
//! \brief factory function for creating data types
//!
template<typename T>
typename TypeTrait<typename std::remove_const<T>::type>::TypeClass create(const T &v = T{}) {
  return TypeTrait<typename std::remove_const<T>::type>::create(v);
}
//!
//! \brief factory function for getting reference of data types
//!
template<typename T>
const Datatype & get(const T &v = T{}) {
  return TypeTrait<typename std::remove_const<T>::type>::get(v);
}

//!
//! @brief data type object holder
//!
class DLL_EXPORT DatatypeHolder
{
  public:

  //!
  //! \brief factory holder method for getting reference of data types
  //!
  //! Returns data type reference for static data type object if available.
  //! Otherwise it creates a new data type object and returns its reference.
  //!
  //! @param v provided datatype data
  //! @return data type reference for data type object
  //!
  template<typename T>
    const Datatype & get(const T & v = T{});

 private:
      Datatype instance;
};

template<typename T>
const Datatype & DatatypeHolder::get(const T & v)
{
  auto & type = hdf5::datatype::get(v);
  if(static_cast<hid_t>(type))
    return type;

  if (!static_cast<hid_t>(instance))
    instance = hdf5::datatype::create(v);
  return instance;
}

} // namespace datatype
} // namespace hdf5
