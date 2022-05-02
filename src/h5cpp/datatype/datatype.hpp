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
// Created on: Aug 15, 2017
//
#pragma once

#include <type_traits>
#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/core/object_handle.hpp>
#include <h5cpp/datatype/types.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace datatype {

//!
//! @brief base class for all data types
//!
class DLL_EXPORT Datatype
{
 public:
  //!
  //! @brief destructor
  //!
  //! Must be virtual for inheritance.
  //!
  virtual ~Datatype();

  //!
  //! @brief default constructor
  //!
  //! Use default compiler implementation here. This will leave
  //! datatype as an invalid HDF5 object. For a default constructed
  //! datatype the class is NONE.
  //!
  //! @sa is_valid()
  //!
  Datatype() = default;

  //!
  //! @brief constructor
  //!
  //! Construct a datatype from an HDF5 object handle.
  //! @throws std::runtime_error in case of a failure
  //! @param handle rvalue reference to the original handle
  //!
  Datatype(ObjectHandle &&handle);

  //!
  //! @brief move constructor
  //!
  //! Use default implementation here.
  //!
  Datatype(Datatype &&type) = default;

  //!
  //! @brief copy constructor
  //!
  //! Use default compiler implementation.
  //!
  Datatype(const Datatype &type);

  //!
  //! @brief copy assignment
  //!
  //! Use default compiler implementation here.
  //!
  Datatype &operator=(const Datatype &type);

  //!
  //! @brief move assignment
  //!
  //! Use default compiler implementation here.
  //!
  Datatype &operator=(Datatype &&type) = default;

  //!
  //! @brief returns the datatypes class
  //!
  //! @throw std::runtime_error in case of a failure
  //!
  Class get_class() const;

  //!
  //! @brief get the base type
  //!
  //! For an array type this will return the base type of the
  //! elements of the array. For an enumeration type it will return
  //! the underlying integer type.
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  Datatype super() const;

  //!
  //! @brief get native type
  //!
  //! Returns the native type associated with a particular data type.
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  Datatype native_type(Direction dir = Direction::Ascend) const;

  //!
  //! @brief search for a type class
  //!
  //! Checks if a type contains a particular type class.
  //!
  bool has_class(Class type_class) const;

  //!
  //! @brief get size of type in bytes
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual size_t size() const;

  //!
  //! @brief set the size of a type in bytes
  //!
  //! @throws std::runtime_error in case of a failure
  //!
  virtual void size(size_t size) const;

  explicit operator hid_t() const
  {
    return static_cast<hid_t>(handle_);
  }

  //!
  //! \brief check status of the object
  //!
  //! Returns true if the instance is a valid HDF5 object, otherwise
  //! it returns false. This can be used to check whether or not an
  //! instance has been default constructed (in which case flase will
  //! be returned).
  bool is_valid() const;
 private:

  ObjectHandle handle_;

  //!
  //! @brief helper for copy assignment and copy constructor
  //!
  void swap(const Datatype &type);

};

//!
//! @brief equality check for datatypes
//!
//! Returns if two datatypes are equal. Datatypes are considered equal if
//! they represent the same type.
//!
//! @param lhs reference to the left handside Datatype instance
//! @param rhs reference to the right handside Datatype instance
//! @return true if instances are considered equal, false otherwise
//!
DLL_EXPORT bool operator==(const Datatype &lhs, const Datatype &rhs);

//!
//! @brief inequality check for datatypes
//!
//! Returns true if both datatypes do not represent the same types.
//!
//! @param lhs reference to the left hand-side Datatype instance
//! @param rhs reference to the right hand-side Datatype instance
//! @return true if datatypes are not equal, false otherwise
//!
DLL_EXPORT bool operator!=(const Datatype &lhs, const Datatype &rhs);

} // namespace datatype
} // namespace hdf5
