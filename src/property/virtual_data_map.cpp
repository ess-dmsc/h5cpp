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
// Created on: Nov 10, 2017
//

#include <h5cpp/property/virtual_data_map.hpp>

namespace hdf5 {
namespace property {

VirtualDataMap::VirtualDataMap(const dataspace::Dataspace &target_space,
                               const boost::filesystem::path &source_file,
                               const hdf5::Path &source_dataset,
                               const dataspace::Dataspace &source_space):
    target_space_(target_space),
    source_file_(source_file),
    source_dataset_(source_dataset),
    source_space_(source_space)
{}

void VirtualDataMap::operator()(const property::DatasetCreationList &dcpl) const
{
  if(H5Pset_virtual(static_cast<hid_t>(dcpl),
                    static_cast<hid_t>(target_space_),
                    source_file_.string().c_str(),
                    static_cast<std::string>(source_dataset_).c_str(),
                    static_cast<hid_t>(source_space_))<0)
  {
    throw std::runtime_error("Failure to apply virtual data mapping!");
  }
}

} // namespace property
} // namespace hdf5
