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
// Created on: Oct 09, 2017
//

#include <h5cpp/property/object_copy_list.hpp>



namespace hdf5 {
namespace property {

std::ostream &operator<<(std::ostream &stream,const CopyFlag &flag)
{
  switch(flag)
  {
    case CopyFlag::SHALLOW_HIERARCHY:
      return stream<<"SHALLOW_HIERARCHY";
    case CopyFlag::EXPAND_SOFT_LINKS:
      return stream<<"EXPAND_SOFT_LINKS";
    case CopyFlag::EXPAND_EXTERNAL_LINKS:
      return stream<<"EXPAND_EXTERNAL_LINKS";
    case CopyFlag::EXPAND_REFERNCES:
      return stream<<"EXPAND_REFERENCES";
    case CopyFlag::WITHOUT_ATTRIBUTES:
      return stream<<"WITHOUT_ATTRIBUTES";
    case CopyFlag::MERGE_COMMITTED_TYPES:
      return stream<<"MERGE_COMMITTED_TYPES";
    default:
      return stream<<"NONE"; //should never happen
  }
}

} // namespace property
} // namespace hdf5
