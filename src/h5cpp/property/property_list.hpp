//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
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

#pragma once

#include <type_traits>

#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/core/object_handle.hpp>
#include <h5cpp/property/property_class.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace property {

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wold-style-cast"
#endif
const decltype(H5P_DEFAULT) kDefault = H5P_DEFAULT;
#ifdef __clang__
#pragma clang diagnostic pop
#endif

class Class;

//!
//! \brief base class for property lists
//!
class DLL_EXPORT List {
 public:
  //!
  //! \brief constructor
  //!
  //! @param plist_class reference to the property list class
  //!
  explicit List(const Class &plist_class);

  //!
  //! \brief copy constructor
  //! @param plist reference to the original property list
  //!
  List(const List &plist);

  //!
  //! \brief constructor
  //!
  //! Construct a property list from a handler object. This constructor is
  //! particularly useful in situations where we retrieve the handler of
  //! a property list from a C-API function.
  //!
  //! \throws std::runtime_error in case of a failure
  //! \param handle r-value reference to the handle object
  //!
  explicit List(ObjectHandle &&handle);

  //!
  //! \brief copy assignment
  //!
  List &operator=(const List &type);

  //!
  //! \brief destructor
  //!
  virtual ~List();

  List &operator=(List &&type) = default;
  List(List &&type) = default;

  //!
  //! \brief return property list class
  //!
  //! Return an instance of the property list class the list belongs to.
  //!
  //! \return class instance
  Class get_class() const;

  //!
  //! \brief conversion operator
  //!
  //! Use this operator to obtain the actual HDF5 handler to the list
  //! instance.
  //!
  explicit operator hid_t() const {
    return static_cast<hid_t>(handle_);
  }

 private:
  ObjectHandle handle_;

};

}  // namespace property
}  // namespace hdf5
