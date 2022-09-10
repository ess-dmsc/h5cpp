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

#include <h5cpp/h5cpp.hpp>
#include "rgbpixel.hpp"

namespace hdf5 {
namespace datatype {

template<>
class TypeTrait<RGBPixel>
{
  public:
    using Type = RGBPixel;
    using TypeClass = Compound;

    static TypeClass create(const Type & = Type())
    {

      datatype::Compound type = datatype::Compound::create(sizeof(RGBPixel));
      type.insert("red",0,datatype::create<std::uint8_t>());
      type.insert("green",1,datatype::create<std::uint8_t>());
      type.insert("blue",2,datatype::create<std::uint8_t>());

      return type;
    }

    const static TypeClass & get(const Type & = Type()) {
      const static TypeClass & cref_ = create();
      return cref_;
    }
};

}
}
