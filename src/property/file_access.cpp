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
// Created on: Aug 17, 2017
//

#include <h5cpp/property/file_access_list.hpp>
#include <h5cpp/property/class.hpp>

namespace hdf5 {
namespace property {


std::ostream &operator<<(std::ostream &stream,const LibVersion &version)
{
  switch(version)
  {
    case LibVersion::EARLIEST: return stream<<"EARLIEST";
    case LibVersion::LATEST: return stream<<"LATEST";
    default:
      return stream;
  }
}

FileAccessList::FileAccessList():
    List(kFileAccess)
{}

FileAccessList::~FileAccessList()
{}


void FileAccessList::library_version_bounds(LibVersion high,LibVersion low) const
{
  if(H5Pset_libver_bounds(static_cast<hid_t>(*this),
                          static_cast<H5F_libver_t>(high),
                          static_cast<H5F_libver_t>(low))<0)
  {
    throw std::runtime_error("Failure setting the library version bounds!");
  }
}

LibVersion FileAccessList::library_version_bound_high() const
{
  H5F_libver_t high,low;

  if(H5Pget_libver_bounds(static_cast<hid_t>(*this),&high,&low)<0)
  {
    throw std::runtime_error("Failure retrieving library version bounds!");
  }

  return static_cast<LibVersion>(high);
}

LibVersion FileAccessList::library_version_bound_low() const
{
  H5F_libver_t high,low;

  if(H5Pget_libver_bounds(static_cast<hid_t>(*this),&high,&low)<0)
  {
    throw std::runtime_error("Failure retrieving library version bounds!");
  }

  return static_cast<LibVersion>(low);
}

} // namespace property
} // namespace hdf5
