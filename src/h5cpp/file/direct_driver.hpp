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

#if ( defined(_DOXYGEN_) || defined(H5_HAVE_DIRECT) )
namespace hdf5 {
namespace file {

//!
//! \brief direct write without buffering (*for hdf5 compiled with H5_HAVE_DIRECT*)
//!
class DLL_EXPORT DirectDriver : public Driver
{
  public:
    //!
    //! \brief default constructor
    //!
    DirectDriver();

    //!
    //! \brief constructor
    //!
    DirectDriver(size_t alignment,size_t block_size,size_t copy_buffer_size);

    //!
    //! \brief copy constructor
    //!
    DirectDriver(const DirectDriver &) = default;

    //!
    //! \brief get alignment value
    //!
    size_t alignment() const noexcept;

    //!
    //! \brief set alignment value
    //!
    //! \throws std::runtime_error in case of an error
    //! \param value the new alignment value
    //!
    void alignment(size_t value);

    //!
    //! \brief get block size
    //!
    size_t block_size() const noexcept;

    //!
    //! \brief set block size
    //! \throws std::runtime_error in case of a failure
    //! \param value the new block size
    //!
    void block_size(size_t value);

    //!
    //! \brief get copy buffer size
    //!
    size_t copy_buffer_size() const noexcept;

    //!
    //! \brief set copy buffer size
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param value the new copy buffer size
    //!
    void copy_buffer_size(size_t value);

    virtual void operator()(const property::FileAccessList &fapl) const;
    virtual DriverID id() const noexcept;

  private:
    size_t alignment_;
    size_t block_size_;
    size_t copy_buffer_size_;

};



} // namespace file
} // namespace hdf5
#endif
