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
// Created on: Aug 23, 2017
//
#pragma once

#include <vector>
#include <type_traits>
#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace datatype {

//!
//! \brief HDF5 integer datatype
//!
class DLL_EXPORT Integer : public Datatype {
 public:
  //!
  //! \brief Default constructor
  //!
  //! We need this for compatability with STL containers. However, we
  //! can use the compiler provided default version.
  //!
  Integer() = default;

  //!
  //! \brief Construct from object handle
  //!
  //! Construct a type from an object handle. The datatype takes full
  //! ownership of the handle whose lifetime is thus bound to the lifetime
  //! of the type.
  //!
  //! \param handle rvalue reference to a new object handle.
  //!
  Integer(ObjectHandle &&handle);

  //!
  //! \brief Copy construction from a Datatype instance
  //!
  //! This copy constructor creates an integer type from an instance of
  //! Datatype. The datatype has to satisfy two conditions
  //!
  //! \li it must be a valid object (is_valid() shoudld return true)
  //! \li it must reference an integer datatype.
  //!
  //! Failure to satify one of the above conditions will cause an
  //! exception.
  //!
  //! \throws std::runtime_error in case of any failure
  //!
  //! \param datatype reference to a Datatype instance
  //!
  Integer(const Datatype &datatype);

  //!
  //! @brief Retrieves the sign type for an integer type.
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual bool is_signed() const;

  //!
  //! @brief Sets the sign property for an integer type.
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual void make_signed(bool sign) const;

  //!
  //! @brief get the precision of type, i.e. the number of significant bits
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual size_t precision() const;

  //!
  //! @brief set the precision of a type, i.e. the number of significant bits
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual void precision(size_t precision) const;

  //!
  //! @brief get the bit offset of the first significant bit
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual size_t offset() const;

  //!
  //! @brief set the bit offset of the first significant bit
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual void offset(size_t offset) const;

  //!
  //! @brief get the order of datatype
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual Order order() const;

  //!
  //! @brief set the order of datatype
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual void order(Order offset) const;

  //!
  //! @brief get the pads of datatype
  //! @return least and most significant bits
  //! @throws std::runtime_error in case of a failure
  //!
  virtual const std::vector<Pad> pad() const;

  //!
  //! @brief set the pads of datatype
  //!
  //! @param lsb padding type for least-significant bits
  //! @param msb padding type for most-significant bits
  //! @throws std::runtime_error in case of a failure
  //!
  virtual void pad(Pad lsb, Pad msb) const;
};

} // namespace datatype
} // namespace hdf5
