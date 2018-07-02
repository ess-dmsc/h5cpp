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
// Created on: Oct 07, 2017
//
#pragma once
#include <complex>
#include <h5cpp/hdf5.hpp>

namespace hdf5 {
namespace datatype {

template<typename BT>
struct complex_t
{
    BT real;
    BT imag;
};

template<typename T>
class TypeTrait<std::complex<T>>
{
  private:
    using complex_type = complex_t<T>;
  public:
    using Type = std::complex<T>;
    using TypeClass = Compound;

    static TypeClass create(const Type & = Type())
    {

      datatype::Compound type = datatype::Compound::create(sizeof(complex_type));
      type.insert("real",HOFFSET(complex_type,real),datatype::create<T>());
      type.insert("imag",HOFFSET(complex_type,imag),datatype::create<T>());

      return type;
    }
};

}
}

