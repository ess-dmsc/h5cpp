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
// Created on: Oct 11, 2017
//
#pragma once

#include <type_traits>
#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace datatype {

//!
//! @brief string datatype
//!
//! This type can be used to represent fixed length or variable length strings.
//!
class DLL_EXPORT String : public Datatype
{
 public:
  //!
  //! @brief default constructor
  //!
  //! We need this for STL containers but can rely on the
  //! default compiler implementation for now.
  //!
  String() = default;

  //!
  //! @brief construct from handle
  //!
  String(ObjectHandle &&handle);

  //!
  //! @brief construct from generic datatype instance
  //!
  //! @throws std::runtime_error if the datatype is not a string type
  //!
  String(const Datatype &type);

  //!
  //! @brief construct variable-length string
  //!
  static String variable();

  //!
  //! @brief construct fixed-length string
  //!
  //! Return an instance of String for a fixed length string. The size of the
  //! string must not be 0 as this would  not make any sense at all.
  //!
  //! @throws std::runtime_error in the case of a failure
  //! @param size the size of the new string type
  //!
  static String fixed(size_t size);

  //!
  //! @brief return true if type is a variable length string
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  bool is_variable_length() const;

  //!
  //! @brief get current character encoding for the string
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  CharacterEncoding encoding() const;

  //!
  //! @brief set current character encoding
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  void encoding(CharacterEncoding cset);

  //!
  //! @brief get the current string padding
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  StringPad padding() const;

  //!
  //! @brief set the string padding for the type
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  void padding(StringPad strpad);

  //!
  //! @brief get current size of the string type
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  size_t size() const override;

  //!
  //! @brief set the string size (number of characters)
  //!
  //! There are two conditions which must be met in order for this function
  //! to succeed:
  //!
  //! \li the String instance must not be a variable length type
  //! \li the size must not be 0
  //!
  //! @throws std::runtime_error in case of a failure
  //! @param size the new size for the fixed length string type
  //!
  void size(size_t size) const override;

  //set order? other types?

  //set precision? other types?

  //set offset?
  //can only be 0 for string

};

} // namespace datatype
} // namespace hdf5
