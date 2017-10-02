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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Sep 9, 2017
//
#include <sstream>
#include <h5cpp/file/functions.hpp>

namespace hdf5 {
namespace file {

File create(const boost::filesystem::path &path, AccessFlags flags,
            const property::FileCreationList &fcpl, const property::FileAccessList &fapl)
{
  return create(path, static_cast<AccessFlagsBase>(flags), fcpl, fapl);
}

File create(const boost::filesystem::path &path, AccessFlagsBase flags,
            const property::FileCreationList &fcpl, const property::FileAccessList &fapl)
{
  return File(hdf5::ObjectHandle(
          H5Fcreate(path.string().c_str(), flags,
                    static_cast<hid_t>(fcpl), static_cast<hid_t>(fapl))
                  ));
}


File open(const boost::filesystem::path &path, AccessFlags flags,
          const property::FileAccessList &fapl)
{
  return open(path, static_cast<AccessFlagsBase>(flags), fapl);
}

File open(const boost::filesystem::path &path, AccessFlagsBase flags,
          const property::FileAccessList &fapl)
{
  return File(ObjectHandle(
      H5Fopen(path.string().c_str(), flags, static_cast<hid_t>(fapl))
  ));
}

bool is_hdf5_file(const boost::filesystem::path &path)
{
  htri_t result = H5Fis_hdf5(path.string().c_str());
  if(result>0)
  {
    return true;
  }
  else if(result==0)
  {
    return false;
  }
  else
  {
    std::stringstream ss;
    ss<<"Failure to determine whether "<<path.string()<<"is an HDF5 file or not!";
    throw std::runtime_error(ss.str());
  }
}

} // namespace file


namespace node {

void copy(const Node &source_parent, const Path &obj, const Group &target_base, const Path &rel_path)
{
  H5Ocopy(static_cast<hid_t>(source_parent), static_cast<std::string>(obj).c_str(),
          static_cast<hid_t>(target_base), static_cast<std::string>(rel_path).c_str(),
          0, 0);
}

void copy(const Node &source, const Group& base, const Path &rel_path)
{
//  auto f = source
//  auto parent = Path::parent_path(source.path());
  auto name = source.path().back();
  H5Ocopy(static_cast<hid_t>(source), name.c_str(),
          static_cast<hid_t>(base), static_cast<std::string>(rel_path).c_str(),
          0, 0);
}

void copy(const Node &source, const Group& destination)
{
  Path name(source.path().back());
  copy(source, destination, name);
}

} // namespace node


} // namespace hdf5




