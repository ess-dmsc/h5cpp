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
// Created on: Oct 20, 2017
//
#pragma once

#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/core/types.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace datatype {

//!
//! \brief array datatype
//!
//! This datatype allows storing multidimensional data as a single element
//! in an dataspace layout. Typical applications would be to use this for
//! tensors and vectors. This is a fixed size data type. All instances (elements)
//! of this type stored in an attribute or dataset are of equal size.
//!
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
class DLL_EXPORT Array : public Datatype
{
 public:
  Array() = default;

  //!
  //! \brief construct from handle
  //!
  Array(ObjectHandle &&handle);

  //!
  //! \brief cosntruct from generic datatype
  //!
  Array(const Datatype &type);

  //!
  //! \brief named constructor
  //!
  static Array create(const Datatype &base_type, const Dimensions &dims);

  //!
  //! \brief get dimensions
  //!
  //! Returns an instance of Dimensions with the number of elements along
  //! each dimension.
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  Dimensions dimensions() const;

  //!
  //! \brief get rank
  //!
  //! Returns the number of dimensions for an array data type
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  size_t rank() const;

};

//!
//! \brief variable length array type
//!
//! Array datatype allowing each element stored in a dataspace
//! having a different size. This type is restricted to a single
//! dimensions. This limitation makes sense as it does not make
//! to much sense to think about multidimensional objects of
//! different size stored in an attribute or dataset.
//!
class DLL_EXPORT VLengthArray : public Datatype
{
 public:
  //!
  //! \brief default constructor
  //!
  //! This constructor is required for compatibility purposes
  //! with STL containers.
  //!
  VLengthArray() = default;

  //!
  //! \brief construct from handle
  //!
  VLengthArray(ObjectHandle &&handle);

  //!
  //! \brief cosntruct from generic datatype
  //!
  VLengthArray(const Datatype &type);

  //!
  //! \brief constructor
  //!
  //! \param base_type the base type for the variable length type
  //!
  static VLengthArray create(const Datatype &base_type);

};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

} // namespace datatype
} // namespace hdf5
