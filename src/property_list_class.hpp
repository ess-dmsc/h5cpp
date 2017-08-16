//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// h5cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// h5cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with h5cpp.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 16, 2017
//
#pragma once

extern "C"{
#include <hdf5.h>
}
#include "object_handle.hpp"


namespace hdf5{
namespace property_list{

//!
//! \brief property list class
//!
//! This class implements a wrapper around HDF5s property list classes.
//!
//! We have to implement this as a class as it is possible to define custom
//! classes on the fly. Though this functionality is currently not implemented
//! we are on the save side with a class implementation instead of an enumeration.
//!
class Class
{
  public:
    //!
    //! \brief default constructor
    //!
    Class() = default;

    //!
    //! \brief copy constructor
    //!
    Class(const Class &c) = default;

    //!
    //! \brief copy assignment
    //!
    Class &operator=(const Class &c) = default;

    //!
    //! \brief constructor
    //!
    Class(ObjectHandle &&handle);


    std::string name() const;
    Class parent() const;

    explicit operator hid_t() const
    {
      return static_cast<hid_t>(handle_);
    }


  private:
    ObjectHandle handle_;
};

bool operator==(const Class &lhs, const Class &rhs);
bool operator!=(const Class &lhs, const Class &rhs);

extern const Class kAttributeCreate;
extern const Class kDatasetAccess;
extern const Class kDatasetCreate;
extern const Class kDatasetXfer;
extern const Class kDatatypeAccess;
extern const Class kDatatypeCreate;
extern const Class kFileAccess;
extern const Class kFileCreate;
extern const Class kFileMount;
extern const Class kGroupAccess;
extern const Class kGroupCreate;
extern const Class kLinkAccess;
extern const Class kLinkCreate;
extern const Class kObjectCopy;
extern const Class kObjectCreate;
extern const Class kStringCreate;


} // namespace property_list
} // namespace hdf5
