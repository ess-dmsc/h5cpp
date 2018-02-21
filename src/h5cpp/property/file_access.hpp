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
// Created on: Aug 18, 2017
//
#pragma once

#include <h5cpp/property/property_list.hpp>
#include <h5cpp/core/windows.hpp>
#include <h5cpp/file/driver.hpp>

namespace hdf5 {
namespace property {

//!
//! \brief library version enumeration
//!
enum class LibVersion : std::underlying_type<H5F_libver_t>::type {
  LATEST = H5F_LIBVER_LATEST,
  EARLIEST = H5F_LIBVER_EARLIEST
};

using LibVersionBase = std::underlying_type<LibVersion>::type;

DLL_EXPORT std::ostream &operator<<(std::ostream &stream, const LibVersion &version);

//!
//! \brief file access property list
//!
//! Class provides object oriented interface to the file access property list.
//!
class DLL_EXPORT FileAccessList : public List {
 public:
  //!
  //! \brief default constructor
  //!
  FileAccessList();

  //!
  //! \brief destructor
  //!
  ~FileAccessList();

  explicit FileAccessList(ObjectHandle &&handle);

  //!
  //! \brief setting library version boundaries
  //!
  void library_version_bounds(LibVersion high, LibVersion low) const;

  //!
  //! \brief get library version high bound
  //!
  LibVersion library_version_bound_high() const;

  //!
  //! \brief get library version low bound
  //!
  LibVersion library_version_bound_low() const;

  //!
  //! \brief set the file driver
  //!
  void driver(const hdf5::file::Driver &file_driver) const;
};

} // namespace property
} // namespace hdf5
