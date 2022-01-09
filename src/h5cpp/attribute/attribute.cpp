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
//   Jan Kotanski <jan.kotanski@desy.de>
//
// Created on: Oct 4, 2017
//
#include <h5cpp/attribute/attribute.hpp>
#include <h5cpp/core/utilities.hpp>
#include <h5cpp/node/link.hpp>

namespace hdf5 {
namespace attribute {

Attribute::Attribute(ObjectHandle &&handle,const node::Link &parent_link):
    handle_(std::move(handle)),
    parent_link_(parent_link)
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
    std::throw_with_nested(std::runtime_error("Failure to obtain the datatype of an attribute!"));
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
    std::throw_with_nested(std::runtime_error("Failure to obtain the dataspace of an attribute!"));
  }

  return dataspace::Dataspace(std::move(handle));
}

std::string Attribute::name() const
{
  ssize_t ssize = H5Aget_name(static_cast<hid_t>(handle_),0,nullptr);
  if(ssize<0)
  {
    error::Singleton::instance().throw_with_stack("Could not determine the size of the attributes name!");
  }

  std::string buffer(signed2unsigned<size_t>(ssize),' ');
  char *ptr = const_cast<char*>(buffer.data());
  if(H5Aget_name(static_cast<hid_t>(handle_),signed2unsigned<size_t>(ssize+1),ptr)<0)
  {
    error::Singleton::instance().throw_with_stack("Failure retrieving the attributes name!");
  }

  return buffer;
}

bool Attribute::is_valid() const
{
  return handle_.is_valid();
}

const node::Link &Attribute::parent_link() const noexcept
{
  return parent_link_;
}

void Attribute::write(const char *data) const
{
  write(std::string(data));
}

void Attribute::write(const char *data,const datatype::Datatype &mem_type) const
{
  write(std::string(data),mem_type);
}

void Attribute::check_size(const dataspace::Dataspace &mem_space,
                           const dataspace::Dataspace &file_space,
                           const std::string &operation) const
{
  if(file_space.size()!=mem_space.size())
  {
    std::stringstream ss;
    ss<<"Size mismatch in attribute "<<operation<<": "<<mem_space.size()
      <<" elements in memory, "<<file_space.size()
      <<" on disk!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

void Attribute::close()
{
  handle_.close();
  parent_link_ = hdf5::node::Link();
}



} // namespace attribute
} // namespace hdf5
