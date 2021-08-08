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
// Created on: Nov 10, 2017
//
#pragma once

#include <h5cpp/core/filesystem.hpp>
#include <h5cpp/dataspace/dataspace.hpp>
#include <h5cpp/dataspace/view.hpp>
#include <h5cpp/property/dataset_creation.hpp>
#include <h5cpp/core/path.hpp>
#include <h5cpp/core/windows.hpp>
#include <vector>

namespace hdf5 {
namespace property {

//!
//! \brief data mapping for virtual datasets
//!
//! This class describes the mapping of data between the dataspace of a
//! virtual dataset and the source dataset.
//!
class DLL_EXPORT VirtualDataMap {
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
  //! \param target_view dataspace view with the selection where to view the
  //!                     source data
  //! \param source_file path to the source file
  //! \param source_dataset path to the source dataset
  //! \param source_view dataspace view with selection of the source dataset
  //!
  VirtualDataMap(const dataspace::View &target_view,
                 const fs::path &source_file,
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
  dataspace::View target_view_;
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
  fs::path source_file_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
  hdf5::Path source_dataset_;
  dataspace::View source_view_;

};

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
//!
//! \brief utility container for virtual data maps
//!
//! This is a one to one derived type from std::vector in order to provide
//! a convenient container for virtual data maps.
//! The interface is exactly the same as for std::vector.
//!
class DLL_EXPORT VirtualDataMaps : public std::vector<VirtualDataMap> {
#ifdef _MSC_VER
#pragma warning(pop)
#endif
 public:
  //
  // pull in std::vector constructors
  //
  using std::vector<VirtualDataMap>::vector;
};

} // namespace property
} // namespace hdf5
