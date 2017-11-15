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
#include <h5cpp/core/object_id.hpp>
#include <vector>

namespace hdf5
{

std::string ObjectId::get_file_name(const ObjectHandle &handle)
{
  ssize_t size = H5Fget_name(static_cast<hid_t>(handle), NULL, 0);
  if(size<0)
  {
    throw std::runtime_error("Failure retrieving the size of the filename  string!");
  }

  //we have to add the space for the space for the \0 which will terminate the
  //string
  std::vector<char> buffer(size+1,'\0');

  //read the characters to the buffer
  if(H5Fget_name(static_cast<hid_t>(handle), buffer.data(), size+1)<0)
  {
    std::stringstream ss;
    ss<<"Failure to retrieve the name of the HDF5 file.";
    throw std::runtime_error(ss.str());
  }

  std::string fname(buffer.data());
  return fname;
}

ObjectId::ObjectId():
    file_num_{0},
    obj_addr_{0},
    file_name_{}
{}

ObjectId::ObjectId(const ObjectHandle &handle):
	file_num_{ 0 },
	obj_addr_{0},
	file_name_{}
{
	if (handle.is_valid())
	{
		H5O_info_t info;
		H5Oget_info(static_cast<hid_t>(handle), &info);
		file_num_ = info.fileno;
		obj_addr_ = info.addr;

		file_name_ = boost::filesystem::path(get_file_name(handle));
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

boost::filesystem::path ObjectId::file_name() const noexcept
{
  return file_name_;
}


}
