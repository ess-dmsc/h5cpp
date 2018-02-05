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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 16, 2017
//
#pragma once

#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/core/object_handle.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace property {

//!
//! \brief property list class
//!
//! This class implements a wrapper around HDF5s property list classes.
//!
//! We have to implement this as a class as it is possible to define custom
//! classes on the fly. Though this functionality is currently not implemented
//! we are on the save side with a class implementation instead of an enumeration.
//!
class DLL_EXPORT Class {
 public:
  //!
  //! \brief default constructor
  //!
  Class() = default;

  //!
  //! \brief copy constructor
  //!
  Class(const Class &c) = default;

  //!
  //! \brief copy assignment
  //!
  Class &operator=(const Class &c) = default;

  //!
  //! \brief constructor
  //!
  explicit Class(ObjectHandle &&handle);

  std::string name() const;
  Class parent() const;

  explicit operator hid_t() const {
    return static_cast<hid_t>(handle_);
  }

 private:
  ObjectHandle handle_;

};

DLL_EXPORT bool operator==(const Class &lhs, const Class &rhs);
DLL_EXPORT bool operator!=(const Class &lhs, const Class &rhs);

DLL_EXPORT extern const Class kAttributeCreate;
DLL_EXPORT extern const Class kDatasetAccess;
DLL_EXPORT extern const Class kDatasetCreate;
DLL_EXPORT extern const Class kDatasetXfer;
DLL_EXPORT extern const Class kDatatypeAccess;
DLL_EXPORT extern const Class kDatatypeCreate;
DLL_EXPORT extern const Class kFileAccess;
DLL_EXPORT extern const Class kFileCreate;
DLL_EXPORT extern const Class kFileMount;
DLL_EXPORT extern const Class kGroupAccess;
DLL_EXPORT extern const Class kGroupCreate;
DLL_EXPORT extern const Class kLinkAccess;
DLL_EXPORT extern const Class kLinkCreate;
DLL_EXPORT extern const Class kObjectCopy;
DLL_EXPORT extern const Class kObjectCreate;
DLL_EXPORT extern const Class kStringCreate;

DLL_EXPORT std::ostream &operator<<(std::ostream &stream, const Class &c);

} // namespace property
} // namespace hdf5
