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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Aug 17, 2017
//

#include <h5cpp/property/file_access.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5 {
namespace property {

std::ostream &operator<<(std::ostream &stream, const LibVersion &version) {
  switch (version) {
    case LibVersion::Earliest: return stream << "EARLIEST";
    case LibVersion::Latest: return stream << "LATEST";
  }
  return stream;
}

std::ostream &operator<<(std::ostream &stream, const CloseDegree &version) {
  switch (version) {
    case CloseDegree::Weak: return stream << "WEAK";
    case CloseDegree::Semi: return stream << "SEMI";
    case CloseDegree::Strong: return stream << "STRONG";
    case CloseDegree::Default: return stream << "DEFAULT";
  }
  return stream;
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

void FileAccessList::library_version_bounds(LibVersion low, LibVersion high) const {
  if (0 > H5Pset_libver_bounds(static_cast<hid_t>(*this),
                               static_cast<H5F_libver_t>(low),
                               static_cast<H5F_libver_t>(high))) {
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

void FileAccessList::close_degree(CloseDegree degree) const {
  if (0 > H5Pset_fclose_degree(static_cast<hid_t>(*this),
                               static_cast<H5F_close_degree_t>(degree))) {
    error::Singleton::instance().throw_with_stack("Failure setting the file close degree!");
  }
}

CloseDegree FileAccessList::close_degree() const {
  H5F_close_degree_t degree;

  if (0 > H5Pget_fclose_degree(static_cast<hid_t>(*this), &degree)) {
    error::Singleton::instance().throw_with_stack("Failure retrieving the file close degree!");
  }

  return static_cast<CloseDegree>(degree);
}

void FileAccessList::driver(const file::Driver &file_driver) const {
  file_driver(*this);
}

} // namespace property
} // namespace hdf5
