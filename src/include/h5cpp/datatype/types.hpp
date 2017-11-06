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
// Created on: Aug 23, 2017
//
#pragma once

#include <iostream>
#include <type_traits>
#include "../hdf5_capi.hpp"
#include "../windows.hpp"

namespace hdf5 {
namespace datatype {

const decltype(H5T_VARIABLE) kVariable = H5T_VARIABLE;

//!
//! \enum data type class
//!
//! Enumeration type describing the class a particular data type belongs to.
//!
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

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const Class &c);

//!
//! \brief enumeration type for byte order
//!
enum class Order : std::underlying_type<H5T_order_t>::type
{
  LE = H5T_ORDER_LE,
  BE = H5T_ORDER_BE
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const Order &o);

//!
//! \brief enumeration for sign
//!
enum class Sign : std::underlying_type<H5T_sign_t>::type
{
  TWOS_COMPLEMENT = H5T_SGN_2,
  UNSIGNED        = H5T_SGN_NONE
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const Sign &s);

//!
//! \brief enumeration describes mantissa norm
//!
enum class Norm : std::underlying_type<H5T_norm_t>::type
{
  IMPLIED = H5T_NORM_IMPLIED,
  MSBSET  = H5T_NORM_MSBSET,
  NONE    = H5T_NORM_NONE
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const Norm &n);

//!
//! \brief enumeration for floating point padding
//!
enum class Pad : std::underlying_type<H5T_pad_t>::type
{
  ZERO = H5T_PAD_ZERO,
  ONE  = H5T_PAD_ONE,
  BACKGROUND = H5T_PAD_BACKGROUND
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const Pad &p);

//!
//! \brief enumeration determining string padding
//!
enum class StringPad : std::underlying_type<H5T_str_t>::type
{
  NULLTERM = H5T_STR_NULLTERM,
  NULLPAD  = H5T_STR_NULLPAD,
  SPACEPAD = H5T_STR_SPACEPAD
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const StringPad &pad);

enum class Direction : std::underlying_type<H5T_direction_t>::type
{
  ASCEND = H5T_DIR_ASCEND,
  DESCEND = H5T_DIR_DESCEND
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const Direction &d);

//!
//! \brief character set encoding
//!
//! Enumeration type determining the character encoding used by string types
//! and links.
//!
enum class CharacterEncoding :  std::underlying_type<H5T_cset_t>::type
{
  ASCII = H5T_CSET_ASCII,//!< ASCII
  UTF8  = H5T_CSET_UTF8  //!< UTF8
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const CharacterEncoding &enc);


} // namespace datatype
} // namespace hdf5
