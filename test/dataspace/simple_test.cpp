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
#include <catch2/catch_all.hpp>
#include <h5cpp/dataspace/simple.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

using Simple = dataspace::Simple;
using Type = dataspace::Type;

SCENARIO("default construction of a simple dataspace") {
  GIVEN("a default constructed dataspace") {
    Simple space;

    THEN("the size is 0") { REQUIRE(space.size() == 0); }
    THEN("the rank must be 0") { REQUIRE(space.rank() == 0u); }
    THEN("the type must be Simple") { REQUIRE(space.type() == Type::Simple); }
    THEN("the dimensions must be empty") {
      REQUIRE(space.current_dimensions().empty());
      REQUIRE(space.maximum_dimensions().empty());
    }
    WHEN("closing the dataspace") {
      ObjectHandle(static_cast<hid_t>(space)).close();

      THEN("accessing the rank must fail") {
        REQUIRE_THROWS_AS(space.rank(), std::runtime_error);
      }
      THEN("accessing the current dimensions must fail") {
        REQUIRE_THROWS_AS(space.current_dimensions(), std::runtime_error);
      }
      THEN("accessing the maximum dimensions must fail") {
        REQUIRE_THROWS_AS(space.maximum_dimensions(), std::runtime_error);
      }
      THEN("accessing the dimensions must fail") {
        REQUIRE_THROWS_AS(space.dimensions({1}, {1}), std::runtime_error);
      }
    }
  }
}

SCENARIO("default construction of a simple dataspace from an hid_t") {
  GIVEN("an hid_t to a simple dataspace") {
    hid_t id = H5Screate(H5S_SIMPLE);
    THEN("we can create a new instance of simple dataspace") {
      Simple space2{ObjectHandle(id)};
    }
  }

  GIVEN("an hid_t to a scalar dataspace") {
    hid_t id = H5Screate(H5S_SCALAR);
    THEN("the construction of an id must fail") {
      REQUIRE_THROWS_AS(Simple{ObjectHandle(id)}, std::runtime_error);
    }
  }
}

SCENARIO("construction of a simple dataspace from dimensions") {
  GIVEN("the dimensions") {
    Dimensions dimensions = {10, 20, 30};
    THEN("we can construct a new simple dataspace") {
      Simple space{dimensions};
      AND_THEN("the size is") { REQUIRE(space.size() == 10 * 20 * 30); }
      AND_THEN("the rank is") { REQUIRE(space.rank() == 3); }
      AND_THEN("the current dimensions are") {
        REQUIRE_THAT(dimensions,
                     Catch::Matchers::Equals(space.current_dimensions()));
      }
      AND_THEN("the maximum dimensions are") {
        REQUIRE_THAT(dimensions,
                     Catch::Matchers::Equals(space.maximum_dimensions()));
      }
    }

    AND_GIVEN("maximum dimensions") {
      Dimensions max = {100, 200, dataspace::Simple::unlimited};
      THEN("we can construct a dataspace with maximum dimensions") {
        Simple space(dimensions, max);
        AND_THEN("the size is") { REQUIRE(space.size() == 10 * 20 * 30); }
        AND_THEN("the rank is") { REQUIRE(space.rank() == 3); }
        AND_THEN("the current dimensions are") {
          REQUIRE_THAT(dimensions,
                       Catch::Matchers::Equals(space.current_dimensions()));
        }
        AND_THEN("the maximum dimensions are") {
          REQUIRE_THAT(max,
                       Catch::Matchers::Equals(space.maximum_dimensions()));
        }
      }
    }
  }
}

SCENARIO("Resizing a simple dataspace") {
  GIVEN("a simple dataspace with 100 elements and rank 1") {
    Simple s{Dimensions{100}};
    THEN("the size is") { REQUIRE(s.size() == 100); }
    THEN("the rank is") { REQUIRE(s.rank() == 1); }
    AND_GIVEN("new dimensions") {
      Dimensions current{2, 3}, max{2, 3};
      WHEN("we can set the new dimensions") {
        s.dimensions(current, max);
        THEN("the size is") { REQUIRE(s.size() == 6); }
        THEN("the rank is") { REQUIRE(s.rank() == 2); }
      }
    }
  }
}
