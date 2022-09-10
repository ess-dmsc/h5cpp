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
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace dataspace {

//!
//! \brief scalar dataspace
//!
//! Dataspace for a single value
//!
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
class DLL_EXPORT Scalar : public Dataspace {
 public:
  //!
  //! \brief default constructor
  //!
  Scalar();

  //!
  //! \brief constructor
  //!
  //! Construct a scalar dataspace from its base class. In this case.
  //! If the Dataspace instance is not a scalar instance an exception
  //! will be thrown.
  //!
  //! \throws std::runtime_error in case of an error
  //!
  //! \param space reference to a Dataspace instance
  //!
  Scalar(const Dataspace &space);

};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

} // namespace dataspace
} // namespace hdf5
