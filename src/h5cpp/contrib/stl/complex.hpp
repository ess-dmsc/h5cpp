//
// (c) Copyright 2021 DESY, ESS
//               2021 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Authors: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Dec 23, 2021
//
#pragma once

#include <h5cpp/datatype/type_trait.hpp>
#include <complex>

namespace hdf5 { 
namespace datatype { 

template<typename T>
class TypeTrait<std::complex<T>>
{
  private:
    using element_type = TypeTrait<T>;

  public:
    using Type = std::complex<T>;
    using TypeClass = Compound;

    static TypeClass create(const Type & = Type())
    {
      datatype::Compound type = datatype::Compound::create(
        sizeof(std::complex<T>));

      type.insert("real", 0, element_type::create(T()));
      type.insert("imag", alignof(T), element_type::create(T()));

      return type;
    }
  const static TypeClass & get(const Type & = Type()) {
    const static TypeClass & cref_ = create();
    return cref_;
  }
};
}
}
