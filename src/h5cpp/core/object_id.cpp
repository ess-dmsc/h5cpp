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
// Author: Martin Shetty <martin.shetty@esss.se>
//
#include <h5cpp/core/object_id.hpp>
#include <h5cpp/core/utilities.hpp>
#include <h5cpp/error/error.hpp>
#include <vector>

namespace hdf5
{

std::string ObjectId::get_file_name(const ObjectHandle &handle)
{
  ssize_t size = H5Fget_name(static_cast<hid_t>(handle), nullptr, 0);
  if(size<0)
  {
    error::Singleton::instance().throw_with_stack("Failure retrieving the size of the filename  string!");
  }

  //we have to add the space for the space for the \0 which will terminate the
  //string
  std::vector<char> buffer(signed2unsigned<size_t>(size+1),'\0');

  //read the characters to the buffer
  if(H5Fget_name(static_cast<hid_t>(handle), buffer.data(), signed2unsigned<size_t>(size+1))<0)
  {
    error::Singleton::instance().throw_with_stack("Failure to retrieve the name of the HDF5 file.");
  }

  std::string fname(buffer.data());
  return fname;
}

H5O_info_t_ ObjectId::get_info(const ObjectHandle &handle)
{
  H5O_info_t_ info;
#if H5_VERSION_LE(1,10,2)
  if (0 > H5Oget_info(static_cast<hid_t>(handle), &info))
#else
  if (0 > H5Oget_info1(static_cast<hid_t>(handle), &info))
#endif
  {
    error::Singleton::instance().throw_with_stack("Could not get Object info.");
  }
  return info;
}

ObjectId::ObjectId(const ObjectHandle &handle)
{
  if (handle.is_valid())
  {
    try
    {
      auto info = get_info(handle);
      file_num_ = info.fileno;
      obj_addr_ = info.addr;
      file_name_ = fs::path(get_file_name(handle));
    }
    catch (...)
    {
      std::stringstream ss;
      ss << "ObjectID: construct from handle = " << static_cast<hid_t>(handle);
      std::throw_with_nested(std::runtime_error(ss.str()));
    }
  }
}

std::ostream & operator<<(std::ostream &os, const ObjectId& p)
{
  os << p.file_num_ << ":" << p.obj_addr_;
#ifdef H5CPP_OBJECTID_USE_FILENAME
  os << " \"" << p.file_name_ << "\"";
#endif
  return os;
}

bool ObjectId::operator== (const ObjectId& other) const
{
  return (
      #ifdef H5CPP_OBJECTID_USE_FILENAME
        (file_name_ == other.file_name_) &&
      #endif
        (file_num_ == other.file_num_) &&
        (obj_addr_ == other.obj_addr_)
        );
}

bool ObjectId::operator!= (const ObjectId &other) const
{
  return !(*this == other);
}

bool ObjectId::operator< (const ObjectId& other) const
{
  if (file_num_ < other.file_num_)
    return true;
#ifdef H5CPP_OBJECTID_USE_FILENAME
  if ((file_num_ == other.file_num_) && (file_name_ < other.file_name_))
    return true;
  if ((file_num_ == other.file_num_) &&
      (file_name_ == other.file_name_) &&
      (obj_addr_ < other.obj_addr_))
    return true;
#else
  if ((file_num_ == other.file_num_) && (obj_addr_ < other.obj_addr_))
    return true;
#endif
  return false;
}

unsigned long ObjectId::file_number() const noexcept
{
  return file_num_;
}

haddr_t ObjectId::object_address() const noexcept
{
  return obj_addr_;
}

fs::path ObjectId::file_name() const noexcept
{
  return file_name_;
}


}
