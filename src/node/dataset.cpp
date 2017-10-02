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
    ss<<"Failure retrieving dataspace for dataset "<<path()<<"!";
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
    ss<<"Failure retrieving datatype for dataset "<<path()<<"!";
    throw std::runtime_error(ss.str());
  }

  return datatype::Datatype(ObjectHandle(id));
}

void Dataset::extent(const Dimensions &dims) const
{
  if(H5Dset_extent(static_cast<hid_t>(*this),dims.data())<0)
  {
    std::stringstream ss;
    ss<<"Failed to set extent for dataset "<<path()<<"!";
    throw std::runtime_error(ss.str());
  }
}



} // namespace node
} // namespace hdf5
