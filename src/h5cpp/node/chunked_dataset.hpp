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
// Created on: Nov 17, 2017
//
#pragma once

#include <h5cpp/node/dataset.hpp>

namespace hdf5 {
namespace node {

//!
//! \brief dataset with chunked layout
//!
//! This class provides an convenient interface to a chunked dataset. As a
//! matter of fact the only thing added here is a convenient constructor where
//! the chunk shape can be passed as an additional argument.
//!
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
class DLL_EXPORT ChunkedDataset : public Dataset
{
  public:
    //!
    //! \brief default constructor
    //!
    //! Required for STL compliance. We can use the compiler provided default
    //! implementation here.
    //!
    ChunkedDataset() = default;

    //!
    //! \brief copy constructor
    //!
    //! Required for STL compliance. We can use the compiler provided default
    //! implementation here.
    //!
    ChunkedDataset(const ChunkedDataset &) = default;

    //!
    //! \brief constructor
    //!
    //! As for all dataset constructors, references to the required property
    //! list can be passed as optional arguments. There are two things worth
    //! noting here
    //!
    //! \li the dataspace for a chunked dataset must be a simple dataspace
    //! \li independent of the configuration of an eventually user provided
    //!     dataset creation property list, the layout of the dataset will be
    //!     chunked with the provided chunk shape.
    //!
    //! The user provided dataset creation property list will not be changed.
    //!
    //! \throws std::runtime_error in case of a failure
    //!
    //! \param base the base object for the dataset creation
    //! \param path the path to the new dataset
    //! \param type optional reference to a datatype
    //! \param space optional reference to a dataspace
    //! \param chunk_shape reference to the chunk shape
    //! \param lcpl optional reference to a link creation property list
    //! \param dcpl optional reference to a dataset creation property list
    //! \param dapl optional reference to a dataset access property list
    //!
    ChunkedDataset(const Group &base,const Path &path,
                   const datatype::Datatype &type,
                   const dataspace::Simple &space,
                   const Dimensions &chunk_shape,
                   const property::LinkCreationList &lcpl = property::LinkCreationList(),
                   const property::DatasetCreationList &dcpl = property::DatasetCreationList(),
                   const property::DatasetAccessList &dapl = property::DatasetAccessList());


};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

} // namespace node
} // namespace hdf5
