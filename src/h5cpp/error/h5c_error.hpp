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
#include <sstream>
#include <stdexcept>
#include <list>

namespace hdf5 {
namespace error {

//!
//! \brief runtime exception containing an HDF5 error H5CError
//!
//! This is an exception class specifically for passing on an HDF5
//! error H5CError. The error H5CError is accessible as a standard list of
//! Descriptor objects. Upon construction, the object also generates
//! a string containing the a printout of the H5CError.
//!
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
class H5CError : public std::runtime_error
{
 public:
  //!
  //! \brief constructor
  //!
  //! Constructs a runtime exception object containing an HDF5 error H5CError.
  //! Should only be used internally by the library.
  //!
  //! \param H5CError a linked list of HDF5 error descriptors
  //!
  H5CError(const std::list<Descriptor>& H5CError);

  //!
  //! \brief printout of error H5CError
  //!
  //! Returns the pre-generated string containing a printout of the
  //! error H5CError.
  //!
  const char* what() const noexcept override;

  //!
  //! \brief access to error H5CError
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
#ifdef __clang__
#pragma clang diagnostic pop
#endif

inline H5CError::H5CError(const std::list<Descriptor>& H5CError)
: std::runtime_error("")
, contents_(H5CError)
{
  std::stringstream ss;
  for (auto& c : contents_)
  {
    c.extract_strings();
    ss << c << "\n";
  }
  what_message_ = ss.str();
}


inline const char* H5CError::what() const noexcept
{
  return what_message_.c_str();
}

inline const std::list<Descriptor>& H5CError::contents() const
{
  return contents_;
}

inline bool H5CError::empty() const
{
  return contents_.empty();
}

} // namespace file
} // namespace hdf5
