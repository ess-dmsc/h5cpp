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
// Created on: Sep 8, 2017
//

#include <h5cpp/file/types.hpp>

namespace hdf5 {
namespace file {

std::ostream &operator<<(std::ostream &stream,const AccessFlags &flags)
{
  switch(flags)
  {
    case AccessFlags::EXCLUSIVE: return stream<<"EXCLUSIVE";
    case AccessFlags::READONLY: return stream<<"READONLY";
    case AccessFlags::READWRITE: return stream<<"READWRITE";
    case AccessFlags::TRUNCATE: return stream<<"TRUNCATE";
#if H5_VERSION_GE(1,10,0)
    case AccessFlags::SWMR_READ: return stream<<"SWMR READ";
    case AccessFlags::SWMR_WRITE: return stream<<"SWMR WRITE";
#endif
    default:
      return stream;
  }
}

std::ostream &operator<<(std::ostream &stream,const SearchFlags &flags)
{
  switch(flags)
  {
    case SearchFlags::ALL: return stream<<"ALL";
    case SearchFlags::ATTRIBUTE: return stream<<"ATTRIBUTE";
    case SearchFlags::DATASET: return stream<<"DATASET";
    case SearchFlags::DATATYPE: return stream<<"DATATYPE";
    case SearchFlags::FILE: return stream<<"FILE";
    case SearchFlags::GROUP: return stream<<"GROUP";
    case SearchFlags::LOCAL: return stream<<"LOCAL";
    default:
      return stream;
  }
}

SearchFlagsBase operator|(const SearchFlags &lhs,const SearchFlags &rhs)
{
  return static_cast<SearchFlagsBase>(lhs) | static_cast<SearchFlagsBase>(rhs);
}

SearchFlagsBase operator|(const SearchFlags &lhs,const SearchFlagsBase &rhs)
{
  return static_cast<SearchFlagsBase>(lhs) | rhs;
}

SearchFlagsBase operator|(const SearchFlagsBase &lhs,const SearchFlags &rhs)
{
  return rhs | lhs;
}

std::ostream &operator<<(std::ostream &stream,const Scope &scope)
{
  switch(scope)
  {
    case Scope::GLOBAL: return stream<<"GLOBAL";
    case Scope::LOCAL: return stream<<"LOCAL";
    default:
      return stream;
  }
}


} // namespace file
} // namespace hdf5
