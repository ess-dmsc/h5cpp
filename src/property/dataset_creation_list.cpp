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
// Created on: Aug 25, 2017
//
#include <stdexcept>
#include <h5cpp/property/class.hpp>
#include <h5cpp/property/dataset_creation_list.hpp>
#include <h5cpp/types.hpp>

namespace hdf5 {
namespace property {

DatasetCreationList::DatasetCreationList():
    ObjectCreationList(kDatasetCreate)
{}

DatasetCreationList::~DatasetCreationList()
{}

void DatasetCreationList::layout(Layout layout) const
{
  if(H5Pset_layout(static_cast<hid_t>(*this),static_cast<H5D_layout_t>(layout))<0)
  {
    throw std::runtime_error("Failure setting the dataset layout!");
  }
}

DatasetCreationList::Layout DatasetCreationList::layout() const
{
  switch(H5Pget_layout)
  {
    case H5D_COMPACT:
      return Layout::COMPACT;
    case H5D_CONTIGUOUS:
      return Layout::CONTIGUOUS;
    case H5D_CHUNKED:
      return Layout::CHUNKED;
#if H5_VERSION_GE(1,10,0)
    case H5D_VIRTUAL:
      return Layout::VIRTUAL;
#endif
    default:
      throw std::runtime_error("Failure retrieving the dataset layout!");
  }
}

void DatasetCreationList::chunk(const Dimensions &chunk_dims) const
{
  if(H5Pset_chunk(static_cast<hid_t>(*this),chunk_dims.size(),chunk_dims.data())<0)
  {
    throw std::runtime_error("Failure setting chunk dimensions!");
  }
}

Dimensions DatasetCreationList::chunk() const
{
  int s = H5Pget_chunk(static_cast<hid_t>(*this),0,NULL);
  if(s<0)
  {
    throw std::runtime_error("Failure retrieving the chunk rank!");
  }

  Dimensions buffer(s);
  if(H5Pget_chunk(static_cast<hid_t>(*this),s,buffer.data())<0)
  {
    throw std::runtime_error("Failure retrieving the chunk dimension!");
  }

  return buffer;
}


} // namespace property
} // namespace hdf5
