//
// (c) Copyright 2018 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Dec 29, 2018
//

#pragma once


#include <h5cpp/hdf5.hpp>
#include "matrix.hpp"


namespace hdf5 {

namespace datatype {

template<typename T,size_t DIM0,size_t DIM1>
class TypeTrait<Matrix<T,DIM0,DIM1>>
{
  public:
    using Type = Matrix<T,DIM0,DIM1>;
    using TypeClass = typename TypeTrait<typename Type::value_type>::TypeClass;

    static TypeClass create(const Type& = Type())
    {
      return TypeTrait<typename Type::value_type>::create();
    }
};


}

namespace dataspace {

template<typename T,size_t DIM0,size_t DIM1>
class TypeTrait<Matrix<T,DIM0,DIM1>>
{
  public:
    using DataspaceType = Simple;

    static DataspaceType create(const Matrix<T,DIM0,DIM1> &value)
    {
      return Simple(Dimensions{DIM0,DIM1},Dimensions{DIM0,DIM1});
    }

    static void *ptr(Matrix<T,DIM0,DIM1> &value)
    {
      return reinterpret_cast<void*>(value.data());
    }

    static const void *cptr(const Matrix<T,DIM0,DIM1> &value)
    {
      return reinterpret_cast<const void*>(value.data());
    }

};

}
}
