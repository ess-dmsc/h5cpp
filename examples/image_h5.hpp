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
// Created on: Oct 08, 2017
//
#pragma once

#include <h5cpp/hdf5.hpp>
#include "image.hpp"
#include "rgbpixel_h5.hpp"

namespace hdf5 {
namespace datatype {

template<typename PixelT>
class TypeTrait<Image<PixelT>>
{
  public:
    using Type = Image<PixelT>;
    using TypeClass = typename TypeTrait<PixelT>::TypeClass;

    static TypeClass create(const Type& = Type())
    {
      return TypeTrait<PixelT>::create();
    }
};

}
}


namespace hdf5 {
namespace dataspace {

template<typename PixelT>
class TypeTrait<Image<PixelT>>
{
  public:
    using DataspaceType = Simple;

    static DataspaceType create(const Image<PixelT> &value)
    {
      return Simple(hdf5::Dimensions{value.ny(),value.nx()},
                    hdf5::Dimensions{value.ny(),value.nx()});
    }

    static void *ptr(Image<PixelT> &value)
    {
      return reinterpret_cast<void*>(value.data());
    }

    static const void *cptr(const Image<PixelT> &value)
    {
      return reinterpret_cast<const void *>(value.data());
    }
};

}
}
