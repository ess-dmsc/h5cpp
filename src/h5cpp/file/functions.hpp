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
// Created on: Sep 8, 2017
//
#pragma once

#include <h5cpp/core/filesystem.hpp>
#include <h5cpp/file/file.hpp>
#include <h5cpp/file/types.hpp>
#include <h5cpp/property/file_creation.hpp>
#include <h5cpp/property/file_access.hpp>
#include <h5cpp/core/windows.hpp>

namespace hdf5 {
namespace file {

//!
//! \brief create a new file
//!
//! \param path the path to the new file
//! \param flags HDF5 file creation flags
//! \param fcpl reference to a file creation property list
//! \param fapl reference to a file access property list
//! \throws std::runtime_error in case of a failure
//! \return new instance of File
//! \sa AccessFlags
//! \sa FileCreationList
//! \sa FileAccessList
//!
DLL_EXPORT File create(const fs::path &path,
                       AccessFlags flags = AccessFlags::EXCLUSIVE,
                       const property::FileCreationList &fcpl = property::FileCreationList(),
                       const property::FileAccessList &fapl = property::FileAccessList());
DLL_EXPORT File create(const fs::path &path,
                       AccessFlagsBase flags,
                       const property::FileCreationList &fcpl = property::FileCreationList(),
                       const property::FileAccessList &fapl = property::FileAccessList());

//!
//! \brief open an existing file
//!
//! \param path the path to the file to open
//! \param flags file open flags
//! \param fapl reference to a file access property list
//! \throws std::runtime_error in case of a failure
//! \return a new File instance
//! \sa AccessFlags
//! \sa FileAccessList
//!
DLL_EXPORT File open(const fs::path &path,
                     AccessFlags flags = AccessFlags::READONLY,
                     const property::FileAccessList &fapl = property::FileAccessList());
DLL_EXPORT File open(const fs::path &path,
                     AccessFlagsBase flags,
                     const property::FileAccessList &fapl = property::FileAccessList());

//!
//! \brief check if the file reference by the path is an HDF5 file
//!
//! \param path reference to the files path
//! \throws std::runtime_error in case of a failure
//! \return true if the path references an HDF5 file, false otherwise
//!
DLL_EXPORT bool is_hdf5_file(const fs::path &path);

} // namespace file
} // namespace hdf5




