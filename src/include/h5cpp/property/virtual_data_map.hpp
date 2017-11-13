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
// Created on: Nov 10, 2017
//
#pragma once

#include <boost/filesystem.hpp>
#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/dataspace/view.hpp>
#include <h5cpp/property/dataset_creation.hpp>
#include <h5cpp/path.hpp>

namespace hdf5 {
namespace property {


//!
//! \brief data mapping for virtual datasets
//!
//! This class describes the mapping of data between the dataspace of a
//! virtual dataset and the source dataset.
//!
class VirtualDataMap {
  public:
    //!
    //! \brief default constructor
    //!
    //! Need this for STL container compliance but can rely on the compiler
    //! provided default version.
    //!
    VirtualDataMap() = default;

    //!
    //! \brief copy constructor
    //!
    //! Need this for STL container compilance but can rely on the compiler
    //! provided default version.
    //!
    VirtualDataMap(const VirtualDataMap &) = default;

    //!
    //! \brief constructor
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param target_space dataspace with the selection where to view the
    //!                     source data
    //! \param source_file path to the source file
    //! \param source_dataset path to the source dataset
    //! \param source_space dataspace with selection of the source dataset
    //!
    VirtualDataMap(const dataspace::View &target_view,
                   const boost::filesystem::path &source_file,
                   const hdf5::Path &source_dataset,
                   const dataspace::View &source_view);


    //!
    //! \brief apply mapping to a dataset creation list
    //!
    //! \throws std::runtime_error in case of a failure
    //! \param dcpl reference to the dataset creation list onto which the
    //!             mapping should be applied
    //!
    void operator()(const property::DatasetCreationList &dcpl) const;


  private:
    dataspace::View         target_view_;
    boost::filesystem::path source_file_;
    hdf5::Path              source_dataset_;
    dataspace::View         source_view_;


};

} // namespace property
} // namespace hdf5
