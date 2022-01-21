
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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Aug 28, 2017
//

#include <h5cpp/property/dataset_transfer.hpp>
#include <h5cpp/property/property_class.hpp>
#include <h5cpp/error/error.hpp>
#include <sstream>

namespace hdf5 {
namespace property {

DatasetTransferList::DatasetTransferList() :
    List(kDatasetXfer) {}

DatasetTransferList::~DatasetTransferList() {}

DatasetTransferList::DatasetTransferList(ObjectHandle &&handle, bool do_check):
    List(std::move(handle)) {
 if (do_check && get_class() != kDatasetXfer) {
     std::stringstream ss;
     ss << "Cannot create property::DatasetTransferList from " << get_class();
     throw std::runtime_error(ss.str());
 }
}

#ifdef H5CPP_WITH_MPI

std::ostream &operator<<(std::ostream &stream,const MPITransferMode &mode)
{
  switch(mode)
  {
    case MPITransferMode::Independent:
      return stream<<"INDEPENDENT";
    case MPITransferMode::Collective:
      return stream<<"COLLECTIVE";
  }
  return stream;
}


std::ostream &operator<<(std::ostream &stream,const MPIChunkOption &option)
{
  switch(option)
  {
    case MPIChunkOption::OneLinkChunked:
      return stream<<"ONE_LINK_CHUNKED";
    case MPIChunkOption::MultiChunk:
      return stream<<"MULTI_CHUNK";
  }
  return stream;
}

void DatasetTransferList::mpi_transfer_mode(MPITransferMode mode) const
{
  if(H5Pset_dxpl_mpio(static_cast<hid_t>(*this),
                      static_cast<H5FD_mpio_xfer_t>(mode))<0)
  {
    error::Singleton::instance().throw_with_stack("Failure to set MPI transfer mode!");
  }

}


MPITransferMode DatasetTransferList::mpi_transfer_mode() const
{
  H5FD_mpio_xfer_t mode;
  if(H5Pget_dxpl_mpio(static_cast<hid_t>(*this),&mode)<0)
  {
    error::Singleton::instance().throw_with_stack("Failure to obtain the MPI transfer mode!");
  }
  return static_cast<MPITransferMode>(mode);
}

void DatasetTransferList::mpi_chunk_option(MPIChunkOption option) const
{
  if(H5Pset_dxpl_mpio_chunk_opt(static_cast<hid_t>(*this),
                                static_cast<H5FD_mpio_chunk_opt_t>(option))<0)
  {
    error::Singleton::instance().throw_with_stack("Failure to set MPI chunk option!");
  }
}

// TODO implement this properly
MPIChunkOption DatasetTransferList::mpi_chunk_option() const
{
  throw std::runtime_error("DatasetTransferList::mpi_chunk_option() is not implemented in h5cpp!");
}


#endif

} // namespace property
} // namespace hdf5
