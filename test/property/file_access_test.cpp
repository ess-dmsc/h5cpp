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
// Created on: Aug 21, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/property/file_access.hpp>

namespace pl = hdf5::property;

TEST(FileAccessList, default_construction)
{
  pl::FileAccessList fapl;
  EXPECT_EQ(fapl.get_class(), pl::kFileAccess);
}

TEST(FileAccessList, library_version_bounds)
{
  pl::FileAccessList fapl;

  EXPECT_EQ(fapl.library_version_bound_low(), pl::LibVersion::EARLIEST);
  EXPECT_EQ(fapl.library_version_bound_high(), pl::LibVersion::LATEST);

  EXPECT_NO_THROW(fapl.library_version_bounds(pl::LibVersion::LATEST, pl::LibVersion::LATEST));
  EXPECT_EQ(fapl.library_version_bound_low(), pl::LibVersion::LATEST);
  EXPECT_EQ(fapl.library_version_bound_high(), pl::LibVersion::LATEST);

  EXPECT_NO_THROW(fapl.library_version_bounds(pl::LibVersion::EARLIEST, pl::LibVersion::LATEST));
  EXPECT_EQ(fapl.library_version_bound_low(), pl::LibVersion::EARLIEST);
  EXPECT_EQ(fapl.library_version_bound_high(), pl::LibVersion::LATEST);

  EXPECT_THROW(fapl.library_version_bounds(pl::LibVersion::EARLIEST, pl::LibVersion::EARLIEST),
               std::runtime_error);

  EXPECT_THROW(fapl.library_version_bounds(pl::LibVersion::LATEST, pl::LibVersion::EARLIEST),
               std::runtime_error);
}

