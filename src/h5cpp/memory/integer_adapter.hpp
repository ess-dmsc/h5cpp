//
// (c) Copyright 2019 DESY,ESS
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
// Created on: Sep 1, 2019
//
#pragma once

#include <h5cpp/memory/memory_adapter.hpp>

namespace hdf5 {
namespace memory {


//template<>
//class MemoryAdapter<int>
//{
//  public:
//    using DataspaceType = dataspace::Scalar;
//    using DatatypeType = datatype::Integer;
//
//
//    static int create(const datatype::Datatype & = datatype::Datatype(),
//                      const dataspace::Dataspace & = dataspace::Dataspace())
//    {
//      return int();
//    }
//
//    DataspaceType dataspace() const
//    {
//      return dataspace::Scalar();
//    }
//
//    DatatypeType datatype() const
//    {
//      return datatype::Integer(ObjectHandle(H5Tcopy(H5T_NATIVE_INT32)));
//    }
//};


}
}
