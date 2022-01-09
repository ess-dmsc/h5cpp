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
#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/core/types.hpp>
#include <h5cpp/core/windows.hpp>
#include <memory>
#include <list>

namespace hdf5 {
namespace dataspace {

//!
//! \brief selection base class
//!
class DLL_EXPORT Selection {
 public:
  //!
  //! \brief pointer for selection stacks
  //!
  //! As selections use virtual functions for being applied we have to
  using UniquePointer = std::unique_ptr<Selection>;
  using SharedPointer = std::shared_ptr<Selection>;

  //!
  //! \brief default constructor
  //!
  //! Use the compiler provided default implementation.
  Selection() = default;

  //!
  //! \brief copy constructor
  //!
  //! Use the compiler provided default implementation.
  //!
  Selection(const Selection &) = default;

  //!
  //! \brief destructor
  //!
  //! The destructor has to be virtual to inherit from this class.
  //!
  virtual ~Selection();

  //!
  //! \brief apply a selection onto a dataspace
  //!
  //! The current selection will be applied to dataspace \c space using the
  //! operator determined by \c ops.
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  //! \param space reference to the dataspace onto which to apply the
  //!              selection
  //! \param ops operator for the selection
  virtual void apply(const Dataspace &space,
                     SelectionOperation ops) const = 0;
  //!
  //! \brief get current dimensions
  //!
  //! Get a number of elements along each dimension a selection spans
  //! this is particularly useful in the case of a Hyperslab 
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  //! \return the selection dimentsions
  //!
  virtual Dimensions dimensions() const = 0;

  //!
  //! \brief get the selection size
  //!
  //! Get the total number of elements adressed by an individual selection
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  //! \return the selection type enumerator
  //!
  virtual size_t size() const = 0;

  //!
  //! \brief get the selection type
  //!
  //! Get the type of the selection
  //!
  //! \return the selection type enumerator
  //!
  virtual SelectionType type() const = 0;
};

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif
struct OperationWithSelection {
  SelectionOperation operation;
  Selection::SharedPointer selection;
};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

using SelectionPair = std::pair<SelectionOperation, Selection::SharedPointer>;
using SelectionList = std::list<OperationWithSelection>;

DLL_EXPORT Dataspace operator||(const Dataspace &space, const SelectionList &selections);

} // namespace dataspace
} // namespace hdf5
