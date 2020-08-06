//
// (c) Copyright 2019 DESY,ESS, Eugen Wintersberger <eugen.wintersberger@gmail.com>
//
// This file is part of h5pp.
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
// Created on: Jan 13, 2019
//

#pragma once

#include <h5cpp/hdf5.hpp>
#include <h5cpp/datatype/enum.hpp>
#include <iostream>
#include <cstdint>

enum class Phase : unsigned char {
    SOLID,
    LIQUID,
    GAS,
    PLASMA
};

std::ostream &operator<<(std::ostream &stream,const Phase &phase);


namespace hdf5 {
namespace datatype {

template<>
class TypeTrait<Phase>
{
  public:
    using Type = Phase;
    using TypeClass = Enum;

    static TypeClass create(const Type& = Type())
    {
      Enum type = Enum::create(Phase());
      type.insert("SOLID",Phase::SOLID);
      type.insert("LIQUID",Phase::LIQUID);
      type.insert("GAS",Phase::GAS);
      type.insert("PLASMA",Phase::PLASMA);

      return type;
    }

};

} // end of namespace datatype
} // end of namespace hdf5
