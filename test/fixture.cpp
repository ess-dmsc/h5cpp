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
// Created on: Oct 08, 2017
//
#include "fixture.hpp"
#include <h5cpp/property/file_creation.hpp>
#include <h5cpp/property/file_access.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/core/filesystem.hpp>

using namespace hdf5;

void BasicFixture::SetUp()
{
  property::FileCreationList fcpl;
  property::FileAccessList fapl;

  fcpl.link_creation_order(property::CreationOrder().enable_indexed());
  fapl.library_version_bounds(property::LibVersion::LATEST,
                              property::LibVersion::LATEST);

#if H5_VERSION_GE(1,10,0)
  //need this for SWMR
  fapl.library_version_bounds(property::LibVersion::LATEST,property::LibVersion::LATEST);
#endif

  file_ = file::create("test_file.h5",file::AccessFlags::TRUNCATE,fcpl,fapl);
  root_ = file_.root();
}


