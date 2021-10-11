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
// Created on: Sep 10, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/file/functions.hpp>

using namespace hdf5;

static const std::string filename = "file_optn_test.h5";

SCENARIO("opening a file") {
#if H5_VERSION_GE(1, 10, 0)
  property::FileCreationList fcpl;
  property::FileAccessList fapl;
  fapl.library_version_bounds(property::LibVersion::LATEST,
                              property::LibVersion::LATEST);
  file::create(filename, file::AccessFlags::TRUNCATE, fcpl, fapl);
#else
  file::create(filename, file::AccessFlags::TRUNCATE);
#endif

  WHEN("using the default operation") {
    auto f = file::open(filename);
    REQUIRE(f.intent() == file::AccessFlags::READONLY);
  }

  WHEN("opening in read/write mode") {
    auto f = file::open(filename, file::AccessFlags::READWRITE);
    REQUIRE(f.intent() == file::AccessFlags::READWRITE);
  }

  WHEN("opening a non-existing file") {
    REQUIRE_THROWS_AS(
        file::open("nonexistent.qqq", file::AccessFlags::READWRITE),
        std::runtime_error);
  }

#if H5_VERSION_GE(1, 10, 0)

  WHEN("opening in SWMR read-mode") {
    auto f = file::open(filename, file::AccessFlags::SWMR_READ);
    REQUIRE(f.intent() == file::AccessFlags::SWMR_READ);
  }

  WHEN("opening in SWM  write-mode") {
    auto f = file::open(filename, file::AccessFlags::READWRITE |
                                            file::AccessFlags::SWMR_WRITE);

    REQUIRE(static_cast<file::AccessFlagsBase>(f.intent()) ==
            (file::AccessFlags::SWMR_WRITE | file::AccessFlags::READWRITE));
  }

#endif
}
