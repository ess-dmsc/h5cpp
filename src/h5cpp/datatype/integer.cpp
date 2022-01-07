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
#include <h5cpp/core/utilities.hpp>
#include <sstream>

namespace hdf5 {
namespace datatype {

Integer::Integer(ObjectHandle &&handle) :
    Datatype(std::move(handle)) {}

Integer::Integer(const Datatype &datatype) :
    Datatype(datatype) {
  if (get_class() != Class::Integer) {
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

size_t Integer::precision() const {
  size_t p = H5Tget_precision(static_cast<hid_t>(*this));
  if (p == 0) {
    error::Singleton::instance().throw_with_stack("Could not retrieve datatype precision");
  }
  return p;
}

void Integer::precision(size_t precision) const {
  if (H5Tset_precision(static_cast<hid_t>(*this), precision) < 0) {
    std::stringstream ss;
    ss << "Could not set datatype precision to " << precision;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

size_t Integer::offset() const {
  ssize_t p = H5Tget_offset(static_cast<hid_t>(*this));
  if (p < 0) {
    error::Singleton::instance().throw_with_stack("Could not retrieve datatype offset");
  }
  return signed2unsigned<size_t>(p);
}

void Integer::offset(size_t offset) const {
  if (H5Tset_offset(static_cast<hid_t>(*this), offset) < 0) {
    std::stringstream ss;
    ss << "Could not set datatype offset to " << offset;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

Order Integer::order() const {
  htri_t ret = H5Tget_order(static_cast<hid_t>(*this));
  if (ret > 4) {
    error::Singleton::instance().throw_with_stack("Could not retrieve datatype order");
  }
  return static_cast<Order>(ret);
}

void Integer::order(Order order) const {
  if (H5Tset_order(static_cast<hid_t>(*this), static_cast<H5T_order_t>(order)) < 0) {
    std::stringstream ss;
    ss << "Could not set datatype order to " << order;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}


const std::vector<Pad> Integer::pad() const {
  H5T_pad_t lsb;
  H5T_pad_t msb;
  std::vector<Pad> pads(2);
  htri_t ret = H5Tget_pad(static_cast<hid_t>(*this), &lsb, &msb);
  if (ret < 0) {
    error::Singleton::instance().throw_with_stack("Could not retrieve datatype order");
  }
  pads[0] = static_cast<Pad>(lsb);
  pads[1] = static_cast<Pad>(msb);
  return pads;
}

void Integer::pad(Pad lsb, Pad msb) const {
  if (H5Tset_pad(static_cast<hid_t>(*this),
		 static_cast<H5T_pad_t>(lsb),
		 static_cast<H5T_pad_t>(msb)) < 0) {
    std::stringstream ss;
    ss << "Could not set datatype pad to (" << lsb << ", " << msb << ")" ;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

} // namespace datatype
} // namespace hdf5
