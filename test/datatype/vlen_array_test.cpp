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
// Created on: Oct 23, 2017
//
#include <catch2/catch.hpp>
#include <h5cpp/datatype/array.hpp>
#include <h5cpp/datatype/factory.hpp>

using namespace hdf5;

SCENARIO("Variable length default construction") {
  GIVEN("a default constructed type") {
    datatype::VLengthArray type;
    THEN("the type is invalid") { REQUIRE_FALSE(type.is_valid()); }
    THEN("the class is NONE") {
      REQUIRE(type.get_class() == datatype::Class::None);
    }
  }

  GIVEN("a double scalar type") {
    auto ft = datatype::create<double>();
    THEN("we cannot construct a variable length array from this") {
      REQUIRE_THROWS_AS((datatype::VLengthArray(ft)), std::runtime_error);
    }
  }

  GIVEN("a default constructed generic type") {
    datatype::Datatype dt;
    THEN("we cannot create a variable length array type") {
      REQUIRE_THROWS_AS((datatype::VLengthArray::create(dt)),
                        std::runtime_error);
    }
  }

  GIVEN("a double base type") {
    auto base_type = datatype::create<double>();
    THEN("we can construct a variable array type from it") {
      auto type = datatype::VLengthArray::create(base_type);
      AND_THEN("the type is valid") { REQUIRE(type.is_valid()); }
      AND_THEN("the type class is") {
        REQUIRE(type.get_class() == datatype::Class::VarLength);
      }
      AND_THEN("the super type is FLOAT") {
        REQUIRE(type.super().get_class() == datatype::Class::Float);
        REQUIRE(type.super() == base_type);
      }
      AND_THEN("the types' size would be") {
        REQUIRE(type.size() == sizeof(hvl_t));
      }
    }
  }
}

SCENARIO("Variable length default construction with cref") {
  GIVEN("a default constructed type") {
    datatype::VLengthArray type;
    THEN("the type is invalid") { REQUIRE_FALSE(type.is_valid()); }
    THEN("the class is NONE") {
      REQUIRE(type.get_class() == datatype::Class::None);
    }
  }

  GIVEN("a double scalar type") {
    auto & ft = datatype::get<double>();
    THEN("we cannot construct a variable length array from this") {
      REQUIRE_THROWS_AS((datatype::VLengthArray(ft)), std::runtime_error);
    }
  }

  GIVEN("a default constructed generic type") {
    datatype::Datatype dt;
    THEN("we cannot create a variable length array type") {
      REQUIRE_THROWS_AS((datatype::VLengthArray::create(dt)),
                        std::runtime_error);
    }
  }

  GIVEN("a double base type") {
    auto & base_type = datatype::get<double>();
    THEN("we can construct a variable array type from it") {
      auto type = datatype::VLengthArray::create(base_type);
      AND_THEN("the type is valid") { REQUIRE(type.is_valid()); }
      AND_THEN("the type class is") {
        REQUIRE(type.get_class() == datatype::Class::VarLength);
      }
      AND_THEN("the super type is FLOAT") {
        REQUIRE(type.super().get_class() == datatype::Class::Float);
        REQUIRE(type.super() == base_type);
      }
      AND_THEN("the types' size would be") {
        REQUIRE(type.size() == sizeof(hvl_t));
      }
    }
  }
}
