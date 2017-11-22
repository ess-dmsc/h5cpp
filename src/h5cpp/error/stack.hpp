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

#include <h5cpp/error/descriptor.hpp>
#include <exception>
#include <list>

namespace hdf5 {
namespace error {

//!
//! \brief runtime exception containing an HDF5 error stack
//!
//! This is an exception class specifically for passing on an HDF5
//! error stack. The error stack is accessible as a standard list of
//! Descriptor objects. Upon construction, the object also generates
//! a string containing the a printout of the stack.
//!
class DLL_EXPORT Stack : public std::runtime_error
{
 public:
  //!
  //! \brief constructor
  //!
  //! Constructs a runtime exception object containing an HDF5 error stack.
  //! Should only be used internally by the library.
  //!
  //! \param stack a linked list of HDF5 error descriptors
  //!
  Stack(const std::list<Descriptor>& stack);

  //!
  //! \brief printout of error stack
  //!
  //! Returns the pre-generated string containing a printout of the
  //! error stack.
  //!
  const char* what() const throw();

  //!
  //! \brief access to error stack
  //!
  //! Returns reference to list of error descriptors.
  //!
  const std::list<Descriptor>& contents() const;

  //!
  //! \brief what it says
  //!
  //! Convenience function
  //!
  bool empty() const;

 private:
  std::list<Descriptor> contents_;
  std::string what_message_;
};


} // namespace file
} // namespace hdf5
