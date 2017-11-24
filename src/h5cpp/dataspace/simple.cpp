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
// Created on: Aug 24, 2017
//
#include <h5cpp/dataspace/simple.hpp>
#include <h5cpp/error/error.hpp>

namespace hdf5 {
namespace dataspace {

Simple::Simple():
    Dataspace(Type::SIMPLE)
{}

Simple::Simple(const Dataspace &space):
    Dataspace(space)
{
  if(space.type()!=Type::SIMPLE)
  {
    error::Singleton::instance().throw_with_stack("Failed to construct a simple dataspace from this!");
  }
}

Simple::Simple(const Dimensions &current,const Dimensions &maximum):
    Dataspace(Type::SIMPLE)
{
  dimensions(current,maximum);
}

int Simple::rank() const
{
  int rank = H5Sget_simple_extent_ndims(static_cast<hid_t>(*this));
  if(rank < 0)
  {
    error::Singleton::instance().throw_with_stack("Failure retrieving the rank of a simple dataspace!");
  }
  return rank;
}

void Simple::dimensions(const Dimensions &current,const Dimensions &maximum)
{
  const hsize_t *current_ptr = current.data(),
                *maximum_ptr = maximum.data();
  if(maximum.empty())
    maximum_ptr = current.data();

  if(H5Sset_extent_simple(static_cast<hid_t>(*this),current.size(),current_ptr,
                          maximum_ptr)<0)
  {
    error::Singleton::instance().throw_with_stack("Failure setting the dimensions for a simple dataspace!");
  }
}

Dimensions Simple::current_dimensions() const
{
  Dimensions dims(rank());
  if(H5Sget_simple_extent_dims(static_cast<hid_t>(*this),dims.data(),NULL)<0)
  {
    error::Singleton::instance().throw_with_stack("Failure retrieving the current dimensions!");
  }
  return dims;
}

Dimensions Simple::maximum_dimensions() const
{
  Dimensions dims(rank());
  if(H5Sget_simple_extent_dims(static_cast<hid_t>(*this),NULL,dims.data())<0)
  {
    error::Singleton::instance().throw_with_stack("Failure retrieving the maximum dimensions!");
  }
  return dims;
}



} // namespace dataspace
} // namespace hdf5
