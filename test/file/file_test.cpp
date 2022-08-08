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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: May 4, 2018
//

#include <catch2/catch.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/contrib/stl/stl.hpp>

using namespace hdf5;

SCENARIO("Testing basic file behavior", "[file,h5cpp]") {
#if H5_VERSION_GE(1, 10, 0)
  property::FileCreationList fcpl;
  property::FileAccessList fapl;
  fapl.library_version_bounds(property::LibVersion::Latest,
                              property::LibVersion::Latest);
  file::create("file_test.h5", file::AccessFlags::Truncate, fcpl, fapl);
#else
  file::create("file_test.h5", file::AccessFlags::Truncate);
#endif

  GIVEN("An open file") {
    file::File f= file::open("file_test.h5", file::AccessFlags::ReadWrite);
    THEN("we must produce the following results") {
      REQUIRE(f.is_valid());
      REQUIRE(f.intent() == file::AccessFlags::ReadWrite);
      REQUIRE(f.size() == 195ul);
      REQUIRE(f.id().file_name() == "file_test.h5");
      REQUIRE(f.path().string() == "file_test.h5");
      auto root = f.root();
      REQUIRE(root.link().path() == "/");
      REQUIRE(f.count_open_objects(file::SearchFlags::Group) == 1ul);
      REQUIRE_NOTHROW(f.flush(file::Scope::Global));
    }
    f.close();
  }

  GIVEN("A closed file") {
    file::File f;
    THEN("file is closed") {
      REQUIRE_FALSE(f.is_valid());
      REQUIRE_THROWS_AS(f.intent(), std::runtime_error);
      REQUIRE_THROWS_AS(f.size(), std::runtime_error);
      REQUIRE_THROWS_AS(f.id(), std::runtime_error);
      REQUIRE_THROWS_AS(f.path(), std::runtime_error);
      REQUIRE_THROWS_AS(f.root(), std::runtime_error);
      REQUIRE_THROWS_AS(f.count_open_objects(file::SearchFlags::All),
                        std::runtime_error);
      REQUIRE_THROWS_AS(f.flush(file::Scope::Global), std::runtime_error);
      REQUIRE_THROWS_AS(f.flush(file::Scope::Local), std::runtime_error);
      REQUIRE_THROWS_AS(f.close(), std::runtime_error);
    }

  }

}

