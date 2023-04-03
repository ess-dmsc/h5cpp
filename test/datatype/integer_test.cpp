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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Aug 23, 2017
//

#include <catch2/catch_all.hpp>
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
      REQUIRE(t.get_class() == datatype::Class::Integer);
    }
    THEN("the size should be the same as the memory size") {
      REQUIRE(t.size() == sizeof(TestType));
    }

    AND_GIVEN("a Datatype reference to that type") {
      datatype::Datatype& generic = t;
      THEN("we can create a new integer type from this reference") {
        datatype::Integer new_type(generic);
        AND_THEN("type type class would be Integer") {
          REQUIRE(new_type.get_class() == datatype::Class::Integer);
        }
      }
    }

    WHEN("checking for the precission") {
      REQUIRE(t.precision() == t.size() * 8lu);
      AND_THEN("we can set the precission to 16") {
        t.precision(16lu);
        REQUIRE(t.precision() == 16lu);
      }
      AND_THEN("we can set the precission to 8") {
        t.precision(8lu);
        REQUIRE(t.precision() == 8lu);
      }
    }

    WHEN("checking the byte order") {
      using datatype::Order;
      REQUIRE((t.order() == Order::LE || t.order() == Order::BE ||
              t.order() == Order::Vax));
      AND_THEN("set the byte order to Big Endian") {
        t.order(Order::BE);
        REQUIRE(t.order() == datatype::Order::BE);
      }
      AND_THEN("set the byte order to Little Endian") {
        t.order(datatype::Order::LE);
        REQUIRE(t.order() == datatype::Order::LE);
      }
    }

    WHEN("checking for the offset") {
      REQUIRE(t.offset() == 0lu);
      AND_THEN("set it to 1") {
        t.offset(1);
        REQUIRE(t.offset() == 1lu);
      }
      AND_THEN("set it to 2") {
        t.offset(2);
        REQUIRE(t.offset() == 2lu);
      }
    }

    WHEN("checking the padding") {
      using datatype::Pad;
      using r = std::vector<Pad>;
      REQUIRE_THAT(t.pad(), Catch::Matchers::Equals(r{Pad::Zero, Pad::Zero}));
      AND_THEN("set it to ZERO:ONE") { 
        t.pad(Pad::Zero,Pad::One);
        REQUIRE_THAT(t.pad(), Catch::Matchers::Equals(r{Pad::Zero,Pad::One}));
      }
      AND_THEN("set it to ONE:BACKGROUND") { 
        t.pad(Pad::One,Pad::Background);
        REQUIRE_THAT(t.pad(), Catch::Matchers::Equals(r{Pad::One,Pad::Background}));
      }
    }
  }
}

TEMPLATE_TEST_CASE("general integer properties with cref",
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
    const auto t = datatype::Integer(datatype::get<TestType>());
    THEN("the return type must be a const integer reference") {
      REQUIRE((std::is_same<decltype(t), const datatype::Integer>::value));
    }
    THEN("the type class is integer") {
      REQUIRE(t.get_class() == datatype::Class::Integer);
    }
    THEN("the size should be the same as the memory size") {
      REQUIRE(t.size() == sizeof(TestType));
    }

    WHEN("checking for the precission") {
      REQUIRE(t.precision() == t.size() * 8lu);
    }

    WHEN("checking the byte order") {
      using datatype::Order;
      REQUIRE((t.order() == Order::LE || t.order() == Order::BE ||
              t.order() == Order::Vax));
    }

    WHEN("checking for the offset") {
      REQUIRE(t.offset() == 0lu);
    }

    WHEN("checking the padding") {
      using datatype::Pad;
      using r = std::vector<Pad>;
      REQUIRE_THAT(t.pad(), Catch::Matchers::Equals(r{Pad::Zero, Pad::Zero}));
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

TEMPLATE_TEST_CASE("signed integer properties with cref",
                   "[datatype][numeric][integer]",
                   char,
                   short,
                   int,
                   long,
                   long long) {
  GIVEN("an instance of a signed integer") {
    auto t = datatype::Integer(datatype::get<TestType>());
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

TEMPLATE_TEST_CASE("unsigned integer properties with cref",
                   "[datatype][numeric][integer]",
                   unsigned char,
                   unsigned short,
                   unsigned int,
                   unsigned long,
                   unsigned long long) {
  GIVEN("an instance of a unsigned integer") {
    auto t = datatype::Integer(datatype::get<TestType>());
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
