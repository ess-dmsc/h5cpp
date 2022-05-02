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

#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/file/mpi_driver.hpp>
#include <h5cpp/property/file_access.hpp>
#include <h5cpp/error/error.hpp>

namespace hdf5 {
namespace file {

#ifdef H5CPP_WITH_MPI

MPIDriver::MPIDriver(MPI_Comm comm,MPI_Info info):
    comm_(comm),
    info_(info)
{}

void MPIDriver::operator()(const property::FileAccessList &fapl) const
{
  if(H5Pset_fapl_mpio(static_cast<hid_t>(fapl),comm_,info_)<0)
  {
    error::Singleton::instance().throw_with_stack("Failure setting MPI driver!");
  }
}

DriverID MPIDriver::id() const noexcept
{
  return DriverID::MPI;
}

#endif

} // namespace file
} // namespace hdf5
