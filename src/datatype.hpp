//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
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
// Created on: Aug 15, 2017
//
#pragma once

#include <type_traits>
extern "C"{
#include<hdf5.h>
}
#include "include/h5cpp/object_handle.hpp"


namespace hdf5{



class Datatype
{
public:
  enum class Class : std::underlying_type<H5T_class_t>::type
  {
    NONE      = H5T_NO_CLASS,
    INTEGER   = H5T_INTEGER,
    FLOAT     = H5T_FLOAT,
    TIME      = H5T_TIME,
    STRING    = H5T_STRING,
    BITFIELD  = H5T_BITFIELD,
    OPAQUE    = H5T_OPAQUE,
    COMPOUND  = H5T_COMPOUND,
    REFERENCE = H5T_REFERENCE,
    ENUM      = H5T_ENUM,
    VARLENGTH = H5T_VLEN,
    ARRAY     = H5T_ARRAY

  };

  enum class Order : std::underlying_type<H5T_order_t>::type
  {
    LE = H5T_ORDER_LE,
    BE = H5T_ORDER_BE
  };

  enum class Sign : std::underlying_type<H5T_sign_t>::type
  {
    TWOS_COMPLEMENT = H5T_SGN_2,
    UNSIGNED        = H5T_SGN_NONE
  };

  static Datatype create(Class type,size_t size);

  template<typename T>
  static Datatype create();


  Datatype &operator=(const Datatype &type) = default;
  Datatype &operator=(Datatype &&type) = default;
  Datatype(const Datatype &type) = default;
  Datatype(Datatype &&type) = default;
  Datatype() = default;

private:
  Datatype(ObjectHandle &&handle);

  ObjectHandle handle_;

  friend class AccessHandle;

};

namespace prefdefined_types {

static const Datatype native_int;
static const Datatype native_double;
static const Datatype native_long_double;
static const Datatype native_short;


} // namespace predefined_types



} // namespace hdf5
