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
// Created on: Aug 17, 2017
//

#include <h5cpp/property/object_creation.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5 {
namespace property {

//============================================================================
// implementation of private member functions
//============================================================================

void ObjectCreationList::get_attribute_phase_change_(unsigned &max_compact,
                                                     unsigned &min_dense,
                                                     const std::string &error_message) const {
  if (H5Pget_attr_phase_change(static_cast<hid_t>(*this), &max_compact, &min_dense) < 0) {
    error::Singleton::instance().throw_with_stack(error_message);
  }
}

//============================================================================
// implementation of protected member functions
//============================================================================

ObjectCreationList::ObjectCreationList(const Class &plist_class) :
    List(plist_class) {}

//============================================================================
// implementation of public member functions
//============================================================================
ObjectCreationList::ObjectCreationList() :
    List(kObjectCreate) {}

ObjectCreationList::ObjectCreationList(ObjectHandle &&handle) :
    List(std::move(handle)) {
  if ((get_class() != kObjectCreate) &&
      (get_class() != kFileCreate) &&
      (get_class() != kDatatypeCreate) &&
      (get_class() != kDatasetCreate) &&
      (get_class() != kGroupCreate)) {
    std::stringstream ss;
    ss << "Cannot create property::ObjectCreationList from " << get_class();
    throw std::runtime_error(ss.str());
  }
}

ObjectCreationList::~ObjectCreationList() {}

void ObjectCreationList::enable_time_tracking() const {
  if (H5Pset_obj_track_times(static_cast<hid_t>(*this), 1) < 0) {
    error::Singleton::instance().throw_with_stack("Failure to enable time tracking for objects!");
  }
}

void ObjectCreationList::disable_time_tracking() const {
  if (H5Pset_obj_track_times(static_cast<hid_t>(*this), 0) < 0) {
    error::Singleton::instance().throw_with_stack("Failure to disable time tracking for objects!");
  }
}

bool ObjectCreationList::time_tracking() const {
#if H5_VERSION_GE(1, 10, 0)
  hbool_t buffer = 0;
#else
  unsigned buffer = 0;
#endif
  if (H5Pget_obj_track_times(static_cast<hid_t>(*this), &buffer)) {
    error::Singleton::instance().throw_with_stack("Failure to retrieve object time tracking mode!");
  }
  if (buffer)
    return true;
  else
    return false;
}

void ObjectCreationList::attribute_creation_order(const CreationOrder &order) const {
  if (H5Pset_attr_creation_order(static_cast<hid_t>(*this), order) < 0) {
    error::Singleton::instance().throw_with_stack("Failure setting attribute creation order!");
  }
}

CreationOrder ObjectCreationList::attribute_creation_order() const {
  unsigned buffer = 0;
  if (H5Pget_attr_creation_order(static_cast<hid_t>(*this), &buffer) < 0) {
    error::Singleton::instance().throw_with_stack("Failure retrieving attribute creation order flags!");
  }

  return CreationOrder(buffer);
}

void ObjectCreationList::attribute_storage_thresholds(unsigned max_compact, unsigned min_dense) const {
  if (H5Pset_attr_phase_change(static_cast<hid_t>(*this), max_compact, min_dense) < 0) {
    error::Singleton::instance().throw_with_stack("Failure setting the compact to dense attribute "
                                                      "storage threshold!");
  }

}

unsigned ObjectCreationList::attribute_storage_maximum_compact() const {
  unsigned max_compact = 0,
      min_dense = 0;
  std::string error_message = "Failure retrieving the compact to dense attribute "
      "storage threshold!";
  get_attribute_phase_change_(max_compact, min_dense, error_message);

  return max_compact;
}

unsigned ObjectCreationList::attribute_storage_minimum_dense() const {
  unsigned max_compact = 0,
      min_dense = 0;
  std::string error_message = "Failure retrieving the dense to compact attribute "
      "storage threshold!";
  get_attribute_phase_change_(max_compact, min_dense, error_message);

  return min_dense;
}

} // namespace property
} // namespace hdf5
