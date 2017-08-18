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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 16, 2017
//

#include <stdexcept>

#include <h5cpp/property/file_creation_list.hpp>

namespace hdf5 {
namespace property{

FileCreationList::FileCreationList():
    GroupCreationList(kFileCreate)
{
}

hsize_t FileCreationList::userblock() const
{
  hsize_t buffer;
  if(H5Pget_userblock(static_cast<hid_t>(*this),&buffer)<0)
  {
    throw std::runtime_error("Cannot retrieve user block size from file creation property list!");
  }
  return buffer;
}

void FileCreationList::userblock(hsize_t size) const
{
  if(H5Pset_userblock(static_cast<hid_t>(*this),size)<0)
  {
    throw std::runtime_error("Cannot set user block size for file creation property list!");
  }
}

void FileCreationList::object_offset_size(size_t size) const
{
  if(H5Pset_sizes(static_cast<hid_t>(*this),size,object_length_size())<0)
  {
    throw std::runtime_error("Failure setting object offset size to file creation property list!");
  }
}

size_t FileCreationList::object_offset_size() const
{
  size_t offset_size = 0,
         length_size = 0;

  if(H5Pget_sizes(static_cast<hid_t>(*this),&offset_size,&length_size)<0)
  {
    throw std::runtime_error("Failure retrieving object offset size from file creation property list!");
  }

  return offset_size;
}

void FileCreationList::object_length_size(size_t size) const
{
  if(H5Pset_sizes(static_cast<hid_t>(*this),object_offset_size(),size)<0)
  {
    throw std::runtime_error("Failure setting object length size in file creation property list!");
  }
}

size_t FileCreationList::object_length_size() const
{
  size_t offset_size = 0,
         length_size = 0;

  if(H5Pget_sizes(static_cast<hid_t>(*this),&offset_size,&length_size)<0)
  {
    throw std::runtime_error("Failure retrieving object length size from file creation property list!");
  }

  return length_size;
}

} // namespace property
} // namespace hdf5
