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
#include <h5cpp/core/hdf5_capi.hpp>

namespace hdf5 {
namespace file {

#if ( defined(_DOXYGEN_) || defined(H5CPP_WITH_MPI) )

//!
//! \brief class for the MPI driver (*for hdf5 with compiled MPI*)
//!
class DLL_EXPORT MPIDriver : public Driver
{
  public:
    MPIDriver(MPI_Comm comm,MPI_Info info);
    MPIDriver(const MPIDriver &) = default;

    virtual void operator()(const property::FileAccessList &fapl) const;
    virtual DriverID id() const noexcept;
  private:

    MPI_Comm comm_;
    MPI_Info info_;
};

#endif

} // namespace file
} // namespace hdf5
