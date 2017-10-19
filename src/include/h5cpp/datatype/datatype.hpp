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
#pragma once

#include <type_traits>
extern "C"{
#include<hdf5.h>
}
#include "../object_handle.hpp"
#include "types.hpp"
#include "../windows.hpp"


namespace hdf5 {
namespace datatype {


//!
//! \brief base class for all data types
//!
class DLL_EXPORT Datatype
{
  public:
    virtual ~Datatype();
    Datatype(ObjectHandle &&handle);
    Datatype &operator=(const Datatype &type);
    Datatype(const Datatype &type);

    Datatype &operator=(Datatype &&type) = default;
    Datatype(Datatype &&type) = default;
    Datatype() = default;

    Class get_class() const;

    Datatype super() const;
    Datatype native_type(Direction dir=Direction::ASCEND) const;
    bool has_class(Class type_class) const;

    virtual size_t size() const;
    virtual void set_size(size_t size) const;

    explicit operator hid_t() const
    {
      return static_cast<hid_t>(handle_);
    }
  private:

    ObjectHandle handle_;

};

DLL_EXPORT bool operator==(const Datatype &lhs,const Datatype &rhs);
DLL_EXPORT bool operator!=(const Datatype &lhs,const Datatype &rhs);

namespace prefdefined_types {

DLL_EXPORT extern const Datatype native_int;
DLL_EXPORT extern const Datatype native_double;
DLL_EXPORT extern const Datatype native_long_double;
DLL_EXPORT extern const Datatype native_short;


} // namespace predefined_types


} // namespace datatype
} // namespace hdf5
