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
#pragma once

#include <h5cpp/dataspace/type.hpp>
#include <h5cpp/core/object_handle.hpp>
#include <h5cpp/core/types.hpp>
#include <h5cpp/dataspace/selection_manager.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace dataspace {

//!
//! \brief dataspace base class
//!
class DLL_EXPORT Dataspace {
 public:
  //!
  //! \brief destructor
  //!
  //! Has to be virtual due to inheritance
  //!
  virtual ~Dataspace();

  //!
  //! \brief default constructor
  //!
  //! The default constructor will leave the dataspace as an
  //! invalid HDF5 object. Default construction is however necessary
  //! for using a Dataspace with certain C++ STL containers.
  //!
  //! \sa is_valid()
  //!
  Dataspace();

  //!
  //! \brief constructor
  //!
  //! Constructs a dataspace object from an rvalue reference to an
  //! HDF5 handle. The class will take full ownership of the handle.
  //!
  //! \param handle rvalue reference to the handle
  //!
  Dataspace(ObjectHandle &&handle);

  //!
  //! \brief move constructor
  //!
  //! Use default implementation here.
  //!
  Dataspace(Dataspace &&type) = default;

  //!
  //! \brief copy constructor
  //!
  Dataspace(const Dataspace &space);

  //!
  //! \brief copy assignment
  //!
  Dataspace &operator=(const Dataspace &space);

  //!
  //! \brief number of elements in the dataspace
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  virtual hssize_t size() const;

  //!
  //! \brief allows explicit conversion to hid_t
  //!
  //! This function is mainly used by \c static_cast for explicit
  //! conversion to \c hid_t.
  //!
  //! \code
  //! Dataspace space();
  //! hid_t id = static_cast<hid_t>(space);
  //! \endcode
  //!
  explicit operator hid_t() const {
    return static_cast<hid_t>(handle_);
  }

  //!
  //! \brief get the type of the dataspace
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  Type type() const;

  //!
  //! \brief check validity of the dataspace
  //!
  //! Returns true if the dataspace is a valid HDF5 object. This member
  //! function should return true in most cases. However, in cases
  //! that the dataspace was
  //!
  //! \li default constructed
  //! \li or the close() method was called before
  //!
  //! this function will return false.
  //!
  //! \throws std::runtime_error in case of a failure
  //!
  //! \return true if valid, false if invalid
  //! \sa Dataspace()
  //!
  bool is_valid() const;

  //!
  //! \brief access to selection manager
  //!
  //! This public member provides access to the selection manager
  //! of the dataspace. See the SelectionManager documentation for
  //! interface details.
  //!
  //! \sa SelectionManager
  SelectionManager selection;

 protected:
  Dataspace(Type type);
 private:
  ObjectHandle handle_;

  //!
  //! @brief helper for copy assignment and copy constructor
  //!
  void swap(const Dataspace &space);

};

} // namespace dataspace
} // namespace hdf5
