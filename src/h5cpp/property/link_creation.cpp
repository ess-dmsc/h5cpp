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
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 21, 2017
//

#include <h5cpp/property/link_creation.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5 {
namespace property {

LinkCreationList::LinkCreationList() :
    StringCreationList(kLinkCreate) {}

LinkCreationList::~LinkCreationList() {}

LinkCreationList::LinkCreationList(ObjectHandle &&handle) :
    StringCreationList(std::move(handle)) {
  if (get_class() != kLinkCreate) {
    std::stringstream ss;
    ss << "Cannot create property::LinkCreationList from " << get_class();
    throw std::runtime_error(ss.str());
  }
}

void LinkCreationList::enable_intermediate_group_creation() const {
  if (H5Pset_create_intermediate_group(static_cast<hid_t>(*this), 1) < 0) {
    error::Singleton::instance().throw_with_stack("Failure setting intermediate group creation "
                                                      "flag to link creation property list!");
  }
}

void LinkCreationList::disable_intermediate_group_creation() const {
  if (H5Pset_create_intermediate_group(static_cast<hid_t>(*this), 0) < 0) {
    error::Singleton::instance().throw_with_stack("Failure deleting intermediate group creation "
                                                      "flag on link creation property list!");
  }
}

bool LinkCreationList::intermediate_group_creation() const {
  unsigned buffer = 0;
  if (H5Pget_create_intermediate_group(static_cast<hid_t>(*this), &buffer) < 0) {
    error::Singleton::instance().throw_with_stack("Failure retrieving intermediate group creation flag "
                                                      "from link creation property list!");
  }
  if (buffer != 0)
    return true;
  else
    return false;
}

} // namespace property
} // namespace hdf5
