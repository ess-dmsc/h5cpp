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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 28, 2017
//

#include <h5cpp/property/dataset_transfer.hpp>
#include <h5cpp/property/property_class.hpp>

namespace hdf5 {
namespace property {

DatasetTransferList::DatasetTransferList():
    List(kDatasetXfer)
{}

DatasetTransferList::~DatasetTransferList()
{}

#ifdef WITH_MPI

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
#endif
std::ostream &operator<<(std::ostream &stream,const MPITransferMode &mode)
{
  switch(mode)
  {
    case MPITransferMode::INDEPENDENT:
      return stream<<"INDEPENDENT";
    case MPITransferMode::COLLECTIVE:
      return stream<<"COLLECTIVE";
  }
}
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
#endif
std::ostream &operator<<(std::ostream &stream,const MPIChunkOption &option)
{
  switch(option)
  {
    case MPIChunkOption::ONE_LINK_CHUNKED:
      return stream<<"ONE_LINK_CHUNKED";
    case MPIChunkOption::MULTI_CHUNK:
      return stream<<"MULTI_CHUNK";
  }
}
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif


void DatasetTransferList::mpi_transfer_mode(MPITransferMode mode) const
{
  if(H5Pset_dxpl_mpio(static_cast<hid_t>(*this),
                      static_cast<H5FD_mpio_xfer_t>(mode))<0)
  {
    throw std::runtime_error("Failure to set MPI transfer mode!");
  }

}


MPITransferMode DatasetTransferList::mpi_transfer_mode() const
{
  H5FD_mpio_xfer_t mode;
  if(H5Pget_dxpl_mpio(static_cast<hid_t>(*this),&mode)<0)
  {
    throw std::runtime_error("Failure to obtain the MPI transfer mode!");
  }
  return static_cast<MPITransferMode>(mode);
}

void DatasetTransferList::mpi_chunk_option(MPIChunkOption option) const
{
  if(H5Pset_dxpl_mpio_chunk_opt(static_cast<hid_t>(*this),
                                static_cast<H5FD_mpio_chunk_opt_t>(option))<0)
  {
    throw std::runtime_error("Failure to set MPI chunk option!");
  }
}

MPIChunkOption DatasetTransferList::mpi_chunk_option() const
{

}


#endif


} // namespace property
} // namespace hdf5
