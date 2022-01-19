//
// (c) Copyright 2017 DESY,ESS
//               2020 Eugen Wintersberger<eugen.wintersberger@gmail.com>
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
// Created on: Sep 7, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/dataspace/type_trait.hpp>
#include <h5cpp/contrib/stl/vector.hpp>

using namespace hdf5;

SCENARIO("testing the type trait for dataspaces") {
  GIVEN("a vector of 20 elements") {
    std::vector<double> data(20);
    auto space = dataspace::create(data);
    REQUIRE(space.type() == dataspace::Type::Simple);
    Dimensions current_dims = space.current_dimensions(),
               max_dims = space.maximum_dimensions();
    REQUIRE(current_dims.size() == 1ul);
    REQUIRE(current_dims[0] == 20ul);
    REQUIRE(max_dims.size() == 1ul);
    REQUIRE(max_dims[0] == 20ul);
  }
  GIVEN("an integer scalar") {
    int data = 10;
    auto space = dataspace::create(data);
    REQUIRE(space.type() == dataspace::Type::Scalar);
    REQUIRE(space.size() == 1l);
  }
}
