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
// Created on: Nov 16, 2017
//
#pragma once

#include <h5cpp/node/dataset.hpp>
#include <h5cpp/property/virtual_data_map.hpp>

namespace hdf5 {
namespace node {

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wweak-vtables"
#endif
//!
//! \brief virtual dataset class
//!
//! This class provides a special constructor which only takes arguments
//! required to construct a virtual dataset.
//!
class DLL_EXPORT VirtualDataset : public Dataset
{
  public:
    //!
    //! \brief default constructor
    //!
    //! This constructor is required for compatibility with STL containers.
    //! We can use the compiler provided version.
    VirtualDataset () = default;

    //!
    //! \brief copy constructor
    //!
    //! This constructor is required for compatibility with STL containers.
    //! We can use the compiler provided version here.
    //!
    VirtualDataset(const VirtualDataset &) = default;

    //!
    //! \brief constructor
    //!
    VirtualDataset(const Group &base,const Path &path,
                   const datatype::Datatype &type,
                   const dataspace::Dataspace &space,
                   const property::VirtualDataMaps &vds_maps,
                   const property::LinkCreationList &lcpl = property::LinkCreationList(),
                   const property::DatasetCreationList &dcpl = property::DatasetCreationList(),
                   const property::DatasetAccessList &dapl = property::DatasetAccessList());



};
#ifdef __clang__
#pragma clang diagnostic pop
#endif

} // namespace node
} // namespace hdf5
