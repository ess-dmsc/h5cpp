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
#include <iostream>
#include "../H5D/matrix.hpp"


template<typename T,size_t D0,size_t D1>
class DataItem : public Matrix<T,D0,D1>
{
  public:
    using Matrix<T,D0,D1>::Matrix;
};


namespace hdf5 {
namespace datatype {

template<typename T,size_t D0,size_t D1>
class TypeTrait<DataItem<T,D0,D1>>
{
  public:
    using Type = DataItem<T,D0,D1>;
    using TypeClass = Array;

    static TypeClass create(const Type& = Type())
    {
      return Array::create(datatype::create<T>(),{D0,D1});
    }
};

} // end of namespace datatype

namespace dataspace {

template<typename T,size_t D0,size_t D1>
class TypeTrait<DataItem<T,D0,D1>>
{
  public:
    using DataspaceType = Scalar;

    static DataspaceType create(const Matrix<T,D0,D1> &value)
    {
      return Scalar();
    }

    static void *ptr(Matrix<T,D0,D1> &value)
    {
      return reinterpret_cast<void*>(value.data());
    }

    static const void *cptr(const Matrix<T,D0,D1> &value)
    {
      return reinterpret_cast<const void*>(value.data());
    }

};

} // end of namespace dataspace
} // end of namespace hdf5




