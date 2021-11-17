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
// Author:
//   Eugen Wintersberger <eugen.wintersberger@gmail.com>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 20, 2017
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <h5cpp/datatype/datatype.hpp>
#include <tuple>

using namespace hdf5;
using namespace hdf5::datatype;

SCENARIO("construction of datatypes") {
  GIVEN("a default constructed datatype") {
    Datatype a;
    THEN("this instance is not valid") { REQUIRE_FALSE(a.is_valid()); }
    THEN("the type class is NONE") { REQUIRE(a.get_class() == Class::None); }
    THEN("the super() method must fail") {
      REQUIRE_THROWS_AS(a.super(), std::runtime_error);
    }
    THEN("the native_type() method must fail") {
      REQUIRE_THROWS_AS(a.native_type(), std::runtime_error);
    }
    THEN("has_class() fails") {
      REQUIRE_THROWS_AS(a.has_class(Class::Integer), std::runtime_error);
    }
    THEN("cannot get the size() of the type - fails with exception") {
      REQUIRE_THROWS_AS(a.size(), std::runtime_error);
    }
    THEN("cannot set the size of the type - fails with exception") {
      REQUIRE_THROWS_AS(a.size(1), std::runtime_error);
    }
    AND_GIVEN("a second default constructed type") {
      Datatype b;
      a = b;
      THEN("this instance is not valid") { REQUIRE_FALSE(b.is_valid()); }
      THEN("the type class is NONE") { REQUIRE(b.get_class() == Class::None); }
      THEN("the super() method must fail") {
	REQUIRE_THROWS_AS(b.super(), std::runtime_error);
      }
      THEN("the native_type() method must fail") {
	REQUIRE_THROWS_AS(b.native_type(), std::runtime_error);
      }
      THEN("has_class() fails") {
	REQUIRE_THROWS_AS(b.has_class(Class::Integer), std::runtime_error);
      }
      THEN("cannot get the size() of the type - fails with exception") {
	REQUIRE_THROWS_AS(b.size(), std::runtime_error);
      }
      THEN("cannot set the size of the type - fails with exception") {
	REQUIRE_THROWS_AS(b.size(1), std::runtime_error);
      }
    }
  }

  GIVEN("a dataspace object handle") {
    auto handle = ObjectHandle(H5Screate(H5S_SIMPLE));
    THEN("construction from such a handle must fail") {
      REQUIRE_THROWS_AS(Datatype(std::move(handle)), std::runtime_error);
    }
  }

  GIVEN("an integer dataytpe") {
    Datatype a(ObjectHandle(H5Tcopy(H5T_NATIVE_INT)));
    THEN("its type class will be integer") {
      REQUIRE(a.get_class() == Class::Integer);
    }
    THEN("we can copy construct a new type from this") {
      Datatype b = a;
      AND_THEN("the new type is of class integer") {
        REQUIRE(b.get_class() == Class::Integer);
      }
      AND_THEN("the two types are different objects") {
        REQUIRE(static_cast<hid_t>(a) != static_cast<hid_t>(b));
      }
    }
  }
}

SCENARIO("comparing datatypes") {
  GIVEN("an integer datatype") {
    Datatype a(ObjectHandle(H5Tcopy(H5T_NATIVE_INT)));
    AND_GIVEN("a second integer type (copy constructed)") {
      auto b = a;
      THEN("these two types are different objects") {
        REQUIRE(static_cast<hid_t>(a) != static_cast<hid_t>(b));
      }
      THEN("these two types are equal types") { REQUIRE(a == b); }
    }

    AND_GIVEN("a floating point type") {
      auto b = Datatype(ObjectHandle(H5Tcopy(H5T_NATIVE_FLOAT)));
      THEN("these two types are considered not equal") { REQUIRE(a != b); }
    }

    AND_GIVEN("a default constructed type") {
      Datatype b;
      THEN("the comparison operation must fail with an exception") {
        REQUIRE_THROWS_AS(a == b, std::runtime_error);
      }
    }
  }
}

