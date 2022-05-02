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
// Created on: Oct 23, 2017
//

#include <h5cpp/datatype/array.hpp>
#include <h5cpp/error/error.hpp>
#include <h5cpp/core/utilities.hpp>
#include <sstream>

namespace hdf5 {
namespace datatype {

Array::Array(ObjectHandle &&handle) :
    Datatype(std::move(handle)) {}

Array::Array(const Datatype &type) :
    Datatype(type) {
  if (get_class() != Class::Array) {
    std::stringstream ss;
    ss << "Cannot create Array from " << get_class();
    throw std::runtime_error(ss.str());
  }
}

Array Array::create(const Datatype &base_type, const Dimensions &dims) {
  hid_t ret = H5Tarray_create(static_cast<hid_t>(base_type), static_cast<unsigned int>(dims.size()), dims.data());
  if (ret < 0) {
    std::stringstream ss;
    ss << "Could not create Array of base=" << base_type.get_class();
    // print debug info on dims ???
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return Array(ObjectHandle(ret));
}

Dimensions Array::dimensions() const {
  size_t my_rank;
  try {
    my_rank = rank();
  }
  catch (...) {
    std::throw_with_nested(std::runtime_error("Could not obtain dimensions for Array datatype"));
  }

  Dimensions dims(my_rank);
  if (H5Tget_array_dims(static_cast<hid_t>(*this), dims.data()) < 0) {
    error::Singleton::instance().throw_with_stack("Could not obtain dimensions for Array datatype");
  }
  return dims;
}

size_t Array::rank() const {
  int ndims = H5Tget_array_ndims(static_cast<hid_t>(*this));
  if (ndims < 0) {
    error::Singleton::instance().throw_with_stack("Could not obtain rank for Array datatype!");
  }
  return signed2unsigned<size_t>(ndims);
}

VLengthArray::VLengthArray(ObjectHandle &&handle) :
    Datatype(std::move(handle)) {}

VLengthArray::VLengthArray(const Datatype &type) :
    Datatype(type) {
  if (get_class() != Class::VarLength) {
    std::stringstream ss;
    ss << "Cannot create VLengthArray from " << get_class();
    throw std::runtime_error(ss.str());
  }
}

VLengthArray VLengthArray::create(const Datatype &base_type) {
  hid_t ret = H5Tvlen_create(static_cast<hid_t>(base_type));
  if (ret < 0) {
    std::stringstream ss;
    ss << "Could not create VLengthArray of base=" << base_type.get_class();
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return VLengthArray(ObjectHandle(ret));
}

} // namespace datatype
} // namespace hdf5
