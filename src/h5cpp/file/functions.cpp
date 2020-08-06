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
// Authors: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Sep 9, 2017
//
#include <sstream>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/error/error.hpp>

namespace hdf5 {
namespace file {

File create(const fs::path &path, AccessFlags flags,
            const property::FileCreationList &fcpl, const property::FileAccessList &fapl)
{
  return create(path, static_cast<AccessFlagsBase>(flags), fcpl, fapl);
}

File create(const fs::path &path, AccessFlagsBase flags,
            const property::FileCreationList &fcpl, const property::FileAccessList &fapl)
{
  hid_t fid = H5Fcreate(path.string().c_str(), flags,
                        static_cast<hid_t>(fcpl), static_cast<hid_t>(fapl));
  if (fid < 0)
  {
    std::stringstream ss;
    ss << "Failure creating file [" << path << "]";
    error::Singleton::instance().throw_with_stack(ss.str());
  }

  return File(hdf5::ObjectHandle(fid));
}

File open(const fs::path &path, AccessFlags flags,
          const property::FileAccessList &fapl)
{
  return open(path, static_cast<AccessFlagsBase>(flags), fapl);
}

File open(const fs::path &path, AccessFlagsBase flags,
          const property::FileAccessList &fapl)
{
  hid_t fid = H5Fopen(path.string().c_str(), flags, static_cast<hid_t>(fapl));
  if (fid < 0)
  {
    std::stringstream ss;
    ss << "Failure opening file [" << path << "]";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return File(ObjectHandle(fid));
}

bool is_hdf5_file(const fs::path &path)
{
  htri_t result = H5Fis_hdf5(path.string().c_str());
  if (result < 0)
  {
    std::stringstream ss;
    ss << "Failure to determine whether " << path.string() << "is an HDF5 file or not!";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return (result != 0);
}

} // namespace file
} // namespace hdf5
