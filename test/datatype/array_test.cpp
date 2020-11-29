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
// Created on: Oct 23, 2017
//
#include <catch2/catch.hpp>
#include <h5cpp/datatype/array.hpp>
#include <h5cpp/datatype/factory.hpp>

using namespace hdf5;

SCENARIO("array type default construction") {
  GIVEN("a default constructed type") {
    datatype::Array type;
    THEN("the type would be invalid") { REQUIRE_FALSE(type.is_valid()); }
    THEN("the class would be none") {
      REQUIRE(type.get_class() == datatype::Class::NONE);
    }
    THEN("we cannot obtain the rank") {
      REQUIRE_THROWS_AS(type.dimensions(), std::runtime_error);
    }
  }

  GIVEN("a floating point type") {
    auto ft = datatype::create<double>();
    THEN("we cannot construct a array type from it") {
      REQUIRE_THROWS_AS((datatype::Array(ft)), std::runtime_error);
    }
  }

  GIVEN("a default constructed generic type") {
    datatype::Datatype dt;
    THEN("we cannot construct an array type from it") {
      REQUIRE_THROWS_AS(datatype::Array::create(dt, {3, 4}),
                        std::runtime_error);
    }
  }
}

SCENARIO("constructing a tensor type") {
  using datatype::Array;
  using datatype::Class;
  GIVEN("a base type") {
    auto base_type = datatype::create<int>();
    THEN("we can construct an array type") {
      auto type = Array::create(base_type, {3, 4});
      AND_THEN("we get a valid datatype") { REQUIRE(type.is_valid()); }
      AND_THEN("is array class") { REQUIRE(type.get_class() == Class::ARRAY); }
      AND_THEN("the size is 12") { REQUIRE(type.size() == 12 * sizeof(int)); }
      AND_THEN("the rank is 2") { REQUIRE(type.rank() == 2ul); }
      AND_THEN("the dimensions are") {
        auto dims = type.dimensions();
        REQUIRE(dims[0] == 3ul);
        REQUIRE(dims[1] == 4ul);
      }
    }
  }
}

SCENARIO("constructing a vector type") {
  GIVEN("a double base type") {
    auto base_type = datatype::create<double>();
    AND_GIVEN("a shape") {
      Dimensions s{4};
      THEN("we can construct a type") {
        auto type = datatype::Array::create(base_type, s);
        AND_THEN("the type is valid") { REQUIRE(type.is_valid()); }
        AND_THEN("is an array class") {
          REQUIRE(type.get_class() == datatype::Class::ARRAY);
        }
        AND_THEN("get the size") { REQUIRE(type.size() == 4 * sizeof(double)); }
      }
    }
  }
}
