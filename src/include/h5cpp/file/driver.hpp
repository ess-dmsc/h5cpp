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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Nov 6, 2017
//
#pragma once
#include <memory>
#include "../property/file_access_list.hpp"


namespace hdf5 {
namespace file {

//!
//! \brief enumeration to determine the file driver
//!
enum class DriverID : unsigned {

  POSIX = 1,
  DIRECT = 2,
  MEMORY = 3,
  MPI    = 4
};

//!
//! \brief abstract class for file drivers
//!
//! Driver classes in h5cpp do not hold a real reference to a driver object.
//! They rather store information about how to setup the driver. This is
//! mainly due to the fact that we are currently accessing the drivers
//! only via the file access property list.
//!
class Driver
{
  public:
    //!
    //! \brief unique pointer type
    //!
    using UniquePointer = std::unique_ptr<Driver>;

    virtual ~Driver(){}

    //!
    //! \brief set a driver
    //!
    //! Sets a driver to a particular file access property list.
    //!
    virtual void operator()(const property::FileAccessList &fapl) const = 0;

    //!
    //! \brief get driver ID
    //!
    //! Return the ID of a particular driver.
    //1
    virtual DriverID id() const noexcept = 0;
};

} // namespace file
} // namespace hdf5
