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
// Created on: Sep 11, 2017
//

#include <h5cpp/node/group.hpp>
#include <h5cpp/error/error.hpp>
#include <h5cpp/node/group_view.hpp>


namespace hdf5 {
namespace node {

GroupView::GroupView(Group &parent_group):
    group_(parent_group)
{}

GroupView::~GroupView()
{}

size_t GroupView::size() const
{
  H5G_info_t info;
  if(H5Gget_info(static_cast<hid_t>(group()),&info)<0)
  {
    error::Singleton::instance().throw_with_stack("Could not access the group info data!");
  }
  return info.nlinks;
}

} // namespace node
} // namespace hdf5
