
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
// Created on: Aug 17, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/property/creation_order.hpp>

namespace pl = hdf5::property;

SCENARIO("Testing LinkCreationOrder construction") {
  WHEN("default constructed") {
    pl::CreationOrder order;
    THEN("it must implicitely convert to 0") { REQUIRE(order == 0x0000ul); }
  }
  WHEN("created with H5P_CRT_ORDER_TRACKED") {
    pl::CreationOrder o1(H5P_CRT_ORDER_TRACKED);
    THEN("the tracked flag must be set") { REQUIRE(o1.tracked()); }
    THEN("the indexed flag must not be set") { REQUIRE_FALSE(o1.indexed()); }
  }
  WHEN("created with TRACKED and INDEXED") {
    auto o1 = pl::CreationOrder(H5P_CRT_ORDER_TRACKED | H5P_CRT_ORDER_INDEXED);
    THEN("the tracked flag must be set") { REQUIRE(o1.tracked()); }
    THEN("the indexed flag must be set") { REQUIRE(o1.indexed()); }
  }
}

SCENARIO("setting LinkCreationOrder configuration by member methods") {
  GIVEN("a default constructed instance") {
    pl::CreationOrder o;
    WHEN("enabling tracking") {
      o.enable_tracked();
      THEN("the tracking flag will be set") { REQUIRE(o.tracked()); }
      THEN("the index flag must not be set") { REQUIRE_FALSE(o.indexed()); }
      AND_WHEN("disabling tracking") {
        o.disable_tracked();
        THEN("the traking flag is unset") { REQUIRE_FALSE(o.tracked()); }
        THEN("the indexed flag is unset") { REQUIRE_FALSE(o.indexed()); }
      }
    }
    WHEN("enabling indexing") {
      o.enable_indexed();
      THEN("the tracking flag will be set") { REQUIRE(o.tracked()); }
      THEN("the index flag will be set") { REQUIRE(o.indexed()); }
      AND_WHEN("disabling indexing") {
        o.disable_indexed();
        THEN("the tracking flag remains set") { REQUIRE(o.tracked()); }
        THEN("the index flag will be unset") { REQUIRE_FALSE(o.indexed()); }
      }
    }
  }
}
