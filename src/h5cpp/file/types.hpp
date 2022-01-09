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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 8, 2017
//
#pragma once

#include <iostream>
#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace file {

//!
//! \brief flags controlling file opening and creation
//!
enum class AccessFlags : unsigned
{
  Truncate  = 0x0002,
  Exclusive = 0x0004,
  ReadWrite = 0x0001,
  ReadOnly  = 0x0000,
#if ( defined(_DOXYGEN_) || H5_VERSION_GE(1,10,0) )
  //! (*since hdf5 1.10.0*)
  SWMRRead = 0x0040,
  //! (*since hdf5 1.10.0*)
  SWMRWrite = 0x0020
#endif
};
using AccessFlagsBase = std::underlying_type<AccessFlags>::type;

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const AccessFlags &flags);

DLL_EXPORT AccessFlagsBase operator|(const AccessFlags &lhs,const AccessFlags &rhs);
DLL_EXPORT AccessFlagsBase operator|(const AccessFlagsBase &lhs,const AccessFlags &rhs);
DLL_EXPORT AccessFlagsBase operator|(const AccessFlags &lhs,const AccessFlagsBase &rhs);

DLL_EXPORT AccessFlagsBase operator&(const AccessFlags &lhs,const AccessFlags &rhs);
DLL_EXPORT AccessFlagsBase operator&(const AccessFlagsBase &lhs,const AccessFlags &rhs);
DLL_EXPORT AccessFlagsBase operator&(const AccessFlags &lhs,const AccessFlagsBase &rhs);

//!
//! \brief flags controlling image file opening and getting
//!
enum class ImageFlags : unsigned
{
  ReadOnly  = 0x0000,
  ReadWrite = H5LT_FILE_IMAGE_OPEN_RW,
  DontCopy = H5LT_FILE_IMAGE_DONT_COPY,
  DontRelease  = H5LT_FILE_IMAGE_DONT_RELEASE,
  All = H5LT_FILE_IMAGE_ALL
};

using ImageFlagsBase = std::underlying_type<ImageFlags>::type;

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const ImageFlags &flags);

DLL_EXPORT ImageFlagsBase operator|(const ImageFlags &lhs,const ImageFlags &rhs);
DLL_EXPORT ImageFlagsBase operator|(const ImageFlagsBase &lhs,const ImageFlags &rhs);
DLL_EXPORT ImageFlagsBase operator|(const ImageFlags &lhs,const ImageFlagsBase &rhs);

DLL_EXPORT ImageFlagsBase operator&(const ImageFlags &lhs,const ImageFlags &rhs);
DLL_EXPORT ImageFlagsBase operator&(const ImageFlagsBase &lhs,const ImageFlags &rhs);
DLL_EXPORT ImageFlagsBase operator&(const ImageFlags &lhs,const ImageFlagsBase &rhs);

//!
//! \brief flags controlling object search in a file
//!
enum class SearchFlags : unsigned int
{
  File      = H5F_OBJ_FILE,
  Dataset   = H5F_OBJ_DATASET,
  Group     = H5F_OBJ_GROUP,
  Datatype  = H5F_OBJ_DATATYPE,
  Attribute = H5F_OBJ_ATTR,
  All       = H5F_OBJ_ALL,
  Local     = H5F_OBJ_LOCAL
};

using SearchFlagsBase = std::underlying_type<SearchFlags>::type;

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const SearchFlags &flags);

DLL_EXPORT SearchFlagsBase operator|(const SearchFlags &lhs,const SearchFlags &rhs);
DLL_EXPORT SearchFlagsBase operator|(const SearchFlags &lhs,const SearchFlagsBase &rhs);
DLL_EXPORT SearchFlagsBase operator|(const SearchFlagsBase &lhs,const SearchFlags &rhs);

DLL_EXPORT SearchFlagsBase operator&(const SearchFlags &lhs,const SearchFlags &rhs);
DLL_EXPORT SearchFlagsBase operator&(const SearchFlags &lhs,const SearchFlagsBase &rhs);
DLL_EXPORT SearchFlagsBase operator&(const SearchFlagsBase &lhs,const SearchFlags &rhs);

//!
//! \brief file scope
//!
enum class Scope : std::underlying_type<H5F_scope_t>::type
{
  Local = H5F_SCOPE_LOCAL,
  Global = H5F_SCOPE_GLOBAL
};

using ScopeBase = std::underlying_type<Scope>::type;

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const Scope &scope);



} // namespace file
} // namespace hdf5
