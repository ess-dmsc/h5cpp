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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 18, 2018
//
#pragma once

#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/datatype/enum.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5
{
namespace datatype
{
//!
//! \brief enumeration bool type
//!
enum EBool : int8_t
{
  False = 0,   //!< indicates a false value
  True = 1 //!< indicates a true value
};


template<>
class TypeTrait<datatype::EBool> {
 public:
  using TypeClass = datatype::Enum;
  using Type = datatype::EBool;

  static TypeClass create(const Type & = Type()) {
    auto type = TypeClass::create(Type());
    type.insert("FALSE", Type::False);
    type.insert("TRUE", Type::True);
    return type;
  }
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
  }
};


//!
//! @brief check if Enum is EBool
//!
//! @param etype object
//! @return if Enum is EBool flag
//!
DLL_EXPORT bool is_bool(const Enum & etype);

} // namespace datatype
} // namespace hdf5
