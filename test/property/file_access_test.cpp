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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 21, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/property/file_access.hpp>
#include <h5cpp/file/memory_driver.hpp>

namespace pl = hdf5::property;

TEST(FileAccessList, lib_version) {
  std::stringstream stream;

  stream.str(std::string());
  stream << pl::LibVersion::EARLIEST;
  EXPECT_EQ(stream.str(), "EARLIEST");

  stream.str(std::string());
  stream << pl::LibVersion::LATEST;
  EXPECT_EQ(stream.str(), "LATEST");
}

TEST(FileAccessList, default_construction) {
  pl::FileAccessList fapl;
  EXPECT_EQ(fapl.get_class(), pl::kFileAccess);

  auto cl = pl::kFileAccess;
  EXPECT_NO_THROW((pl::FileAccessList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))));

  cl = pl::kGroupCreate;
  EXPECT_THROW((pl::FileAccessList(hdf5::ObjectHandle(H5Pcreate(static_cast<hid_t>(cl))))),
               std::runtime_error);
}

TEST(FileAccessList, library_version_bounds) {
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

  hdf5::ObjectHandle(static_cast<hid_t>(fapl)).close();
  EXPECT_THROW(fapl.library_version_bound_low(), std::runtime_error);
  EXPECT_THROW(fapl.library_version_bound_high(), std::runtime_error);
}

TEST(FileAccessList, driver) {
  pl::FileAccessList fapl;

  hdf5::file::MemoryDriver driver;

  EXPECT_NO_THROW(fapl.driver(driver));
}
