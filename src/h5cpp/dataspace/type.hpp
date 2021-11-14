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
// Created on: Aug 24, 2017
//
#pragma once

#include <iostream>
#include <type_traits>
#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace dataspace {

//!
//! \enum Type determine the datatype instance
//!
//! This enumeration type is primarily used to identify the particular type
//! of dataspace when given only a reference to dataspace::Dataspace.
//!
enum class Type : std::underlying_type<H5S_class_t>::type {
  //!
  //! the dataspace is an instance of dataspace::Scalar
  //!
      Scalar = H5S_SCALAR,

  //!
  //! the dataspace is an instance of dataspace::Simple
  //!
      Simple = H5S_SIMPLE,

  //!
  //! the dataspace is an instance of dataspace::Null
  //!
  //! \warning dataspace::Null is currently not implemented
  //!
      NoData = H5S_NULL
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream, const Type &t);

//!
//! \brief selection type
//!
//! Determines what kind of selection is applied to a datatype. Like
//! datapsace::Type this identifies the particular type of selection
//! when given only a reference to dataspace::Selection.
//!
enum class SelectionType : std::underlying_type<H5S_sel_type>::type {
  //!
  //! nothing is selected
  //!
      None = H5S_SEL_NONE,
  //!
  //! the selection is a point selection (dataspace::Points)
  //!
      Points = H5S_SEL_POINTS,
  //!
  //! the selection is a hyperslab selection (dataspace::Hyperslab)
  //!
      Hyperslab = H5S_SEL_HYPERSLABS,
  //!
  //! everything is selected
  //!
      All = H5S_SEL_ALL
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream, const SelectionType &t);

//!
//! \brief selection operator
//!
enum class SelectionOperation : std::underlying_type<H5S_seloper_t>::type {
  //!
  //! replace all selections by this one
  //!
      Set = H5S_SELECT_SET,
  //!
  //! select all elements which are in this or the previously applied
  //! selections
  //!
      Or = H5S_SELECT_OR,
  //!
  //! selects the overlapping region of the actual selection and previously
  //! applied selections
  //!
      And = H5S_SELECT_AND,
  //!
  //! select all elements which are either in this or in the previously
  //! applied selections but not in both
  //!
      XOr = H5S_SELECT_XOR,
  //!
  //! select those elements which are on the previously applied selections
  //! but not in the current one
  //!
      NotB = H5S_SELECT_NOTB,
  //!
  //! select only those elements which are in the current selection and not
  //! in the previous ones
  //!
      NotA = H5S_SELECT_NOTA,
  //!
  //! for point selections: add the point to the end of the current list
  //! of points
  //!
      Append = H5S_SELECT_APPEND,
  //!
  //! for point selections: add the point to the beginning of the current
  //! list of points
  //!
      Prepend = H5S_SELECT_PREPEND
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream, const SelectionOperation &o);

} // namespace dataspace
} // namespace hdf5
