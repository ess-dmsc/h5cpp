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

#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/core/types.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace dataspace {

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
//!
//! \brief simple multidimensional dataspace
//!
class DLL_EXPORT Simple : public Dataspace {
 public:
  //!
  //! \brief dimension value for unlimited number of elements
  //!
  static const hsize_t unlimited;

  //!
  //! \brief default constructor
  //!
  Simple();

  //!
  //! \brief constructor
  //!
  //! Construct a simple dataspace from a reference to its base
  //! instance. If space does not refer to a simple dataspace an
  //! exception will be thrown.
  //!
  //! \throws std::runtime_error in case of a failure
  //! \param space reference to a dataspace instance
  //!
  Simple(const Dataspace &space);

  //!
  //! \brief constructor
  //!
  //! If the maximum dimensions is not provided it will be set to the
  //! current number of elements along each dimension.
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  //! \param current current number of elements along each dimension
  //! \param maximum maximum number of elements along each dimension
  //! \sa dimensions
  //!
  Simple(const Dimensions &current,
         const Dimensions &maximum = hdf5::Dimensions());

  //!
  //! \brief get number of dimensions
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  size_t rank() const;

  //!
  //! \brief set number of elements along each dimension
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  void dimensions(const Dimensions &current,
                  const Dimensions &maximum = Dimensions());

  //!
  //! \brief get current dimensions
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  Dimensions current_dimensions() const;

  //!
  //! \brief get maximum dimensions
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  Dimensions maximum_dimensions() const;
};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

} // namespace dataspace
} // namespace hdf5
