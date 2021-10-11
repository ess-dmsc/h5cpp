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
// Created on: Nov 13, 2017
//
#pragma once

#include <h5cpp/dataspace/hyperslab.hpp>
#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace dataspace {

//!
//! \brief guard object for selections
//!
//! The View class applies selections on a dataspace. Since a copy of the
//! original dataspace is created the former one remains unchanged.
//!
class DLL_EXPORT View {
 public:
  //!
  //! \brief default constructor
  //!
  //! Need this for STL container compatibility. Can rely on default
  //! implementation provided by the compiler.
  //!
  View() = default;

  //!
  //! \brief copy constructor
  //!
  //! Need this for STL container compatibility. Use the default
  //! implementation provided by the compiler.
  //!
  View(const View &) = default;

  //!
  //! \brief constructor
  //!
  //! This constructor applies now selection but selects all elements in the
  //! dataspace.
  //!
  //! \throws std::runtime_error in the case of a failure
  //! \param space reference to the original dataspace
  //!
  explicit View(const Dataspace &space);

  //!
  //! \brief constructor
  //!
  //! Creates a copy of the dataspace and applies all selections provieed
  //! by th selection list to this copy.
  //!
  //! \throws std::runtime_error in case of a failure
  //! \param space reference to the original dataspace
  //! \param selections reference to the list of selections to apply
  //!
  View(const Dataspace &space, const SelectionList &selections);

  //!
  //! \brief constructor
  //!
  //! Creates a copy of the dataspace and applies a single hyperslab on it.
  //! This is a conveniance constructor in the case that we need only a
  //! single hyperslab.
  //!
  //! \throws std::runtime_error in case of a failure
  //! \param space reference to the original dataspace
  //! \param selection reference to the original hyperslab
  //!
  View(const Dataspace &space, const Hyperslab &selection);

  //!
  //! \brief apply a new set of selections
  //!
  //! Calling this operator will erase all current selections and replace
  //! them by the new set of selections provided by the \c selections
  //! argument.
  //!
  //! \throws std::runtime_error
  void operator()(const SelectionList &selections) const;

  //!
  //! \brief set a single hyperslab
  //!
  //! This is a mere convienance function for situations where a single
  //! Hyperslab should be selected. This even might be the most common
  //! case at all.
  //!
  //! \throws std::runtime_error in case of a failure
  //! \param slab reference to the hyperslab
  //!
  void operator()(const Hyperslab &slab) const;

  //!
  //! \brief get number of elements in the view
  //!
  size_t size() const;

  explicit operator hid_t() const {
    return static_cast<hid_t>(space_);
  }

 private:
  Dataspace space_;

  //!
  //! \brief delete all selections
  //!
  void clear() const;

  //!
  //! \brief apply a selection list
  //!
  void apply(const SelectionList &selections) const;
};

} // namespace dataspace
} // namespace hdf5
