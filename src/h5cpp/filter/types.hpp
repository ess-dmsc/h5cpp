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
// Created on: Nov 6, 2017
//
#pragma once

#include <h5cpp/core/hdf5_capi.hpp>

namespace hdf5 {
namespace filter {


using FilterID = H5Z_filter_t;

//!
//! \brief availability requirement of a filter
//!
//! When a filter is applied to a dataset creation property list the
//! user in general must declare a degree of availability for the filter.
//! A filter can be either \b optional or \b mandatory. In the former case
//! the filter is simply omitted if not available (for instance an external
//! filter) in the latter case the operation fails if the filter is not
//! available.
//!
//! This enumeration type is used to mark a filter as optional or mandatory.
//!
enum class Availability : unsigned int
{
  Mandatory = H5Z_FLAG_MANDATORY,
  Optional  = H5Z_FLAG_OPTIONAL
};


} // namespace filter
} // namespace hdf5
