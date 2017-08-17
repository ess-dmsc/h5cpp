//
// (c) Copyright 2017 DESY,ESS
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
// Created on: Aug 15, 2017
//

#include "datatype.hpp"


namespace hdf5 {

Datatype Datatype::create(Datatype::Class type_class,size_t size)
{

  return Datatype();
}

template<>
Datatype Datatype::create<double>()
{
  return Datatype(ObjectHandle(H5Tcopy(H5T_NATIVE_DOUBLE)));
}

template<>
Datatype Datatype::create<float>()
{
  return Datatype(ObjectHandle(H5Tcopy(H5T_NATIVE_FLOAT)));
}

template<>
Datatype Datatype::create<long double>()
{
  return Datatype(ObjectHandle(H5Tcopy(H5T_NATIVE_LDOUBLE)));
}


Datatype::Datatype(ObjectHandle &&handle):
      handle_(std::move(handle))
{}

} // namespace hdf5
