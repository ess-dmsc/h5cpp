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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Sep 11, 2017
//
#pragma once

#include <h5cpp/core/hdf5_capi.hpp>
#include <type_traits>
#include <iostream>
#include <h5cpp/core/windows.hpp>
#include <h5cpp/property/link_access.hpp>

namespace hdf5 {

//!
//! \enum IterationOrder iteration order
//!
//! This enumeration is used to control how an iterator traverses an iterable
//! with a particular index.
//!
enum class IterationOrder : std::underlying_type<H5_iter_order_t>::type
{
  Increasing = H5_ITER_INC,    //!< iteration in increasing index order
  Decreasing = H5_ITER_DEC,    //!< iteration in decreasing index order
  Native     = H5_ITER_NATIVE  //!< iteration in native index order
};

//!
//! @brief ouput stream for iteration order enumeration
//!
DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const IterationOrder &order);

//!
//! @brief iteration index
//!
enum class IterationIndex : std::underlying_type<H5_index_t>::type
{
  //!using the name as index
  Name = H5_INDEX_NAME,
  CreationOrder = H5_INDEX_CRT_ORDER  //!< using creation time as index
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const IterationIndex &index);

//!
//! @brief iterator configuration
//!
//! This class encapsulates the iteration configuration for nodes, attributes and
//! links.
//!
class DLL_EXPORT IteratorConfig
{
  public:
    //!
    //! @brief default constructor
    //!
    IteratorConfig();

    //!
    //! @brief copy constructor
    //!
    //! We use the compiler provided default implementation here.
    //!
    IteratorConfig(const IteratorConfig &) = default;

    //!
    //! @brief get the current iteration order
    //!
    IterationOrder order() const noexcept;

    //!
    //! @brief set the iteration order
    //!
    void order(IterationOrder o) noexcept;

    //!
    //! @brief get the current iteration index
    //!
    IterationIndex index() const noexcept;

    //!
    //! @brief set the current iteration index
    //!
    void index(IterationIndex i) noexcept;

    const property::LinkAccessList &link_access_list() const noexcept;
    void link_access_list(const property::LinkAccessList &list);

  private:
    IterationOrder order_;
    IterationIndex index_;
    property::LinkAccessList lapl_;

};

} // namespace hdf5
