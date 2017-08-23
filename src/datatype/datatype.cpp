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
// Created on: Aug 15, 2017
//

#include <stdexcept>
#include <h5cpp/datatype/datatype.hpp>


namespace hdf5 {
namespace datatype {

Datatype::Datatype(ObjectHandle &&handle):
    handle_(std::move(handle))
{}

Datatype::~Datatype()
{}

Class Datatype::get_class() const
{
  switch(H5Tget_class(static_cast<hid_t>(*this)))
  {
    case H5T_INTEGER:
      return Class::INTEGER;
    case H5T_FLOAT:
      return Class::FLOAT;
    case H5T_STRING:
      return Class::STRING;
    case H5T_BITFIELD:
      return Class::BITFIELD;
    case H5T_OPAQUE:
      return Class::OPAQUE;
    case H5T_COMPOUND:
      return Class::COMPOUND;
    case H5T_REFERENCE:
      return Class::REFERENCE;
    case H5T_ENUM:
      return Class::ENUM;
    case H5T_VLEN:
      return Class::VARLENGTH;
    case H5T_ARRAY:
      return Class::ARRAY;
    default:
      throw std::runtime_error("unkown data type class");
  }
}

Datatype Datatype::super() const
{
  hid_t id = H5Tget_super(static_cast<hid_t>(*this));
  if(id<0)
  {
    throw std::runtime_error("Failure retrieving the base data type!");
  }
  return Datatype(ObjectHandle(id));
}

Datatype Datatype::native_type(Direction dir) const
{
  hid_t id = H5Tget_native_type(static_cast<hid_t>(*this),
                                static_cast<H5T_direction_t>(dir));
  if(id<0)
  {
    throw std::runtime_error("Failure retrieving the native type!");
  }
  return Datatype(ObjectHandle(id));
}

bool Datatype::has_class(Class type_class) const
{
  htri_t result = H5Tdetect_class(static_cast<hid_t>(*this),
                                  static_cast<H5T_class_t>(type_class));
  if(result<0)
  {
    throw std::runtime_error("Failure searching for type class!");
  }

  if(result>0)
    return true;
  else
    return false;
}

size_t Datatype::size() const
{
  size_t s = H5Tget_size(static_cast<hid_t>(*this));
  if(s==0)
  {
    throw std::runtime_error("Failure to retrieve the datatype size!");
  }
  return s;
}

void Datatype::size(size_t size) const
{
  if(H5Tset_size(static_cast<hid_t>(*this),size)<0)
  {
    throw std::runtime_error("Failure to set the datatype size!");
  }
}



} // namespace datatype
} // namespace hdf5
