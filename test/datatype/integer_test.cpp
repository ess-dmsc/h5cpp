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
// Created on: Aug 23, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/datatype/integer.hpp>

#include "test_traits.hpp"

using namespace hdf5;


/*
TYPED_TEST(Integer, Exceptions) {
  datatype::Datatype dtype;
  EXPECT_THROW((datatype::Integer(dtype)), std::runtime_error);

  auto ft = datatype::create<double>();
  EXPECT_THROW((datatype::Integer(ft)), std::runtime_error);
}*/

TEMPLATE_TEST_CASE("general integer properties",
                   "[datatype][numeric][integer]",
                   unsigned char,
                   char,
                   short,
                   unsigned short,
                   int,
                   unsigned int,
                   long,
                   unsigned long,
                   long long,
                   unsigned long long) {
  GIVEN("a particular integer type") {
    auto t = datatype::create<TestType>();
    THEN("the return type must be an integer type") {
      REQUIRE((std::is_same<decltype(t), datatype::Integer>::value));
    }
    THEN("the type class is integer") {
      REQUIRE(t.get_class() == datatype::Class::INTEGER);
    }
    THEN("the size should be the same as the memory size") {
      REQUIRE(t.size() == sizeof(TestType));
    }

    AND_GIVEN("a Datatype reference to that type") {
      datatype::Datatype& generic = t;
      THEN("we can create a new integer type from this reference") {
        datatype::Integer new_type(generic);
        AND_THEN("type type class would be Integer") {
          REQUIRE(new_type.get_class() == datatype::Class::INTEGER);
        }
      }
    }
  }
}

TEMPLATE_TEST_CASE("signed integer properties",
                   "[datatype][numeric][integer]",
                   char,
                   short,
                   int,
                   long,
                   long long) {
  GIVEN("an instance of a signed integer") {
    auto t = datatype::create<TestType>();
    THEN("the signed property will be true") { REQUIRE(t.is_signed()); }
    AND_THEN("we can make it unsigned") {
      t.make_signed(false);
      THEN("setting the flag") { REQUIRE_FALSE(t.is_signed()); }
      AND_THEN("make it signed again") {
        t.make_signed(true);
        THEN("the flag will be true again") { REQUIRE(t.is_signed()); }
      }
    }
  }
}

TEMPLATE_TEST_CASE("unsigned integer properties",
                   "[datatype][numeric][integer]",
                   unsigned char,
                   unsigned short,
                   unsigned int,
                   unsigned long,
                   unsigned long long) {
  GIVEN("an instance of a unsigned integer") {
    auto t = datatype::create<TestType>();
    THEN("the signed property will be true") { REQUIRE_FALSE(t.is_signed()); }
    AND_THEN("we can make it signed") {
      t.make_signed(true);
      THEN("setting the flag") { REQUIRE(t.is_signed()); }
      AND_THEN("make it unsigned again") {
        t.make_signed(false);
        THEN("the flag will be false again") { REQUIRE_FALSE(t.is_signed()); }
      }
    }
  }
}