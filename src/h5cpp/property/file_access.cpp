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
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 17, 2017
//

#include <h5cpp/property/file_access.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5 {
namespace property {

std::ostream &operator<<(std::ostream &stream, const LibVersion &version) {
  switch (version) {
    case LibVersion::EARLIEST: return stream << "EARLIEST";
    case LibVersion::LATEST: return stream << "LATEST";
    default:return stream;
  }
}

FileAccessList::FileAccessList() :
    List(kFileAccess) {}

FileAccessList::~FileAccessList() {}

FileAccessList::FileAccessList(ObjectHandle &&handle) :
    List(std::move(handle)) {
  if (get_class() != kFileAccess) {
    std::stringstream ss;
    ss << "Cannot create property::FileAccessList from " << get_class();
    throw std::runtime_error(ss.str());
  }
}

void FileAccessList::library_version_bounds(LibVersion high, LibVersion low) const {
  if (0 > H5Pset_libver_bounds(static_cast<hid_t>(*this),
                               static_cast<H5F_libver_t>(high),
                               static_cast<H5F_libver_t>(low))) {
    error::Singleton::instance().throw_with_stack("Failure setting the library version bounds!");
  }
}

LibVersion FileAccessList::library_version_bound_high() const {
  H5F_libver_t high, low;

  if (0 > H5Pget_libver_bounds(static_cast<hid_t>(*this), &low, &high)) {
    error::Singleton::instance().throw_with_stack("Failure retrieving library version bounds!");
  }

  return static_cast<LibVersion>(high);
}

LibVersion FileAccessList::library_version_bound_low() const {
  H5F_libver_t high, low;

  if (0 > H5Pget_libver_bounds(static_cast<hid_t>(*this), &low, &high)) {
    error::Singleton::instance().throw_with_stack("Failure retrieving library version bounds!");
  }

  return static_cast<LibVersion>(low);
}

void FileAccessList::driver(const file::Driver &file_driver) const {
  file_driver(*this);
}

} // namespace property
} // namespace hdf5
