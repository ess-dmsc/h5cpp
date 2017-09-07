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
// Created on: Aug 24, 2017
//
#pragma once

#include <iostream>
#include <type_traits>
extern "C" {
#include <hdf5.h>
}

namespace hdf5 {
namespace dataspace {

enum class Type : std::underlying_type<H5S_class_t>::type
{
  SCALAR = H5S_SCALAR,
  SIMPLE = H5S_SIMPLE,
  NODATA = H5S_NULL
};

std::ostream &operator<<(std::ostream &stream,const Type &t);

//!
//! \brief selection type
//!
//! Determines what kind of selection is applied to a datatype.
//!
enum class SelectionType : std::underlying_type<H5S_sel_type>::type
{
  NONE      = H5S_SEL_NONE,
  POINTS    = H5S_SEL_POINTS,
  HYPERSLAB = H5S_SEL_HYPERSLABS,
  ALL       = H5S_SEL_ALL
};

std::ostream &operator<<(std::ostream &stream,const SelectionType &t);

//!
//! \brief selection operator
//!
enum class SelectionOperation : std::underlying_type<H5S_seloper_t>::type
{
  SET     = H5S_SELECT_SET,
  OR      = H5S_SELECT_OR,
  AND     = H5S_SELECT_AND,
  XOR     = H5S_SELECT_XOR,
  NOTB    = H5S_SELECT_NOTB,
  NOTA    = H5S_SELECT_NOTA,
  APPEND  = H5S_SELECT_APPEND,
  PREPEND = H5S_SELECT_PREPEND
};

std::ostream &operator<<(std::ostream &stream,const SelectionOperation &o);

} // namespace dataspace
} // namespace hdf5
