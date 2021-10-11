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

#include <h5cpp/property/property_list.hpp>
#include <h5cpp/property/creation_order.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace property {

class DLL_EXPORT ObjectCreationList : public List {
 public:
  //!
  //! \brief constructor
  //!
  ObjectCreationList();
  ObjectCreationList(const ObjectCreationList &) = default;

  //!
  //! \brief destructor
  //!
  virtual ~ObjectCreationList() override;

  explicit ObjectCreationList(ObjectHandle &&handle);

  //!
  //! \brief enable object time tracking
  //!
  //! Activates the time tracking feature on objects in the file.
  //!
  //! \sa disable_time_tracking
  //! \sa time_tracking
  void enable_time_tracking() const;

  //!
  //! \brief disable object time tracking
  //! \sa enable_time_tracking
  //! \sa time_tracking
  void disable_time_tracking() const;

  //!
  //! \brief return time tacking status
  //!
  //! Queries the current status of the time tracking feature. This method
  //! returns true if time tracking is activate and false otherwise.
  //!
  //! \throws std::runtime_errr in case of an error
  //!
  //! @return true if time tracking is active, false otherwise
  //! \sa enable_time_tracking
  //! \sa disable_time_tracking
  bool time_tracking() const;

  //!
  //! \brief set the attribute creation order
  //!
  //! Set the attribute creation order flags which will be used for all
  //! objects.
  //!
  //! @param order requested attribute creation order
  //! \sa CreationOrder
  //! \sa attribute_creation_order()
  void attribute_creation_order(const CreationOrder &order) const;

  //!
  //! \brief retrieve current attribute creation order
  //!
  //! @return current attribute creation order
  //! \sa attribute_creation_order
  //! \sa CreationOrder
  CreationOrder attribute_creation_order() const;

  //!
  //! \brief set storage layout thresholds
  //!
  //! @param max_compact maximum number above which dense storage will be
  //!                    used
  //! @param min_dense minimum number below which compact storage will be
  //!                  used
  //! \sa attribute_storage_maximum_compact
  //! \sa attribute_storage_minimum_dense
  void attribute_storage_thresholds(unsigned max_compact, unsigned min_dense) const;

  //!
  //! \brief get upper threshold for compact storage
  //!
  //! \return return the upper threshhold for which compat storage is used
  unsigned attribute_storage_maximum_compact() const;

  //!
  //! \brief get lower threshold for dense threshold
  unsigned attribute_storage_minimum_dense() const;

 protected:
  ObjectCreationList(const Class &plist_class);
 private:
  void get_attribute_phase_change_(unsigned &max_compact,
                                   unsigned &min_dense,
                                   const std::string &error_message) const;
};

} // namespace property
} // namespace hdf5

