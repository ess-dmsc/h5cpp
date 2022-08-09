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
// Created on: Oct 10, 2017
//
#pragma once

#include <h5cpp/h5cpp.hpp>
#include "vector.hpp"

namespace hdf5 {
namespace datatype {

//!
//! \brief datatype trait for a 3D vector
//!
template<typename T>
class TypeTrait<Vector<T>>
{
  public:
    using Type = Vector<T>;
    using TypeClass = Compound;

    static TypeClass create(const Type& = Type())
    {
      Compound type = Compound::create(sizeof(Vector<T>));
      type.insert("x",0,TypeTrait<T>::create());
      type.insert("y",sizeof(T),TypeTrait<T>::create());
      type.insert("z",sizeof(T)*2,TypeTrait<T>::create());

      return type;
    }

    const static TypeClass & get(const Type & = Type()) {
      const static TypeClass & cref_ = create();
      return cref_;
    }
};

}
}
