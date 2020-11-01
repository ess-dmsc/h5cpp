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
// Created on: Nov 13, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5::dataspace;

SCENARIO("testing data view") {
  auto space = Simple({1024, 512});
  auto selections = SelectionList{
      {SelectionOperation::SET,
       Selection::SharedPointer(new Hyperslab({0, 0}, {100, 100}))},
      {SelectionOperation::OR,
       Selection::SharedPointer(new Hyperslab({200, 200}, {100, 100}))}};

  GIVEN("a default constructed view") {
    View view;
    THEN("access to the size failed") {
      REQUIRE_THROWS_AS(view.size(), std::runtime_error);
    }
    THEN("application to a hyperslab fails") {
      REQUIRE_THROWS_AS(view(Hyperslab{{0, 0}, {10, 10}}), std::runtime_error);
    }
    THEN("application to a selection list must fail") {
      REQUIRE_THROWS_AS(view(selections), std::runtime_error);
    }
  }

  GIVEN("a hyperslab an a selections") {
    auto slab = Hyperslab{{300, 300}, {100, 100}};
    THEN("we can construct a new view") {
      View view{space, selections};
      AND_THEN("the size is") { REQUIRE(view.size() == 2ul * 100ul * 100ul); }
      AND_THEN("the space is of size") {
        REQUIRE(space.size() == 1024ul * 512ul);
      }
    }

    AND_GIVEN("a view on the dataspace") {
      View view{space};
      THEN("the size of the view and the dataspace match") {
        REQUIRE(view.size() == space.size());
      }

      WHEN("applying a single hyperslab") {
        REQUIRE_NOTHROW(view(slab));
        THEN("the size of the view will be") {
          REQUIRE(view.size() == 100ul * 100ul);
        }
      }

      WHEN("applying a list of selections to the dataspace") {
        REQUIRE_NOTHROW(view(selections));
        THEN("the size of the view will be") {
          REQUIRE(view.size() == 2ul * 100ul * 100ul);
        }
      }
    }
  }
}
