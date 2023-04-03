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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Aug 25, 2017
//
#include <catch2/catch_amalgamated.hpp>
#include <h5cpp/dataspace/pool.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

using Simple = dataspace::Simple;
using DataspacePool = dataspace::DataspacePool;

SCENARIO("construction of a 1d simple dataspace from dimensions using pool") {
  GIVEN("the dimensions") {
    hsize_t size = 12;
    Dimensions dimensions = {size};
    THEN("we can construct a new simple dataspace") {
      DataspacePool pool;
      const Simple & space = pool.getSimple(size);
      const Simple & space2 = pool.getSimple(size);
      AND_THEN("the size is") { REQUIRE(space.size() == 12); }
      AND_THEN("the rank is") { REQUIRE(space.rank() == 1); }
      AND_THEN("the references are equal") {
        REQUIRE(std::addressof(space) == std::addressof(space2)); }
      AND_THEN("the current dimensions are") {
        REQUIRE_THAT(dimensions,
                     Catch::Matchers::Equals(space.current_dimensions()));
      }
      AND_THEN("the maximum dimensions are") {
        REQUIRE_THAT(dimensions,
                     Catch::Matchers::Equals(space.maximum_dimensions()));
      }
    }
  }
}

SCENARIO("construction of a 3d simple dataspace from dimensions using pool") {
  GIVEN("the dimensions") {
    Dimensions dimensions = {10, 20, 30};
    THEN("we can construct a new simple dataspace") {
      DataspacePool pool;
      const Simple & space = pool.getSimple(dimensions);
      const Simple & space2 = pool.getSimple(dimensions);
      AND_THEN("the size is") { REQUIRE(space.size() == 10 * 20 * 30); }
      AND_THEN("the rank is") { REQUIRE(space.rank() == 3); }
      AND_THEN("the references are equal") {
        REQUIRE(std::addressof(space) == std::addressof(space2)); }
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
        DataspacePool pool;
        const Simple & space = pool.getSimple(dimensions, max);
        const Simple & space2 = pool.getSimple(dimensions, max);
        AND_THEN("the size is") { REQUIRE(space.size() == 10 * 20 * 30); }
        AND_THEN("the rank is") { REQUIRE(space.rank() == 3); }
        AND_THEN("the references are equal") {
          REQUIRE(std::addressof(space) == std::addressof(space2)); }
        AND_THEN("the references are equal") {
          REQUIRE(hid_t(space) == hid_t(space2)); }
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

