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

Datatype::~Datatype()
{
}

Datatype::Datatype(ObjectHandle &&handle):
    handle_(std::move(handle))
{}

Datatype::Datatype(const Datatype &type)
{
  hid_t ret = H5Tcopy(static_cast<hid_t>(type.handle_));
  if (0 > ret)
  {
    throw std::runtime_error("could not copy-construct Datatype");
  }
  handle_ = ObjectHandle(ret);
}

Datatype& Datatype::operator=(const Datatype &type)
{
  hid_t ret = H5Tcopy(static_cast<hid_t>(type.handle_));
  if (0 > ret)
  {
    throw std::runtime_error("could not copy Datatype");
  }
  handle_ = ObjectHandle(ret);
  return *this;
}

Class Datatype::get_class() const
{
  return static_cast<Class>(H5Tget_class(static_cast<hid_t>(*this)));
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

void Datatype::set_size(size_t size) const
{
  if(H5Tset_size(static_cast<hid_t>(*this),size)<0)
  {
    throw std::runtime_error("Failure to set the datatype size!");
  }
}

bool Datatype::is_valid() const
{
  return handle_.is_valid();
}

bool operator==(const Datatype &lhs,const Datatype &rhs)
{
  htri_t ret = H5Tequal(static_cast<hid_t>(lhs), static_cast<hid_t>(rhs));
  if (0 > ret)
  {
    throw std::runtime_error("Failure to compare datatypes!");
  }
  return (ret > 0);
}

bool operator!=(const Datatype &lhs,const Datatype &rhs)
{
  return !operator ==(lhs, rhs);
}



} // namespace datatype
} // namespace hdf5
