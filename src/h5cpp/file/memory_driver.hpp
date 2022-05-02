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

#include <h5cpp/file/driver.hpp>

namespace hdf5 {
namespace file {

//!
//! \brief memory file driver
//!
//! Using this driver HDF5 writes the file not to disk but in memory which
//! can reduce the overhead from disk IO. If backing_store option is
//! enabled the file will be written to disk with the same file name used
//! to create the file in memory.
//!
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wpadded"
#endif
class DLL_EXPORT MemoryDriver : public Driver
{
  public:
    //!
    //! \brief default constructor
    //!
    //! Sets the increment to 1MByte and backing store to false.
    //!
    MemoryDriver() noexcept;

    //!
    //! \brief constructor
    //!
    //! \param increment number of bytes used to increment the memory buffer
    //!                  if it runs out of storage
    //! \param backing_store enable disk storage after file close
    //!
    MemoryDriver(size_t increment,bool backing_store) noexcept;

    //!
    //! \brief copy constructor
    //!
    //! Use the default implementation here.
    //!
    MemoryDriver(const MemoryDriver &) = default;


    //!
    //! \brief get backing store status
    //!
    bool backing_store() const noexcept;

    //!
    //! \brief set backing store status
    //!
    void backing_store(bool value) noexcept;

    //!
    //! \brief get increment value
    //!
    size_t increment() const noexcept;

    //!
    //! \brief set increment
    //!
    void increment(size_t value);

    virtual void operator()(const property::FileAccessList &fapl) const override;
    virtual DriverID id() const noexcept override;



  private:
    size_t increment_;
    bool backing_store_;

};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

} // namespace file
} // namespace hdf5
