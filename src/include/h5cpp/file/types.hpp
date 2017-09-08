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
// Created on: Sep 8, 2017
//
#pragma once

#include <iostream>
extern "C" {
#include <hdf5.h>
}


namespace hdf5 {
namespace file {

//!
//! \brief flags controlling file opening and creation
//!
enum class AccessFlags : unsigned
{
  TRUNCATE  = 0x0002,
  EXCLUSIVE = 0x0004,
  READWRITE = 0x0001,
  READONLY  = 0x0000,
#if H5_VERSION_GE(1,10,0)
  SWMR_READ = H5F_ACC_SWMR_WRITE,
  SWMR_READ = H5F_ACC_SWMR_READ
#endif
};

std::ostream &operator<<(std::ostream &stream,const AccessFlags &flags);


//!
//! \brief flags controlling object search in a file
//!
enum class SearchFlags : unsigned int
{
  FILE      = H5F_OBJ_FILE,
  DATASET   = H5F_OBJ_DATASET,
  GROUP     = H5F_OBJ_GROUP,
  DATATYPE  = H5F_OBJ_DATATYPE,
  ATTRIBUTE = H5F_OBJ_ATTR,
  ALL       = H5F_OBJ_ALL,
  LOCAL     = H5F_OBJ_LOCAL
};

using SearchFlagsBase = std::underlying_type<SearchFlags>::type;

std::ostream &operator<<(std::ostream &stream,const SearchFlags &flags);

SearchFlagsBase operator|(const SearchFlags &lhs,const SearchFlags &rhs);
SearchFlagsBase operator|(const SearchFlags &lhs,const SearchFlagsBase &rhs);
SearchFlagsBase operator|(const SearchFlagsBase &lhs,const SearchFlags &rhs);


} // namespace file
} // namespace hdf5
