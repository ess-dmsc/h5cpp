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
// Created on: Aug 28, 2017
//
#pragma once

#include <h5cpp/property/property_list.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace property {

#ifdef WITH_MPI
enum class MPITransferMode : std::underlying_type<H5FD_mpio_xfer_t>::type
{
  INDEPENDENT = H5FD_MPIO_INDEPENDENT,
  COLLECTIVE  = H5FD_MPIO_COLLECTIVE
};

std::ostream &operator<<(std::ostream &stream,const MPITransferMode &mode);

enum class MPIChunkOption : std::underlying_type<H5FD_mpio_chunk_opt_t>::type
{
  ONE_LINK_CHUNKED = H5FD_MPIO_CHUNK_ONE_IO,
  MULTI_CHUNK      = H5FD_MPIO_CHUNK_MULTI_IO
};

std::ostream &operator<<(std::ostream &stream,const MPIChunkOption &option);
#endif

class DLL_EXPORT DatasetTransferList : public List
{
  public:
    DatasetTransferList();
    ~DatasetTransferList();

#ifdef WITH_MPI
    void mpi_transfer_mode(MPITransferMode mode) const;
    MPITransferMode mpi_transfer_mode() const;

    void mpi_chunk_option(MPIChunkOption option) const;
    MPIChunkOption mpi_chunk_option() const;


#endif
};

} // namespace property
} // namespace hdf5
