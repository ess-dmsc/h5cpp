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
// Created on: Aug 15, 2017
//

#include <h5cpp/property/property_list.hpp>
#include <h5cpp/error/error.hpp>

#include <sstream>

namespace hdf5 {
namespace property {

List::List(const Class &plist_class) :
    handle_(H5Pcreate(static_cast<hid_t>(plist_class))) {
}

List::List(ObjectHandle &&handle) :
    handle_(std::move(handle)) {
  if (handle_.is_valid() &&
      (handle_.get_type() != ObjectHandle::Type::PropertyList)) {
    std::stringstream ss;
    ss << "Could not construct property::List from Handle, type="
       << handle_.get_type();
    throw std::runtime_error(ss.str());
  }
}

List::List(const List &plist) {
  hid_t ret = H5Pcopy(static_cast<hid_t>(plist.handle_));
  if (0 > ret) {
    error::Singleton::instance().throw_with_stack("could not copy-construct property list");
  }
  handle_ = ObjectHandle(ret);
}

List &List::operator=(const List &plist) {
  hid_t ret = H5Pcopy(static_cast<hid_t>(plist.handle_));
  if (0 > ret) {
    error::Singleton::instance().throw_with_stack("could not copy property list");
  }
  handle_ = ObjectHandle(ret);
  return *this;
}

List::~List() {
}

Class List::get_class() const {
  return Class(ObjectHandle(H5Pget_class(static_cast<hid_t>(handle_))));
}

} // namespace property_list
} // namespace hdf5


