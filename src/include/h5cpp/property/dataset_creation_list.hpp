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

#include "object_creation_list.hpp"
#include "../types.hpp"

namespace hdf5 {
namespace property {

class DatasetCreationList : public ObjectCreationList
{
  public:
    enum class Layout : std::underlying_type<H5D_layout_t>::type
    {
      COMPACT    = H5D_COMPACT,
      CONTIGUOUS = H5D_CONTIGUOUS,
      CHUNKED    = H5D_CHUNKED,
#if H5_VERSION_GE(1,10,0)
      VIRTUAL    = H5D_VIRTUAL
#endif
    };

    DatasetCreationList();
    ~DatasetCreationList();

    void layout(Layout layout) const;
    Layout layout() const;

    void chunk(const hdf5::Dimensions &chunk_dims) const;
    hdf5::Dimensions chunk() const;



};

} // namespace property
} // namespace hdf5
