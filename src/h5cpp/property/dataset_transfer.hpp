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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Aug 28, 2017
//
#pragma once

#include <h5cpp/property/property_list.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace property {

#if (defined(_DOXYGEN_) || defined(H5CPP_WITH_MPI))
enum class MPITransferMode : std::underlying_type<H5FD_mpio_xfer_t>::type
{
  Independent = H5FD_MPIO_INDEPENDENT,
  Collective  = H5FD_MPIO_COLLECTIVE
};

std::ostream &operator<<(std::ostream &stream,const MPITransferMode &mode);

enum class MPIChunkOption : std::underlying_type<H5FD_mpio_chunk_opt_t>::type
{
  OneLinkChunked = H5FD_MPIO_CHUNK_ONE_IO,
  MultiChunk     = H5FD_MPIO_CHUNK_MULTI_IO
};

std::ostream &operator<<(std::ostream &stream,const MPIChunkOption &option);
#endif

//!
//! \brief class for a dataset transfer property list
//!
class DLL_EXPORT DatasetTransferList : public List {
 public:
  //!
  //! \brief constructor
  //!
  DatasetTransferList();
  //!
  //! \brief destructor
  //!
  ~DatasetTransferList() override;

  //!
  //! \brief constructor
  //!
  //! Construct a property list from a handler object. This constructor is
  //! particularly useful in situations where we retrieve the handler of
  //! a property list from a C-API function.
  //!
  //! \throws std::runtime_error in case of a failure
  //! \param handle r-value reference to the handle object
  //! \param do_check perform the object handle class type check
  //!
  explicit DatasetTransferList(ObjectHandle &&handle, bool do_check=true);

  //!
  //! \brief reference to const static DatasetTransferList object
  //!
  //! Return a reference to const static DatasetTransferList object. The object
  //! has to be constructed directly with H5P_DATASET_XFER because during
  //! the construction kDatasetXfer does not exist.
  //!
  static const DatasetTransferList &get() {
    const static DatasetTransferList & dtpl_ = DatasetTransferList(ObjectHandle(H5Pcreate(H5P_DATASET_XFER)), false);
    return dtpl_;
  }

#if (defined(_DOXYGEN_) || defined(H5CPP_WITH_MPI) )
  //!
  //! \brief set mpi transfer mode (*for hdf5 compiled with MPI*)
  //!

  void mpi_transfer_mode(MPITransferMode mode) const;
  //!
  //! \brief get mpi transfer mode (*for hdf5 compiled with MPI*)
  //!
  MPITransferMode mpi_transfer_mode() const;

  //!
  //! \brief set mpi chunk option (*for hdf5 compiled with MPI*)
  //!
  void mpi_chunk_option(MPIChunkOption option) const;
  //!
  //! \brief get mpi chunk option (*for hdf5 compiled with MPI*)
  //!
  MPIChunkOption mpi_chunk_option() const;


#endif
};

} // namespace property
} // namespace hdf5
