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
// Created on: Oct 11, 2017
//
#pragma once
#include <iostream>
#include "frame_buffer.hpp"

template<typename PixelType>
class DetectorFrame
{
  public:
    using BufferType = FrameBuffer<PixelType>;
    DetectorFrame();
    DetectorFrame(const DetectorFrame &) = default;
    DetectorFrame(DetectorFrame &&) = default;
    DetectorFrame(size_t nfast_direction,size_t nslow_direction);

    size_t size() const noexcept;

    PixelType *data() noexcept;
    const PixelType *data() const noexcept;

    PixelType &operator(size_t slow_index,size_t fast_index) noexcept;
    const PixelType &operator(size_t slow_index,size_t fast_index) const noexcept;

  private:
    size_t nfast_; // number of elements along the fast direction
    size_t nslow_; // number of elements along the slow direction
    BufferType frame_buffer_; // data buffer

};
