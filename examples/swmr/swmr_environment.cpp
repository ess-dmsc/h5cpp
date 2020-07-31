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
// Created on: Oct 18, 2017
//

#include "swmr_environment.hpp"

using namespace hdf5;

SWMREnvironment::SWMREnvironment():
    fapl_(),
    fcpl_()
{
  fapl_.library_version_bounds(property::LibVersion::LATEST,
                               property::LibVersion::LATEST);
}

file::File SWMREnvironment::create_file(const fs::path &file_path,
                                        const NodeBuilder &builder) const
{
  file::File f = file::create(file_path,file::AccessFlags::TRUNCATE,
                              fcpl(),fapl());
  builder(f.root());
  return f;
}

file::File SWMREnvironment::open_write_file(const fs::path &file_path) const
{
  return file::open(file_path,file::AccessFlags::READWRITE |
                                 file::AccessFlags::SWMR_WRITE,fapl());
}

file::File SWMREnvironment::open_read_file(const fs::path &file_path) const
{
  return file::open(file_path,file::AccessFlags::READONLY |
                              file::AccessFlags::SWMR_READ,fapl());
}
