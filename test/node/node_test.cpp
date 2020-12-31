
//
// (c) Copyright 2017 DESY,ESS
//               2020 Eugen Wintersberger <eugen.wintersberger@gmail.com>
//
// This file is part of h5cpp.
//
// h5cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// h5cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the imndied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with h5cpp.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Martin Shetty <martin.shetty@esss.se>
//         Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Oct 2, 2017
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/functions.hpp>

using namespace hdf5;

SCENARIO("testing a Node instance") {
  auto f = file::create("node_test.h5", file::AccessFlags::TRUNCATE);
  GIVEN("a default constructed node") {
    node::Node n;
    AND_GIVEN("a second default constructed node") {
      node::Node m;
      THEN("the nodes must be equal") {
        REQUIRE(m == n);
        REQUIRE_FALSE(m != n);
      }
    }
    AND_GIVEN("the root group of the current file") {
      auto root = f.root();
      THEN("n and the root must not be equal") { REQUIRE(root != n); }
      AND_GIVEN("a second instance of the root node") {
        auto root2 = f.root();
        THEN("the two root node instances must be equal") {
          REQUIRE(root2 == root);
        }
      }
    }
  }
}
