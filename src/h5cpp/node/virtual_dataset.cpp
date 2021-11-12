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
// Created on: Nov 16, 2017
//

#include <h5cpp/node/dataset.hpp>
#if H5_VERSION_GE(1,10,0)

#include <h5cpp/node/virtual_dataset.hpp>
#include <algorithm>

namespace hdf5 {
namespace node {

VirtualDataset::VirtualDataset(const Group &base,const Path &path,
                               const datatype::Datatype &type,
                               const dataspace::Dataspace &space,
                               const property::VirtualDataMaps &vds_maps,
                               const property::LinkCreationList &lcpl,
                               const property::DatasetCreationList &dcpl,
                               const property::DatasetAccessList &dapl):
                                   Dataset()
{
  //ensure that the dataspace layout is virtual
  dcpl.layout(property::DatasetLayout::Virtual);

  // apply the maps to the datset creation list
  std::for_each(vds_maps.begin(),vds_maps.end(),
                [&dcpl](const property::VirtualDataMap &map) {map(dcpl);});

  Dataset::operator=(Dataset(base,path,type,space,lcpl,dcpl,dapl));
}

} // namespace node
} // namespace hdf5
#endif
