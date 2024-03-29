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
// Created on: Oct 16, 2017
//
#pragma once

#include <h5cpp/hdf5.hpp>
#include "frame_buffer.hpp"

//!
//! \brief FrameBuffer HDF5 support
//!
//! Header file with type traits to support FrameBuffer for HDF5 IO.
//!

//=============================================================================
// The FrameBuffer is considered a Container and thus the elementary data type
// is the type of the PixelType.
//=============================================================================
namespace hdf5 {
namespace datatype {

template<typename PixelType>
class TypeTrait<FrameBuffer<PixelType>>
{
  public:
    using Type = FrameBuffer<PixelType>;
    using TypeClass = typename TypeTrait<PixelType>::TypeClass;

    static TypeClass create(const Type & = Type())
    {
      return TypeTrait<PixelType>::create();
    }

    const static TypeClass & get(const Type & = Type()) {
      const static TypeClass & cref_ = create();
      return cref_;
    }
};

} // namespace datatype
} // namespace hdf5

namespace hdf5 {
namespace dataspace {

template<typename PixelType>
class TypeTrait<FrameBuffer<PixelType>>
{
  public:


};


} // namespace dataspace
} // namespace hdf5
