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
// Created on: Aug 18, 2017
//
#pragma once

#include <h5cpp/property/object_creation.hpp>
#include <h5cpp/property/creation_order.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace property {

class DLL_EXPORT GroupCreationList : public ObjectCreationList {
 public:
  GroupCreationList();
  virtual ~GroupCreationList() override;

  explicit GroupCreationList(ObjectHandle &&handle);

  size_t local_heap_size_hint() const;
  void local_heap_size_hint(size_t size) const;

  unsigned estimated_number_of_links() const;
  void estimated_number_of_links(unsigned nlinks) const;

  unsigned estimated_link_name_length() const;
  void estimated_link_name_length(unsigned name_length) const;

  void link_creation_order(CreationOrder order) const;
  CreationOrder link_creation_order() const;

  void link_storage_thresholds(unsigned max_compact, unsigned min_dense) const;
  unsigned link_storage_maximum_compact() const;
  unsigned link_storage_minimum_dense() const;

 public:
  GroupCreationList(const Class &plist_class);

 private:

  void set_estimated_link_info_(unsigned nlinks, unsigned name_length,
                                const std::string &error_message) const;
  void get_estimated_link_info_(unsigned &nlinks, unsigned &name_length,
                                const std::string &error_message) const;

  void set_link_phase_change_(unsigned max_links, unsigned min_links,
                              const std::string &error_message) const;
  void get_link_phase_change_(unsigned &max_links, unsigned &min_links,
                              const std::string &error_message) const;

};

} // namespace property
} // namespace hdf5
