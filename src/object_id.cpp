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
// Author: Martin Shetty <martin.shetty@esss.se>
//
#include <h5cpp/object_id.hpp>
#include <vector>

namespace hdf5
{

ObjectId::ObjectId()
{}

ObjectId::ObjectId(hid_t object)
{
  ssize_t size = H5Fget_name(object, NULL, 0);
  std::vector<char> namec(size + 2, '\0');
  size = H5Fget_name(object, namec.data(), size);
  file_name_ = std::string(namec.data());

  H5O_info_t info;
  H5Oget_info(object, &info);
  file_num_ = info.fileno;
  obj_addr_ = info.addr;
}

std::ostream & operator<<(std::ostream &os, const ObjectId& p)
{
  os << p.file_num_ << ":" << p.obj_addr_
     << " \"" << p.file_name_ << "\"";
  return os;
}

bool ObjectId::operator== (const ObjectId& other) const
{
  return (
        (file_name_ == other.file_name_) &&
//        (file_num_ == other.file_num_) &&
        (obj_addr_ == other.obj_addr_)
        );
}

bool ObjectId::operator!= (const ObjectId &other) const
{
  return !(*this == other);
}

bool ObjectId::operator< (const ObjectId& other) const
{
  return (
        (file_name_ < other.file_name_) &&
//        (file_num_ < other.file_num_) &&
        (obj_addr_ < other.obj_addr_)
        );
}

std::string ObjectId::file_name() const
{
  return file_name_;
}

unsigned long ObjectId::file_number() const
{
  return file_num_;
}

haddr_t ObjectId::object_address() const
{
  return obj_addr_;
}


}
