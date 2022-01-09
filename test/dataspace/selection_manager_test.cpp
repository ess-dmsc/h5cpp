//
// (c) Copyright 2017 DESY,ESS
//               2020 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
//   Eugen Wintersberger <eugen.wintersberger@gmail.com>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 25, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/dataspace/simple.hpp>

using namespace hdf5;

SCENARIO("test selection handling on dataspaces") {
  GIVEN("a simple dataspace {10,1024}") {
    dataspace::Simple space({10, 1024});
    THEN("the size must be 10*1024") { REQUIRE(space.size() == 10l * 1024l); }
    THEN("the selection size is the same") {
      REQUIRE(space.selection.size() == 10ul * 1024ul);
    }
    THEN("the selection type must be all") {
      REQUIRE(space.selection.type() == dataspace::SelectionType::All);
    }
    WHEN("calling none()") {
      REQUIRE_NOTHROW(space.selection.none());
      THEN("the original size of the space remains") {
        REQUIRE(space.size() == 10l * 1024l);
      }
      THEN("the number of selected elements is") {
        REQUIRE(space.selection.size() == 0ul);
      }
      THEN("the selection type must be NONE") {
        REQUIRE(space.selection.type() == dataspace::SelectionType::None);
      }
    }
    WHEN("calling all()") {
      REQUIRE_NOTHROW(space.selection.all());
      THEN("the dataspace keeps its size") {
        REQUIRE(space.size() == 10l * 1024l);
      }
      THEN("all elements are selected") {
        REQUIRE(space.selection.size() == 10ul * 1024ul);
      }
      THEN("the selection type is ALL") {
        REQUIRE(space.selection.type() == dataspace::SelectionType::All);
      }
    }
    WHEN("closing the dataspace") {
      REQUIRE_NOTHROW(ObjectHandle(static_cast<hid_t>(space)).close());
      THEN("calling size() must fail") {
        REQUIRE_THROWS_AS(space.selection.size(), std::runtime_error);
      }
      THEN("calling none() must fail") {
        REQUIRE_THROWS_AS(space.selection.none(), std::runtime_error);
      }
      THEN("calling all() must fail") {
        REQUIRE_THROWS_AS(space.selection.all(), std::runtime_error);
      }
    }
  }
}
