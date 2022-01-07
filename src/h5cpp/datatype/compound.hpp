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
// Created on: Oct 5, 2017
//
#pragma once

#include <h5cpp/datatype/datatype.hpp>

namespace hdf5 {
namespace datatype {

//!
//! \brief compound data type
//!
//! A compound data type which can be used for data elements of heterogeneous
//! type like C-structures or a C++ class.
//!
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
class DLL_EXPORT Compound : public Datatype {
 public:
  //!
  //! \brief default constructor
  //!
  Compound() = default;

  //!
  //! \brief construct from handle
  //!
  Compound(ObjectHandle &&handle);

  //!
  //! \brief construct from generic datatype
  //!
  Compound(const Datatype &type);

  //!
  //! \brief constructor
  //!
  static Compound create(size_t size);

  //!
  //! \brief return the datatype for index element
  //!
  Datatype operator[](size_t index) const;

  //!
  //! \brief return the datatype for element name
  //!
  Datatype operator[](const std::string &name) const;

  //!
  //! \brief return the index of a type element
  //!
  size_t field_index(const std::string &name) const;

  std::string field_name(size_t index) const;

  size_t field_offset(const std::string &name) const;
  size_t field_offset(size_t index) const;

  Class field_class(const std::string &name) const;
  Class field_class(size_t index) const;

  //!
  //! \brief return the total number of elements of the type
  //!
  size_t number_of_fields() const;

  void insert(const std::string &name, size_t offset, const Datatype &type) const;

  void pack() const;

};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

} // namespace datatype
} // namespace hdf5
