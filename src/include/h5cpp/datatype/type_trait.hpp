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
// Created on: Aug 28, 2017
//
#pragma once

#include "datatype.hpp"
#include "integer.hpp"
#include "float.hpp"

namespace hdf5 {
namespace datatype {

template<typename T> class TypeTrait
{
  public:
    using TypeClass = Datatype;
    static TypeClass create();
};

template<> class TypeTrait<char>
{
  public:
    using TypeClass = Integer;
    static TypeClass create()
    {
      return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_CHAR)));
    }
};

template<> class TypeTrait<unsigned char>
{
  public:
    using TypeClass = Integer;
    static TypeClass create()
    {
      return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_UCHAR)));
    }
};

template<> class TypeTrait<signed char>
{
  public:
    using TypeClass = Integer;
    static TypeClass create()
    {
      return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_SCHAR)));
    }
};

template<> class TypeTrait<short>
{
  public:
    using TypeClass = Integer;
    static TypeClass create()
    {
      return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_SHORT)));
    }
};

template<> class TypeTrait<unsigned short>
{
  public:
    using TypeClass = Integer;
    static TypeClass create()
    {
      return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_USHORT)));
    }
};

template<> class TypeTrait<int>
{
  public:
    using TypeClass = Integer;
    static TypeClass create()
    {
      return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_INT)));
    }
};

template<> class TypeTrait<unsigned int>
{
  public:
    using TypeClass = Integer;
    static TypeClass create()
    {
      return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_UINT)));
    }
};

template<> class TypeTrait<long>
{
  public:
    using TypeClass = Integer;
    static TypeClass create()
    {
      return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_LONG)));
    }
};

template<> class TypeTrait<unsigned long>
{
  public:
    using TypeClass = Integer;
    static TypeClass create()
    {
      return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_ULONG)));
    }
};

template<> class TypeTrait<long long>
{
  public:
    using TypeClass = Integer;
    static TypeClass create()
    {
      return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_LLONG)));
    }
};

template<> class TypeTrait<unsigned long long>
{
  public:
    using TypeClass = Integer;
    static TypeClass create()
    {
      return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_ULLONG)));
    }
};

template<> class TypeTrait<float>
{
  public:
    using TypeClass = Float;
    static TypeClass create()
    {
      return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_FLOAT)));
    }
};

template<> class TypeTrait<double>
{
  public:
    using TypeClass = Float;
    static TypeClass create()
    {
      return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_DOUBLE)));
    }
};

template<> class TypeTrait<long double>
{
  public:
    using TypeClass = Float;
    static TypeClass create()
    {
      return TypeClass(ObjectHandle(H5Tcopy(H5T_NATIVE_LDOUBLE)));
    }
};



} // namespace datatype
} // namespace hdf5
