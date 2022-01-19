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

#include <sstream>
#include <h5cpp/datatype/enum.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>
#include <h5cpp/error/error.hpp>

namespace hdf5
{
namespace datatype
{

bool is_bool(const Enum & etype){
  size_t s = etype.number_of_values();
  if(s != 2){
    return false;
  }
  if(etype.name(0) != "FALSE"){
    return false;
  }
  if(etype.name(1) != "TRUE"){
    return false;
  }
  return true;
}


} // namespace datatype
} // namespace hdf5
