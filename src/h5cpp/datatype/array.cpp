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
// Created on: Oct 23, 2017
//

#include <h5cpp/datatype/array.hpp>
#include <h5cpp/error/error.hpp>

namespace hdf5 {
namespace datatype {

Array::Array():Datatype()
{}

Array::Array(const Datatype &base_type,const Dimensions &dims):
    Datatype(ObjectHandle(H5Tarray_create(static_cast<hid_t>(base_type),
                                          dims.size(),dims.data())))
{}

Dimensions Array::dimensions() const
{
  Dimensions dims(rank());

  if(H5Tget_array_dims(static_cast<hid_t>(*this),dims.data())<0)
  {
    error::Singleton::instance().throw_with_stack("Cannot obtain dimensions for Array datatype!");
  }

  return dims;

}

size_t Array::rank() const
{
  int ndims = H5Tget_array_ndims(static_cast<hid_t>(*this));
  if(ndims<0)
  {
    error::Singleton::instance().throw_with_stack("Cannot obtain rank for array datatype!");
  }

  return ndims;
}

VLengthArray::VLengthArray():Datatype()
{}

VLengthArray::VLengthArray(const Datatype &base_type):
    Datatype(ObjectHandle(H5Tvlen_create(static_cast<hid_t>(base_type))))
{}


} // namespace datatype
} // namespace hdf5
