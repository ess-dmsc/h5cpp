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
// Created on: Aug 21, 2017
//
#pragma once

#include <h5cpp/core/hdf5_capi.hpp>
#include <vector>

namespace hdf5 {

using Dimensions = std::vector<hsize_t>;

using VarLengthDataBuffer = std::vector<hvl_t>;

//!
//! \brief variable length buffer trait
//!
//! This trait provides conversion functions from an instance of T to
//! a variable length data buffer and back.
//!
template<typename T>
struct VarLengthBufferTrait
{
    static void to_buffer(const T &,VarLengthDataBuffer &)
    {}

    static void from_buffer(const VarLengthDataBuffer &,T &)
    {}
};

} // namespace hdf5
