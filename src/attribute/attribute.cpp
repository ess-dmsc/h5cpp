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
// Created on: Oct 4, 2017
//
#include <stdexcept>
#include <h5cpp/attribute/attribute.hpp>

namespace hdf5 {
namespace attribute {

Attribute::Attribute(ObjectHandle &&handle):
    handle_(std::move(handle))
{
}

datatype::Datatype Attribute::datatype() const
{
  ObjectHandle handle;
  try
  {
    handle = ObjectHandle(H5Aget_type(static_cast<hid_t>(handle_)));
  }
  catch(const std::runtime_error &)
  {
    throw std::runtime_error("Failure to obtain the datatype of an attribute!");
  }
  return datatype::Datatype(std::move(handle));

}

dataspace::Dataspace Attribute::dataspace() const
{
  ObjectHandle handle;
  try
  {
    handle = ObjectHandle(H5Aget_space(static_cast<hid_t>(handle_)));
  }
  catch(const std::runtime_error &)
  {
    throw std::runtime_error("Failure to obtain the dataspace of an attribute!");
  }

  return dataspace::Dataspace(std::move(handle));
}

std::string Attribute::name() const
{
  ssize_t size = H5Aget_name(static_cast<hid_t>(handle_),0,NULL);
  if(size<0)
  {
    throw std::runtime_error("Could not determine the size of the attributes name!");
  }

  std::string buffer(size+1,' ');
  char *ptr = const_cast<char*>(buffer.data());
  if(H5Aget_name(static_cast<hid_t>(handle_),size+1,ptr)<0)
  {
    throw std::runtime_error("Failure retrieving the attributes name!");
  }

  return buffer;
}

bool Attribute::is_valid() const
{
  return handle_.is_valid();
}

} // namespace attribute
} // namespace hdf5
