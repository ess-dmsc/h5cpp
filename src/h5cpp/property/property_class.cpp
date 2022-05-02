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
// Created on: Aug 16, 2017
//

#include <h5cpp/property/property_class.hpp>
#include <h5cpp/error/error.hpp>

#include <iterator>
#include <cstring>
#include <sstream>

namespace hdf5 {
namespace property {

Class::Class(ObjectHandle &&handle) :
    handle_(handle) {
  if (handle_.is_valid() &&
      (handle_.get_type() != ObjectHandle::Type::PropertyListClass)) {
    std::stringstream ss;
    ss << "Could not construct property::Class from Handle, type="
       << handle_.get_type();
    throw std::runtime_error(ss.str());
  }
}

std::string Class::name() const {
  char *cptr = H5Pget_class_name(static_cast<hid_t>(handle_));
  if (!cptr) {
    return std::string();
  }

  std::string buffer(cptr, std::strlen(cptr));
  free(static_cast<void *>(cptr));
  return buffer;

}

bool operator==(const Class &lhs, const Class &rhs) {
  htri_t result = H5Pequal(static_cast<hid_t>(lhs), static_cast<hid_t>(rhs));
  if (result > 0)
    return true;
  else if (result == 0)
    return false;
  else
    error::Singleton::instance().throw_with_stack("Could check equality of property list classes");
#ifndef __clang__
  return {};
#endif
}

bool operator!=(const Class &lhs, const Class &rhs) {
  htri_t result = H5Pequal(static_cast<hid_t>(lhs), static_cast<hid_t>(rhs));
  if (result > 0)
    return false;
  else if (result == 0)
    return true;
  else
    error::Singleton::instance().throw_with_stack("Could check inequality of property list classes");
#ifndef __clang__
  return {};
#endif
}

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif
const Class kAttributeCreate = Class(ObjectHandle(H5P_ATTRIBUTE_CREATE,
                                                  ObjectHandle::Policy::WithoutWard));
const Class kDatasetAccess = Class(ObjectHandle(H5P_DATASET_ACCESS,
                                                ObjectHandle::Policy::WithoutWard));
const Class kDatasetCreate = Class(ObjectHandle(H5P_DATASET_CREATE,
                                                ObjectHandle::Policy::WithoutWard));
const Class kDatasetXfer = Class(ObjectHandle(H5P_DATASET_XFER,
                                              ObjectHandle::Policy::WithoutWard));
const Class kDatatypeAccess = Class(ObjectHandle(H5P_DATATYPE_ACCESS,
                                                 ObjectHandle::Policy::WithoutWard));
const Class kDatatypeCreate = Class(ObjectHandle(H5P_DATATYPE_CREATE,
                                                 ObjectHandle::Policy::WithoutWard));
const Class kFileAccess = Class(ObjectHandle(H5P_FILE_ACCESS,
                                             ObjectHandle::Policy::WithoutWard));
const Class kFileCreate = Class(ObjectHandle(H5P_FILE_CREATE,
                                             ObjectHandle::Policy::WithoutWard));
const Class kFileMount = Class(ObjectHandle(H5P_FILE_MOUNT,
                                            ObjectHandle::Policy::WithoutWard));
const Class kGroupAccess = Class(ObjectHandle(H5P_GROUP_ACCESS,
                                              ObjectHandle::Policy::WithoutWard));
const Class kGroupCreate = Class(ObjectHandle(H5P_GROUP_CREATE,
                                              ObjectHandle::Policy::WithoutWard));
const Class kLinkAccess = Class(ObjectHandle(H5P_LINK_ACCESS,
                                             ObjectHandle::Policy::WithoutWard));
const Class kLinkCreate = Class(ObjectHandle(H5P_LINK_CREATE,
                                             ObjectHandle::Policy::WithoutWard));
const Class kObjectCopy = Class(ObjectHandle(H5P_OBJECT_COPY,
                                             ObjectHandle::Policy::WithoutWard));
const Class kObjectCreate = Class(ObjectHandle(H5P_OBJECT_CREATE,
                                               ObjectHandle::Policy::WithoutWard));
const Class kStringCreate = Class(ObjectHandle(H5P_STRING_CREATE,
                                               ObjectHandle::Policy::WithoutWard));
#ifdef __clang__
#pragma clang diagnostic pop
#endif

std::ostream &operator<<(std::ostream &stream, const Class &c) {
  return stream << "AttributeClass(" << c.name() << ")";
}

} // namespace property_list
} // namespace hdf5



