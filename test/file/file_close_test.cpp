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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Jul 06, 2018
//

#include <catch2/catch.hpp>
#include <h5cpp/core/filesystem.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/node/group.hpp>
#include <string>
#include <h5cpp/contrib/stl/stl.hpp>

using namespace hdf5;

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
namespace { 
static const std::string filename = "file_close_test.h5";
}
#ifdef __clang__
#pragma clang diagnostic pop
#endif

SCENARIO("Closing file") {
  {
    hdf5::property::FileAccessList fapl;
    hdf5::property::FileCreationList fcpl;
    auto f =
        file::create(filename, file::AccessFlags::Truncate, fcpl, fapl);
    f.root()
        .attributes
        .create("HDF5_version", datatype::create<std::string>(),
                dataspace::Scalar())
        .write(std::string("1.0.0"));
  }

  GIVEN("A strong closing policy") {
    hdf5::property::FileAccessList fapl;
    fapl.close_degree(hdf5::property::CloseDegree::Strong);
    REQUIRE(fapl.close_degree() == hdf5::property::CloseDegree::Strong);
    THEN("the all remaining objects will be close along with the file") {
      auto file = hdf5::file::open(filename,
                                   hdf5::file::AccessFlags::ReadOnly, fapl);
      auto root_group = file.root();

      auto attr = root_group.attributes[0];
      REQUIRE(file.count_open_objects(file::SearchFlags::All) == 3u);

      // with CloseDegree::Strong it closes also root_group and attr
      REQUIRE_NOTHROW(file.close());
      REQUIRE_FALSE(root_group.is_valid());
      REQUIRE_FALSE(attr.is_valid());
      REQUIRE_FALSE(file.is_valid());

      // everything is close so file can be reopen in a different mode, i.e.
      // READWRITE
      REQUIRE_NOTHROW(
          hdf5::file::open(filename, hdf5::file::AccessFlags::ReadWrite));
    }
  }

  GIVEN("the default closing policy") {
    hdf5::property::FileAccessList fapl;
    REQUIRE(fapl.close_degree() == hdf5::property::CloseDegree::Default);
    auto file = hdf5::file::open(filename,
                                 hdf5::file::AccessFlags::ReadOnly, fapl);
    auto root_group = file.root();

    auto attr = root_group.attributes[0];
    REQUIRE(file.count_open_objects(file::SearchFlags::All) == 3ul);

    // without CloseDegree::Strong root_group and attr are still open
    REQUIRE_NOTHROW(file.close());
    REQUIRE(root_group.is_valid());
    REQUIRE(attr.is_valid());

    // file cannot be reopen in a different mode, i.e. READWRITE
    REQUIRE_THROWS_AS(
        hdf5::file::open(filename, hdf5::file::AccessFlags::ReadWrite),
        std::runtime_error);
  }
}

