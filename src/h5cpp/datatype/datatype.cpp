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
// Created on: Aug 15, 2017
//

#include <h5cpp/datatype/datatype.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5 {
namespace datatype {

Datatype::~Datatype() {
}

Datatype::Datatype(ObjectHandle &&handle)
    : handle_(std::move(handle)) {
  if (handle_.is_valid() &&
      (handle_.get_type() != ObjectHandle::Type::Datatype)) {
    std::stringstream ss;
    ss << "Could not construct Datatype from Handle, type="
       << handle_.get_type();
    throw std::runtime_error(ss.str());
  }
}

Datatype::Datatype(const Datatype &type) {
  swap(type);
}

Datatype &Datatype::operator=(const Datatype &type) {
  swap(type);
  return *this;
}

void Datatype::swap(const Datatype &type) {
  if(static_cast<hid_t>(type.handle_)) {
    hid_t ret = H5Tcopy(static_cast<hid_t>(type.handle_));
    if (0 > ret) {
      error::Singleton::instance().throw_with_stack("Could not copy Datatype");
    }
    handle_ = ObjectHandle(ret);
  }
  else
    handle_ = ObjectHandle();
}

Class Datatype::get_class() const {
  if(static_cast<hid_t>(handle_))
    return static_cast<Class>(H5Tget_class(static_cast<hid_t>(*this)));
  else
    return Class::None;
}

Datatype Datatype::super() const {
  hid_t id = H5Tget_super(static_cast<hid_t>(*this));
  if (id < 0) {
    error::Singleton::instance().throw_with_stack("Could not retrieve base data type");
  }
  return Datatype(ObjectHandle(id));
}

Datatype Datatype::native_type(Direction dir) const {
  hid_t id = H5Tget_native_type(static_cast<hid_t>(*this),
                                static_cast<H5T_direction_t>(dir));
  if (id < 0) {
    std::stringstream ss;
    ss << "Could not retrieve native type "
       << " (Direction=" << dir << ")";
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return Datatype(ObjectHandle(id));
}

bool Datatype::has_class(Class type_class) const {
  htri_t result = H5Tdetect_class(static_cast<hid_t>(*this),
                                  static_cast<H5T_class_t>(type_class));
  if (result < 0) {
    std::stringstream ss;
    ss << "Failure searching for type class " << type_class;
    error::Singleton::instance().throw_with_stack(ss.str());
  }

  if (result > 0)
    return true;
  else
    return false;
}

size_t Datatype::size() const {
  size_t s = H5Tget_size(static_cast<hid_t>(*this));
  if (s == 0) {
    error::Singleton::instance().throw_with_stack("Could not retrieve datatype size");
  }
  return s;
}

void Datatype::size(size_t size) const {
  if (H5Tset_size(static_cast<hid_t>(*this), size) < 0) {
    std::stringstream ss;
    ss << "Could not set datatype to " << size;
    error::Singleton::instance().throw_with_stack(ss.str());
  }
}

bool Datatype::is_valid() const {
  return handle_.is_valid();
}

bool operator==(const Datatype &lhs, const Datatype &rhs) {
  hid_t hlhs = static_cast<hid_t>(lhs);
  hid_t hrhs = static_cast<hid_t>(rhs);
  htri_t ret;
  if (hlhs != 0 && hrhs != 0)
    ret = H5Tequal(hlhs, hrhs);
  else
    ret = -1;
  if (0 > ret) {
    std::stringstream ss;
    ss << "Could not compare datatypes "
       << " LHS=" << lhs.get_class()
       << " RHS=" << rhs.get_class();
    error::Singleton::instance().throw_with_stack(ss.str());
  }
  return (ret > 0);
}

bool operator!=(const Datatype &lhs, const Datatype &rhs) {
  return !operator==(lhs, rhs);
}

} // namespace datatype
} // namespace hdf5
