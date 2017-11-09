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

#include <h5cpp/hdf5_capi.hpp>
#include <type_traits>
#include <iostream>
#include <h5cpp/windows.hpp>
#include <h5cpp/property/link_access.hpp>

namespace hdf5 {

//!
//! \brief iteration order
//!
enum class IterationOrder : std::underlying_type<H5_iter_order_t>::type
{
  INCREASING = H5_ITER_INC,
  DECREASING = H5_ITER_DEC,
  NATIVE     = H5_ITER_NATIVE
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const IterationOrder &order);

//!
//! \brief iteration index
//!
enum class IterationIndex : std::underlying_type<H5_index_t>::type
{
  NAME = H5_INDEX_NAME,
  CREATION_ORDER = H5_INDEX_CRT_ORDER
};

DLL_EXPORT std::ostream &operator<<(std::ostream &stream,const IterationIndex &index);

class DLL_EXPORT IteratorConfig
{
  public:
    IteratorConfig();
    IteratorConfig(const IteratorConfig &) = default;

    IterationOrder order() const noexcept;
    void order(IterationOrder o) noexcept;

    IterationIndex index() const noexcept;
    void index(IterationIndex i) noexcept;

    const property::LinkAccessList &link_access_list() const noexcept;
    void link_access_list(const property::LinkAccessList &list);

  private:
    IterationOrder order_;
    IterationIndex index_;
    property::LinkAccessList lapl_;

};

} // namespace hdf5