struct {
  const hid_t& native_uint8 = H5T_NATIVE_UINT8;
  const hid_t& native_int8 = H5T_NATIVE_INT8;
  const hid_t& native_uint16 = H5T_NATIVE_UINT16;
  const hid_t& native_int16 = H5T_NATIVE_INT16;
  const hid_t& native_uint32 = H5T_NATIVE_UINT32;
  const hid_t& native_int32 = H5T_NATIVE_INT32;
  const hid_t& native_uint64 = H5T_NATIVE_UINT64;
  const hid_t& native_int64 = H5T_NATIVE_INT64;
  const hid_t& native_float32 = H5T_NATIVE_FLOAT;
  const hid_t& native_float64 = H5T_NATIVE_DOUBLE;
} h5t;

SCENARIO("Properties of numeric types") {
  auto create = [](const hid_t& tc) {
    return Datatype(ObjectHandle(H5Tcopy(tc)));
  };

  using ptype = std::tuple<hid_t, Class, size_t>;
  auto p = GENERATE(table<hid_t, Class, size_t>(
      {ptype{h5t.native_uint8, Class::Integer, 1},
       ptype{h5t.native_int8, Class::Integer, 1},
       ptype{h5t.native_uint16, Class::Integer, 2},
       ptype{h5t.native_int16, Class::Integer, 2},
       ptype{h5t.native_uint32, Class::Integer, 4},
       ptype{h5t.native_int32, Class::Integer, 4},
       ptype{h5t.native_uint64, Class::Integer, 8},
       ptype{h5t.native_int64, Class::Integer, 8},
       ptype{h5t.native_float32, Class::Float, 4},
       ptype{h5t.native_float64, Class::Float, 8}}));

  GIVEN("an integer type") {
    auto a = create(std::get<0>(p));
    THEN("the type class must be integer") {
      REQUIRE(a.get_class() == std::get<1>(p));
    }
    THEN("the size would be") { REQUIRE(a.size() == std::get<2>(p)); }
  }
}

/*


TEST(Datatype, Classes) {


  a = Datatype(ObjectHandle(H5Tcreate(H5T_STRING, 1)));
  EXPECT_EQ(a.get_class(), Class::String);
}

  a = Datatype(ObjectHandle(H5Tcreate(H5T_COMPOUND, 8)));
  EXPECT_EQ(a.get_class(), Class::Compound);
  EXPECT_THROW(a.super(), std::runtime_error);
  H5Tinsert(static_cast<hid_t>(a), "hello", 0, H5T_NATIVE_INT);
  EXPECT_TRUE(a.has_class(Class::Integer));
  EXPECT_FALSE(a.has_class(Class::Float));

  a = Datatype(ObjectHandle(H5Tcreate(H5T_OPAQUE, 1)));
  EXPECT_EQ(a.get_class(), Class::Opaque);

  a = Datatype(ObjectHandle(H5Tcreate(H5T_ENUM, 1)));
  EXPECT_EQ(a.get_class(), Class::Enum);
  auto b = a.super();
  EXPECT_EQ(b.get_class(), Class::Integer);

  a = Datatype(ObjectHandle(H5Tvlen_create(H5T_NATIVE_INT)));
  EXPECT_EQ(a.get_class(), Class::VarLength);

  hsize_t arrsize = 2;
  a = Datatype(ObjectHandle(H5Tarray_create(H5T_NATIVE_INT, 1, &arrsize)));
  EXPECT_EQ(a.get_class(), Class::Array);

  // TODO: reenable tests when relevant library functionality is implemented
  //  a = Datatype(ObjectHandle((H5T_BITFIELD)));
  //  a = Datatype(ObjectHandle(H5Tcopy(H5T_BITFIELD)));
  //  EXPECT_TRUE(a.native_type().get_class()==Class::BitField);

  //  a = Datatype(ObjectHandle(H5Tcopy(H5T_REFERENCE)));
  //  EXPECT_TRUE(a.get_class()==Class::Reference);

  //  a =
  // Datatype(ObjectHandle(H5Tcreate(static_cast<H5T_class_t>(Class::Time),1)));
  //  EXPECT_TRUE(a.get_class()==Class::Time);
}

TEST(Datatype, Size) {
  auto a = Datatype(ObjectHandle(H5Tcreate(H5T_COMPOUND, 2)));
  ASSERT_EQ(a.size(), 2ul);
  a.size(4);
  ASSERT_EQ(a.size(), 4ul);
}
*/
