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
// Created on: Oct 18, 2017
//
#pragma once

#include <h5cpp/hdf5.hpp>
#include <h5cpp/core/filesystem.hpp>

#include "../node_builder.hpp"

class SWMREnvironment
{
  private:
    hdf5::property::FileAccessList fapl_;
    hdf5::property::FileCreationList fcpl_;

  public:
    SWMREnvironment();

    const hdf5::property::FileAccessList &fapl() const noexcept
    {
      return fapl_;
    }

    const hdf5::property::FileCreationList &fcpl() const noexcept
    {
      return fcpl_;
    }

    hdf5::file::File create_file(const fs::path &file_path,
                           const NodeBuilder &builder) const;
    hdf5::file::File open_write_file(const fs::path &file_path) const;
    hdf5::file::File open_read_file(const fs::path &file_path) const;
};
