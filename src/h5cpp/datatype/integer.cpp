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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Aug 23, 2017
//

#include <h5cpp/datatype/integer.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5 {
namespace datatype {

Integer::Integer(ObjectHandle &&handle) :
    Datatype(std::move(handle)) {}

Integer::Integer(const Datatype &datatype) :
    Datatype(datatype) {
  if (get_class() != Class::INTEGER) {
    std::stringstream ss;
    ss << "Could not create Integer from " << get_class();
    throw std::runtime_error(ss.str());
  }
}

bool Integer::is_signed() const {
  auto s = H5Tget_sign(static_cast<hid_t>(*this));
  if (s < 0) {
    error::Singleton::instance().throw_with_stack("Could not retrieve datatype sign");
    return false;
  }
  return bool(s);
}

void Integer::make_signed(bool sign) const {
  if (H5Tset_sign(static_cast<hid_t>(*this), (sign ? H5T_SGN_2 : H5T_SGN_NONE)) < 0) {
    std::stringstream ss;
    ss << "Could not set datatype sign to " << sign;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

} // namespace datatype
} // namespace hdf5
