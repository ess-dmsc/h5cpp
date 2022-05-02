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
// Created on: Aug 24, 2017
//

#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5 {
namespace dataspace {

Dataspace::~Dataspace() {
}

Dataspace::Dataspace()
    : selection(*this), handle_() {}

Dataspace::Dataspace(ObjectHandle &&handle)
    : selection(*this), handle_(std::move(handle)) {
  if (handle_.is_valid() &&
      (handle_.get_type() != ObjectHandle::Type::Dataspace)) {
    std::stringstream ss;
    ss << "Could not construct Dataspace from Handle, type="
       << handle_.get_type();
    throw std::runtime_error(ss.str());
  }
}

Dataspace::Dataspace(const Dataspace &space)
    : selection(*this) {
  swap(space);
}

Dataspace &Dataspace::operator=(const Dataspace &space) {
  swap(space);
  return *this;
}

void Dataspace::swap(const Dataspace &space) {
  if(static_cast<hid_t>(space.handle_)) {
    hid_t ret = H5Scopy(static_cast<hid_t>(space.handle_));
    if (0 > ret) {
      error::Singleton::instance().throw_with_stack("could not copy Dataspace");
    }
    handle_ = ObjectHandle(ret);
  }
  else
    handle_ = ObjectHandle();
}

Dataspace::Dataspace(Type type)
    : selection(*this), handle_(ObjectHandle(H5Screate(static_cast<H5S_class_t>(type)))) {}

hssize_t Dataspace::size() const {
  hssize_t s = H5Sget_simple_extent_npoints(static_cast<hid_t>(*this));
  if (s < 0) {
    error::Singleton::instance().throw_with_stack("Failure retrieving the number of elements in the dataspace!");
  }
  return s;
}

Type Dataspace::type() const {
  if(static_cast<hid_t>(handle_)) {
    H5S_class_t ret = H5Sget_simple_extent_type(static_cast<hid_t>(*this));
    if (ret == H5S_NO_CLASS) {
      error::Singleton::instance().throw_with_stack("Failure to retrieve the dataspace type!");
    }
    return static_cast<Type>(ret);
  }
  return Type::NoData;

}

bool Dataspace::is_valid() const {
  return handle_.is_valid();
}

} // namespace dataspace
} // namespace hdf5
