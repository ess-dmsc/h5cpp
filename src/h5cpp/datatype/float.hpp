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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Aug 23, 2017
//
#pragma once

#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/core/windows.hpp>
#include <vector>

namespace hdf5 {
namespace datatype {

class DLL_EXPORT Float : public Datatype {
 public:
  //!
  //! \brief default constructor
  //!
  //! Need this for compliance with STL containers but we can use the
  //! default implementation of the compiler.
  //!
  Float() = default;

  //!
  //! \brief constructor
  //!
  //! \param handle rvalue reference to an HDF5 object handle
  //!
  Float(ObjectHandle &&handle);

  //!
  //! \brief constructor
  //!
  //! Conversion constructor which allows creation of a Float type
  //! from a generic Datatype instance. If datatype does not reference
  //! a float datatype an exception is thrown.
  //!
  //! \throws std::runtime_error in case of a failure
  //! \param datatype reference to a generic datatype instance
  //!
  explicit Float(const Datatype &datatype);

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
  virtual void order(Order order) const;

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

  //!
  //! @brief get the floating point datatype bit field information
  //! @return floating point datatype bit field information,
  //!         i.e. floating-point sign bit, exponent bit-position, size of exponent in bits
  //!              mantissa bit-position, size of mantissa in bits
  //! @throws std::runtime_error in case of a failure
  //!
  virtual const std::vector<size_t> fields() const;

  //!
  //! @brief set the floating point datatype bit field information
  //!
  //! @param spos  floating-point sign bit
  //! @param epos  exponent bit-position
  //! @param esize size of exponent in bits
  //! @param mpos  mantissa bit-position
  //! @param msize size of mantissa in bits
  //! @throws std::runtime_error in case of a failure
  //!
  virtual void fields(size_t spos, size_t epos, size_t esize, size_t mpos, size_t msize) const;

  //!
  //! @brief get the exponent bias of a floating-point type
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual size_t ebias() const;

  //!
  //! @brief set the exponent bias of a floating-point type
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual void ebias(size_t ebias) const;

  //!
  //! @brief get the mantissa normalization of a floating-point datatype
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual Norm norm() const;

  //!
  //! @brief set the mantissa normalization of a floating-point datatype
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual void norm(Norm norm) const;

  //!
  //! @brief get the internal padding type for unused bits in floating-point datatypes
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual Pad inpad() const;

  //!
  //! @brief set the internal padding type for unused bits in floating-point datatypes
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual void inpad(Pad inpad) const;
};


class DLL_EXPORT float16_t{
 private:
  uint16_t _value; //!< data element holding the current float16 value
 public:
  //! default constructor
  float16_t():_value(0u) {}

  //! conversion constructor
  float16_t(uint16_t v):_value(v) {}

  //! conversion operator
  operator uint16_t() const {
    return _value;
  }
};


} // namespace datatype
} // namespace hdf5
