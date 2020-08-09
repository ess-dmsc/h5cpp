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
// Created on: Nov 10, 2017
//

#include <h5cpp/property/virtual_data_map.hpp>
#include <h5cpp/error/error.hpp>

namespace hdf5 {
namespace property {

#if H5_VERSION_GE(1, 10, 0)

VirtualDataMap::VirtualDataMap(const dataspace::View &target_view,
                               const fs::path &source_file,
                               const hdf5::Path &source_dataset,
                               const dataspace::View &source_view) :
    target_view_(target_view),
    source_file_(source_file),
    source_dataset_(source_dataset),
    source_view_(source_view) {}

void VirtualDataMap::operator()(const property::DatasetCreationList &dcpl) const {
  if (H5Pset_virtual(static_cast<hid_t>(dcpl),
                     static_cast<hid_t>(target_view_),
                     source_file_.string().c_str(),
                     static_cast<std::string>(source_dataset_).c_str(),
                     static_cast<hid_t>(source_view_)) < 0) {
    error::Singleton::instance().throw_with_stack("Failure to apply virtual data mapping!");
  }
}

#endif

} // namespace property
} // namespace hdf5
