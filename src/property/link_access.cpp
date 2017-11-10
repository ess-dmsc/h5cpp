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

#include <h5cpp/property/link_access.hpp>
#include <h5cpp/property/property_class.hpp>


namespace hdf5 {
namespace property {

LinkAccessList::LinkAccessList():
    List(kLinkAccess),
    elink_prefix_()
{}

LinkAccessList::LinkAccessList(const Class &plist_class):
    List(plist_class),
    elink_prefix_()
{}

LinkAccessList::~LinkAccessList()
{}

size_t LinkAccessList::maximum_link_traversals() const
{
  size_t buffer = 0;
  if(H5Pget_nlinks(static_cast<hid_t>(*this),&buffer)<0)
  {
    std::runtime_error("Failure retrieving the maximum number of link traversals!");
  }
  return buffer;
}

void LinkAccessList::maximum_link_traversals(size_t size) const
{
  if(H5Pset_nlinks(static_cast<hid_t>(*this),size)<0)
  {
    std::runtime_error("Failure setting the maximum number of link traversals!");
  }
}

boost::filesystem::path LinkAccessList::external_link_prefix() const
{
  return elink_prefix_;
}

void LinkAccessList::external_link_prefix(const boost::filesystem::path &path)
{
  std::string old_prefix = elink_prefix_;
  elink_prefix_ = path.string();
  if(H5Pset_elink_prefix(static_cast<hid_t>(*this),elink_prefix_.c_str())<0)
  {
    elink_prefix_ = old_prefix;
    std::runtime_error("Failure setting the external link prefix to ["+path.string()+"]");
  }
}


} // namespace property
} // namespace hdf5
