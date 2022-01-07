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

#include <h5cpp/core/filesystem.hpp>
#include <h5cpp/property/property_list.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace property {

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
//!
//! \brief link access property list
//!
class DLL_EXPORT LinkAccessList : public List {
 public:
  //!
  //! \brief default constructor
  //!
  LinkAccessList();

  explicit LinkAccessList(ObjectHandle &&handle);

  //!
  //! \brief get maximum number of link traversals
  //!
  size_t maximum_link_traversals() const;

  //!
  //! \brief set maximum number of link traversals
  //!
  void maximum_link_traversals(size_t size) const;

  //!
  //! \brief get external link prefix
  //!
  //! Returns the prefix prepended to every path in an external link.
  //!
  //! \throws std::runtime_error in case of a failure
  //! \return prefix as an instance of fs
  //! \sa external_link_prefix
  fs::path external_link_prefix() const;

  //!
  //! \brief set external link prefix
  //!
  //! Sets the external link prefix for a path. As the this information is
  //! stored internally and must be kept valid throughout the lifetime of the
  //! property list this method cannot be const.
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  //! \param path reference to a fs path containing the prefix
  //! \sa external_link_prefix
  void external_link_prefix(const fs::path &path);

 protected:
  //!
  //! \brief constructor
  //!
  //! This protected constructor is used for the construction of child-classes.
  //!
  LinkAccessList(const Class &plist_class);
 private:

  //!
  //! \brief local storage for the external link prefix
  //!
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable:4251)
#endif
  std::string elink_prefix_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
};

#ifdef __clang__
#pragma clang diagnostic pop
#endif

} // namespace property
} // namespace hdf5
