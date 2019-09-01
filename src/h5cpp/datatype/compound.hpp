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

/**
 * @brief compound data type
 *
 * A compound data type which can be used for data elements of heterogeneous
 * type like C-structures or a C++ class.
 *
 */
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
  //! \brief factory function
  //!
  //! This factory function create a new base instance for a compound data
  //! type. Once this is created one still has to insert the fields
  //! comprising the type.
  //!
  //! \param size the size of the total compound type in bits
  //! \return new Compound instance
  //!
  static Compound create(size_t size);

  /**
   * @brief get the data type of a field
   *
   * @param index the index of the field
   * @return new instance of the HDF5 data type
   */
  Datatype operator[](size_t index) const;

  /**
   * @brief get the data type of a field
   *
   * @param name the name of the field
   * @return new instance of the HDF5 data type
   */
  Datatype operator[](const std::string &name) const;

  /**
   * @brief index of a field
   *
   * @param name the name of the field for which to obtain the index
   * @return field index
   */
  size_t field_index(const std::string &name) const;

  //!
  //! \brief return the name of a field
  //!
  //! Return the name of a field determined by index.
  //!
  //! \param index the numeric index of the field
  //! \return the name of the field
  //!
  std::string field_name(size_t index) const;

  //!
  //! \brief return offset of a field
  //!
  //! Returns the offset of a particular field determined by its name in bits.
  //!
  //! \param name the name of the field
  //! \return the offset of the field in bits
  //!
  size_t field_offset(const std::string &name) const;

  //!
  //! \brief return offset of a field in
  size_t field_offset(size_t index) const;

  /**
   * @brief get the type class for a field
   *
   * @param name the name of the field
   * @return a new instance of a type class
   */
  Class field_class(const std::string &name) const;

  /**
   * @brief get the type class for a field
   *
   * @param index the index of the field
   * @return a new instance of a type class
   */
  Class field_class(size_t index) const;

  /**
   * @brief the number of fields
   *
   * @return the number of fields comprising the compound type
   */
  size_t number_of_fields() const;

  /**
   * @brief insert a new field into the type
   *
   * @param name the name of the new field
   * @param offset the offset in bits of the field
   * @param type the HDF5 data type of the field
   */
  void insert(const std::string &name, size_t offset, const Datatype &type) const;

  void pack() const;

};

} // namespace datatype
} // namespace hdf5
