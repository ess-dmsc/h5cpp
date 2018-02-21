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
// Created on: Aug 25, 2017
//
#pragma once

#include <h5cpp/dataspace/type.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace dataspace {

class Dataspace;
class Selection;

//!
//! \brief interface for selection management
//!
//! The \c SelectionManager provides an interface to access the selections
//! made on a \c Dataspace.
//! It stores a reference to the dataspace it belongs to and applies or
//! removes selections on this dataspace.
//!
class DLL_EXPORT SelectionManager {
 public:
  //!
  //! \brief not default constructible
  //!
  SelectionManager() = delete;

  //!
  //! \brief constructor
  //!
  //! \param space reference to the dataspace the manager instance belongs to
  //!
  SelectionManager(Dataspace &space);

  //!
  //! \brief copy constructor
  //!
  //! Use the default implementation here
  //!
  SelectionManager(const SelectionManager &) = default;

  //!
  //! \brief apply a selection
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  //! \param ops selection operator
  //! \param selection reference to the selection to apply
  //!
  void operator()(SelectionOperation ops, const Selection &selection) const;

  //!
  //! \brief return the number of elements in the current selection
  //!
  //! This value may differ from the number of elements stored in a
  //! dataspace.
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  size_t size() const;

  //!
  //! \brief get the type of the current selection
  //!
  SelectionType type() const;

  //!
  //! \brief select everything
  //!
  void all() const;

  //!
  //! \brief select nothing
  //!
  void none() const;

 private:
  //!
  //! reference to the dataspace the instance belongs to
  //!
  Dataspace &space_;
};

} // namespace dataspace
} // namespace hdf5
