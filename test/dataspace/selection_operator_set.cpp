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
// Created on: Nov 13, 2017
//
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5::dataspace;

SCENARIO("testing the operators for selection operations") {
  GIVEN("a two dimensional dataspace") {
    auto space = Simple{{1024, 512}};
    AND_GIVEN("a hyperslab selection") {
      auto hyperslab = Hyperslab{{0, 0}, {100, 200}};

      WHEN("creating a new dataspace") {
        Simple new_space = space || hyperslab;
        THEN("the size of the dataspaces must be equal") {
          REQUIRE(new_space.size() == space.size());
        }
        THEN("the new space has the selection attached") {
          REQUIRE(new_space.selection.size() == 100ul * 200ul);
        }
      }
    }
    AND_GIVEN("a list of selections") {
      SelectionList selections{
          {SelectionOperation::Set,
           Selection::SharedPointer(new Hyperslab{{0, 0}, {100, 200}})},
          {SelectionOperation::Or,
           Selection::SharedPointer(new Hyperslab{{101, 201}, {100, 200}})}};
      WHEN("creating a new dataset from the selection") { 
        Simple new_space = space || selections;
        THEN("the dataspace sizes must match") { REQUIRE(new_space.size() == space.size());}
        THEN("the new dataspace must have the selection added") {
          REQUIRE(new_space.selection.size() == 2ul * 100ul * 200ul);
        }
      }
    }
  }
}
