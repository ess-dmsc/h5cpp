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
// Created on: Sep 12, 2017
//

#include <sstream>
#include <stdexcept>
#include <h5cpp/node/dataset.hpp>

namespace hdf5 {
namespace node {

Dataset::Dataset(const Node &node):
    Node(node)
{}

dataspace::Dataspace Dataset::dataspace() const
{
  hid_t id = H5Dget_space(static_cast<hid_t>(*this));
  if(id<0)
  {
    std::stringstream ss;
    ss<<"Failure retrieving dataspace for dataset "<<link().path()<<"!";
    throw std::runtime_error(ss.str());
  }
  return dataspace::Dataspace(ObjectHandle(id));
}

datatype::Datatype Dataset::datatype() const
{
  hid_t id = H5Dget_type(static_cast<hid_t>(*this));
  if(id<0)
  {
    std::stringstream ss;
    ss<<"Failure retrieving datatype for dataset "<<link().path()<<"!";
    throw std::runtime_error(ss.str());
  }

  return datatype::Datatype(ObjectHandle(id));
}

void Dataset::extent(const Dimensions &dims) const
{
  if(H5Dset_extent(static_cast<hid_t>(*this),dims.data())<0)
  {
    std::stringstream ss;
    ss<<"Failed to set extent for dataset "<<link().path()<<"!";
    throw std::runtime_error(ss.str());
  }
}

void Dataset::extent(size_t dim,ssize_t delta_elements) const
{
  dataspace::Dataspace space = dataspace();
  if(space.type()!=dataspace::Type::SIMPLE)
  {
    std::stringstream ss;
    ss<<"Dataset ["<<link().path()<<"] does not use a simple dataspace"
      <<" and thus cannot be extended!";
    throw std::runtime_error(ss.str());
  }
  dataspace::Simple simple_space(space);

  Dimensions current_dims = simple_space.current_dimensions();
  //check current dimensions
  if(dim>=current_dims.size())
  {
    std::stringstream ss;
    ss<<"Dataset ["<<link().path()<<"] has rank "<<current_dims.size()
      <<" however you requested to change dimension "<<dim
      <<" this would not work!";
    throw std::runtime_error(ss.str());
  }

  if((delta_elements<0) && (current_dims[dim]<abs(delta_elements)))
  {
    std::stringstream ss;
    ss<<"Extent of dataset ["<<link().path()<<"] cannot be changed "
      <<" by "<<delta_elements<<" along dimensions "<<dim
      <<" (currently "<<current_dims[dim]<<") as the resulting size"
      <<" would be negative";
    throw std::runtime_error(ss.str());
  }

  current_dims[dim] += delta_elements;
  extent(current_dims);
}

#if H5_VERSION_GE(1,10,0)
void Dataset::refresh() const
{
  if(H5Drefresh(static_cast<hid_t>(*this))<0)
  {
    std::stringstream ss;
    ss<<"Failure to refresh dataset ["<<link().path()<<"]!";
    std::runtime_error(ss.str());
  }
}

#endif



} // namespace node
} // namespace hdf5
