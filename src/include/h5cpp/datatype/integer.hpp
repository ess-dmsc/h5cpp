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
// Created on: Aug 23, 2017
//
#pragma once

#include <type_traits>
#include "datatype.hpp"
#include "copy_native_type.hpp"

namespace hdf5 {
namespace datatype {


class Integer : public Datatype
{
  public:
    template<typename T>
    static Integer create();

  private:
    Integer(ObjectHandle &&handle);

};

template<typename T>
Integer Integer::create()
{
  static_assert(std::is_integral<T>::value,"Type must be integral");

  return Integer(ObjectHandle(copy_native_type<T>()));
}

} // namespace datatype
} // namespace hdf5
