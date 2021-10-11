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
// Created on: Oct 25, 2017
//
#pragma once

#include <h5cpp/core/windows.hpp>
#include <h5cpp/core/hdf5_capi.hpp>
#include <iostream>
#include <string>

namespace hdf5
{
namespace error
{

//!
//! \brief HDF5 error descriptor
//!
//! This is a descriptor for an error from the HDF5 error stack.
//! It contains information about where in the underlying HDF5
//! library an error occurred. Such information may be passed on to the user
//! of the library along with thrown exceptions, but only in the case
//! that automatic error stack printing is turned off.
//!
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif
struct DLL_EXPORT Descriptor
{
  //!
  //! \brief constructor
  //!
  //! Constructs a mostly human-readable descriptor from the underlying
  //! C-API handle. Only used by the library internally.
  //!
  //! \param descr reference to C-API error entry
  //!
  Descriptor(const H5E_error2_t& descr);

  void extract_strings();

  hid_t       maj_num;	// major error ID
  hid_t       min_num;	// minor error number
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
  std::string major;         // major error text
  std::string minor;         // minor error text

  unsigned line;          // line in file where error occurs
  std::string function;      // function in which error occurred
  std::string file;          // file in which error occurred
  std::string description;   // supplied description
#ifdef _MSC_VER
#pragma warning(pop)
#endif
};

#ifdef __clang__
#pragma clang diagnostic pop
#endif


//!
//! \brief output operator for Descriptor
//!
DLL_EXPORT std::ostream& operator<<(std::ostream& stream, const Descriptor& desc);

} // namespace file
} // namespace hdf5
