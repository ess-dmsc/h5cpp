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
// Created on: Aug 21, 2017
//

#include <stdexcept>
#include <h5cpp/property/link_creation_list.hpp>
#include <h5cpp/property/class.hpp>

namespace hdf5 {
namespace property {

LinkCreationList::LinkCreationList():
    StringCreationList(kLinkCreate)
{}

LinkCreationList::~LinkCreationList()
{}

void LinkCreationList::enable_intermediate_group_creation() const
{
  if(H5Pset_create_intermediate_group(static_cast<hid_t>(*this),1)<0)
  {
    throw std::runtime_error("Failure setting intermediate group creation "
        "flag to link creation property list!");
  }
}

void LinkCreationList::disable_intermediate_group_creation() const
{
  if(H5Pset_create_intermediate_group(static_cast<hid_t>(*this),-1)<0)
  {
    throw std::runtime_error("Failure deleting intermediate group creation "
        "flag on link creation property list!");
  }
}

bool LinkCreationList::intermediate_group_creation() const
{
  unsigned buffer = 0;
  if(H5Pget_create_intermediate_group(static_cast<hid_t>(*this),&buffer)<0)
  {
    std::runtime_error("Failure retrieving intermediate group creation flag "
        "from link creation property list!");
  }
  if(buffer>0)
    return true;
  else
    return false;
}

} // namespace property
} // namespace hdf5
