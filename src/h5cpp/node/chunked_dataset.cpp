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
// Created on: Nov 17, 2017
//

#include <h5cpp/node/chunked_dataset.hpp>

namespace hdf5 {
namespace node {


ChunkedDataset::ChunkedDataset(const Group &base,const Path &path,
                               const datatype::Datatype &type,
                               const dataspace::Simple &space,
                               const Dimensions &chunk_shape,
                               const property::LinkCreationList &lcpl,
                               const property::DatasetCreationList &dcpl,
                               const property::DatasetAccessList &dapl):
                                   Dataset()
{
  //create a local copy for the dataset creation property list
  property::DatasetCreationList local_dcpl(dcpl);
  local_dcpl.layout(property::DatasetLayout::Chunked);
  local_dcpl.chunk(chunk_shape);

  Dataset::operator=(Dataset(base,path,type,space,lcpl,local_dcpl,dapl));
}

} // namespace node
} // namespace hdf5
