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

#include <h5cpp/datatype/float.hpp>
#include <h5cpp/error/error.hpp>
#include <h5cpp/core/utilities.hpp>
#include <sstream>

namespace hdf5 {
namespace datatype {

Float::Float(ObjectHandle &&handle) :
    Datatype(std::move(handle)) {}

Float::Float(const Datatype &datatype) :
    Datatype(datatype) {
  if (datatype.get_class() != Class::Float) {
    std::stringstream ss;
    ss << "Cannot create datatype::Float from " << get_class();
    throw std::runtime_error(ss.str());
  }
}


size_t Float::precision() const {
  size_t p = H5Tget_precision(static_cast<hid_t>(*this));
  if (p == 0) {
    error::Singleton::instance().throw_with_stack("Could not retrieve datatype precision");
  }
  return p;
}

void Float::precision(size_t precision) const {
  if (H5Tset_precision(static_cast<hid_t>(*this), precision) < 0) {
    std::stringstream ss;
    ss << "Could not set datatype precision to " << precision;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

size_t Float::offset() const {
  ssize_t p = H5Tget_offset(static_cast<hid_t>(*this));
  if (p < 0) {
    error::Singleton::instance().throw_with_stack("Could not retrieve datatype offset");
  }
  return signed2unsigned<size_t>(p);
}

void Float::offset(size_t offset) const {
  if (H5Tset_offset(static_cast<hid_t>(*this), offset) < 0) {
    std::stringstream ss;
    ss << "Could not set datatype offset to " << offset;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

Order Float::order() const {
  htri_t ret = H5Tget_order(static_cast<hid_t>(*this));
  if (ret > 4) {
    error::Singleton::instance().throw_with_stack("Could not retrieve datatype order");
  }
  return static_cast<Order>(ret);
}

void Float::order(Order order) const {
  if (H5Tset_order(static_cast<hid_t>(*this), static_cast<H5T_order_t>(order)) < 0) {
    std::stringstream ss;
    ss << "Could not set datatype order to " << order;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

const std::vector<Pad> Float::pad() const {
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

void Float::pad(Pad lsb, Pad msb) const {
  if (H5Tset_pad(static_cast<hid_t>(*this),
		 static_cast<H5T_pad_t>(lsb),
		 static_cast<H5T_pad_t>(msb)) < 0) {
    std::stringstream ss;
    ss << "Could not set datatype pad to (" << lsb << ", " << msb << ")" ;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

const std::vector<size_t> Float::fields() const {
  std::vector<size_t> fields(5);
  if (H5Tget_fields(static_cast<hid_t>(*this), &fields[0], &fields[1], &fields[2], &fields[3], &fields[4]) < 0) {
    error::Singleton::instance().throw_with_stack("Could not retrieve datatype fields");
  }
  return fields;
}

void Float::fields(size_t spos, size_t epos, size_t esize, size_t mpos, size_t msize) const {
  if (H5Tset_fields(static_cast<hid_t>(*this), spos, epos, esize, mpos, msize) < 0) {
    std::stringstream ss;
    ss << "Could not set datatype fields to ("
       << spos << ", " <<  epos << ", " <<  esize << ", " <<  mpos << ", " <<  msize << ")" ;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

size_t Float::ebias() const {
  size_t p = H5Tget_ebias(static_cast<hid_t>(*this));
  if (p == 0) {
    error::Singleton::instance().throw_with_stack("Could not retrieve datatype ebias");
  }
  return p;
}

void Float::ebias(size_t ebias) const {
  if (H5Tset_ebias(static_cast<hid_t>(*this), ebias) < 0) {
    std::stringstream ss;
    ss << "Could not set datatype ebias to " << ebias;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

Norm Float::norm() const {
  H5T_norm_t ret = H5Tget_norm(static_cast<hid_t>(*this));
  if (ret == H5T_NORM_ERROR) {
    error::Singleton::instance().throw_with_stack("Could not retrieve datatype norm");
  }
  return static_cast<Norm>(ret);
}

void Float::norm(Norm norm) const {
  if (H5Tset_norm(static_cast<hid_t>(*this), static_cast<H5T_norm_t>(norm)) < 0) {
    std::stringstream ss;
    ss << "Could not set datatype norm to " << norm;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

Pad Float::inpad() const {
  H5T_pad_t ret = H5Tget_inpad(static_cast<hid_t>(*this));
  if (ret == H5T_PAD_ERROR) {
    error::Singleton::instance().throw_with_stack("Could not retrieve datatype inpad");
  }
  return static_cast<Pad>(ret);
}

void Float::inpad(Pad inpad) const {
  if (H5Tset_inpad(static_cast<hid_t>(*this), static_cast<H5T_pad_t>(inpad)) < 0) {
    std::stringstream ss;
    ss << "Could not set datatype inpad to " << inpad;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

} // namespace datatype
} // namespace hdf5
