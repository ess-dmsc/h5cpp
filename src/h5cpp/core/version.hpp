//
// (c) Copyright 2018 DESY,ESS
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Feb 7, 2018
//
#pragma once

#include <string>
#include <iostream>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {

//!
//! @brief a 3 number version class
//!
//! Describes a version number.
//!
class DLL_EXPORT Version
{
  public:
    //!
    //! @brief the number type used to represent version numbers
    //!
    using NumberType = unsigned long;
  private:
    NumberType major_;
    NumberType minor_;
    NumberType patch_;
  public:
    //!
    //! @brief default constructor
    //!
    //! Set all three version numbers to 0
    //!
    Version() noexcept;

    //!
    //! @brief constructor
    //! @param major_number the major version number
    //! @param minor_number the minor version number
    //! @param patch the patch version number
    //!
    Version(NumberType major_number, NumberType minor_number, NumberType patch) noexcept;

    //!
    //! @brief return the major version number
    //!
    NumberType major_number() const noexcept;

    //!
    //! @brief return the minor version number
    //!
    NumberType minor_number() const noexcept;

    //!
    //! @brief return the patch version number
    //!
    NumberType patch_number() const noexcept;

    //!
    //! @brief convert a Version to a string
    //!
    //! The result is a string with the format *MAJOR.MINOR.PATCH*.
    //! @param version reference to a instance of Version
    //! @return a new instance of std::string
    //!
    static std::string to_string(const Version &version);
};

//!
//! @brief output stream operator
//!
//! Writes an instance of Version to a std::ostream. The output format is the
//! same as for Version::to_string.
//!
//! @param stream   the stream where to write the version
//! @param version  reference to the Version to write
//! @return modified version of std::ostream
//! @sa Version::to_string
//!
DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const Version &version);

//!
//! @brief checks two version for equality
//!
//! Two version are considered equal if all of their parts are equal.
//!
//! @param lhs reference to the left hand side version
//! @param rhs reference to the right hand side version
//! @return true if versions are equal, false otherwise
//!
DLL_EXPORT bool operator==(const Version &lhs,const Version &rhs);

//!
//! @brief checks if two versions are not equal
//!
//! @param lhs reference to the left hand side version
//! @param rhs reference to the right hand side version
//! @return true if versions are not equal, false otherwise
//!
DLL_EXPORT bool operator!=(const Version &lhs,const Version &rhs);

//!
//! @brief checks if the left version is smaller or equal to the right
//!
//! @param lhs reference to the left hand side version
//! @param rhs reference to the right hand side version
//!
DLL_EXPORT bool operator<=(const Version &lhs,const Version &rhs);

//!
//! @brief checks if the left version is strictly small than the right
//!
//! @param lhs reference to the left hand side version
//! @param rhs reference to the right hand side version
//!
DLL_EXPORT bool operator<(const Version &lhs,const Version &rhs);

//!
//! @brief checks if the left version is bigger or equal than the right
//!
//! @param lhs reference to the left hand side version
//! @param rhs reference to the right hand side version
//!
DLL_EXPORT bool operator>=(const Version &lhs,const Version &rhs);

//!
//! @brief checks if the left version is strictly bigger than the right
//!
//! @param lhs reference to the left hand side version
//! @param rhs reference to the right hand side version
//!
DLL_EXPORT bool operator>(const Version &lhs,const Version &rhs);

//!
//! @brief returns the current version of the HDF5 library
//!
//! @throws std::runtime_error in case of a failure
//! @return instance of Version with the current HDF5 version
DLL_EXPORT Version current_library_version();

} // namespace hdf5
