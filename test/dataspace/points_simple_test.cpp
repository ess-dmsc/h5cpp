//
// (c) Copyright 2017 DESY,ESS
//               2020 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
//   Eugen Wintersberger <eugen.wintersberger@gmail.com>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 25, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/dataspace/points.hpp>
#include <h5cpp/dataspace/simple.hpp>

using namespace hdf5;

SCENARIO("construction of point selections") {
  GIVEN("a default constructed Points") {
    dataspace::Points h;
    THEN("the rank must be 0") { REQUIRE(h.rank() == 0); }
    THEN("the size must be 0") { REQUIRE(h.size() == 0ul); }
    THEN("the type must be Points") {
      REQUIRE(h.type() == hdf5::dataspace::SelectionType::Points);
    }
    THEN("dimensions access must fail") {
      REQUIRE_THROWS_AS(h.dimensions(), std::runtime_error);
    }
  }

  GIVEN("a Point selection constructed for a rank 2") { 
    dataspace::Points h(2);
    THEN("the rank must be 2") { REQUIRE(h.rank() == 2); }
    THEN("the size must be 0") { REQUIRE(h.size() == 0ul); }
    THEN("the type must be Points") {
      REQUIRE(h.type() == hdf5::dataspace::SelectionType::Points);
    }
    THEN("dimensions access be 0") {
      REQUIRE_THAT(h.dimensions(),
                   Catch::Matchers::Equals(Dimensions{0, 0}));
    }
  }

  GIVEN("a Point selection constructed from a list of points") { 
    dataspace::Points points({{1, 1}, {2, 2}});
    THEN("the rank must be 2") { REQUIRE(points.rank() == 2u); }
    THEN("the number of points must be 2") { REQUIRE(points.points() == 2u); }
    THEN("the size must be 2") { REQUIRE(points.size() == 2ul); }
    THEN("the type must be Points") {
      REQUIRE(points.type() == hdf5::dataspace::SelectionType::Points);
    }
    THEN("dimensions access be {2,2}") {
      REQUIRE_THAT(points.dimensions(),
                   Catch::Matchers::Equals(Dimensions{2, 2}));
    }
  }

  GIVEN("a list of points of different rank") {
    THEN("the construction of a point selection must fail"){
      REQUIRE_THROWS_AS(dataspace::Points({{1, 1}, {2, 2, 3}}), std::runtime_error);
    }
  }

}

SCENARIO("apply a point selection") { 
  GIVEN("a point selection for rank 1") { 
    dataspace::Points h(1);
    THEN("the number of points must be 0") { REQUIRE(h.points() == 0); }
    WHEN("adding a point") {
      h.add({2});
      THEN("the number of points must be 1") { REQUIRE(h.points() == 1); }
      AND_WHEN("adding another point") { 
        h.add({7});
        THEN("the number of points must be 2") { REQUIRE(h.points() == 2); }
      }
    }
    WHEN("trying to add a 2d point") {
      REQUIRE_THROWS_AS(h.add({2,3}), std::runtime_error);
    }

  }

  GIVEN("a simple dataspace of shape {10,1024}") { 
    dataspace::Simple space({10, 1024});
    THEN("the selection type for the dataspace must be ALL") { 
      REQUIRE(space.selection.type() == dataspace::SelectionType::All);
    }

    AND_GIVEN("a selection of two points") { 
      dataspace::Points points({{1,1},{2,2}});
      THEN("applying this selection to the dataspace will fail") {
        REQUIRE_THROWS_AS(space.selection(dataspace::SelectionOperation::Or, points), std::runtime_error);
      }
    }
  }

  GIVEN("a point selection of ranke 2") { 
    dataspace::Points points(2);
    AND_GIVEN("a set of points") { 
      THEN("adding the list of indexes") { 
        REQUIRE_THROWS_AS(points.add_set({{1,1},{2,2,3}}), std::runtime_error);
      }
    }
  }
}

SCENARIO("test case one for a point selection") { 
  // create the dataspace
  dataspace::Simple space({10, 20});
  REQUIRE(space.rank() == 2u);
  REQUIRE(space.size() == 200);

  // create the point selection
  dataspace::Points points({{1,1}, {5,5}});

  // apply the selection to the dataspace
  space.selection(dataspace::SelectionOperation::Set, points);
  REQUIRE(space.selection.size() == 2ul);
  REQUIRE(space.selection.type() == dataspace::SelectionType::Points);

  // remove the selection
  REQUIRE_NOTHROW(space.selection.all());
  REQUIRE(space.selection.type() == dataspace::SelectionType::All);
}

SCENARIO("test case two for point selection") {
  dataspace::Simple space({10, 1024, 1024});

  dataspace::Points points(2);
  points.add({1, 1});
  points.add({2, 2});
  points.add({3, 3});
  points.add({4, 4});

  // TODO: why does this not throw when rank is not matching?
  REQUIRE_NOTHROW(space.selection(dataspace::SelectionOperation::Set, points));
  REQUIRE(space.selection.size() == 4ul);
  REQUIRE(space.selection.type() == dataspace::SelectionType::Points);

  dataspace::Points points2(2);
  points2.add({5, 5});
  points2.add({6, 6});

  REQUIRE_NOTHROW(
      space.selection(dataspace::SelectionOperation::Append, points2));
  REQUIRE(space.selection.size() == 6ul);
  REQUIRE(space.selection.type() == dataspace::SelectionType::Points);
}
