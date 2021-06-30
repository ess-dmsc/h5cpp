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
// Author: Martin Shetty <martin.shetty@esss.se>
//         Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Oct 22, 2017
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <h5cpp/dataspace/dataspace.hpp>

using namespace hdf5;
using namespace hdf5::dataspace;

SCENARIO("default constructed dataspace") {
  GIVEN("a default constructed dataspace") {
    Dataspace s;
    THEN("size() will fail") {
      REQUIRE_THROWS_AS(s.size(), std::runtime_error);
    }
    THEN("type() will fail") {
      REQUIRE_THROWS_AS(s.type(), std::runtime_error);
    }
    THEN("the dataspace will not be valid") { REQUIRE_FALSE(s.is_valid()); }
  }
}

SCENARIO("dataspace constructed from an hid_t") {
  GIVEN("a valid hidt") {
    hid_t id = H5Screate(H5S_SCALAR);
    THEN("we can construct a dataspace") {
      Dataspace s{ObjectHandle(id)};
      AND_THEN("the dataspace size will be 1") { REQUIRE(s.size() == 1); }
      AND_THEN("the type will be scalar") { REQUIRE(s.type() == Type::SCALAR); }
      AND_THEN("the dataspace will be valid") { REQUIRE(s.is_valid()); }
    }
  }

  GIVEN("a handle to compound data type") {
    hid_t id = H5Tcreate(H5T_COMPOUND, 1);
    THEN("the creation of the dataspace will fail") {
      REQUIRE_THROWS_AS(Dataspace(ObjectHandle(id)), std::runtime_error);
    }
  }
}

SCENARIO("copy constructed dataspace") {
  GIVEN("a default constructed original dataspace") {
    Dataspace s;
    const Dataspace& ss = s;
    THEN("copy construction will fail") {
      REQUIRE_THROWS_AS(Dataspace(ss).is_valid(), std::runtime_error);
    }
  }

  GIVEN("a dataspace constructed from an hid_t") {
    auto s = Dataspace(ObjectHandle(H5Screate(H5S_SCALAR)));
    THEN("we can copy construct a new dataspace") {
      Dataspace s2(s);
      AND_THEN("its types will match") { REQUIRE(s.type() == s2.type()); }
      AND_THEN("the two underlying ids are different") {
        REQUIRE_FALSE(static_cast<hid_t>(s) == static_cast<hid_t>(s2));
      }
    }
  }
}

SCENARIO("copy assignemnt of a dataspace") {
  Dataspace s2;
  GIVEN("two default constructed dataspaces") {
    Dataspace s1;
    THEN("assignment fails") {
      REQUIRE_THROWS_AS((s2 = s1), std::runtime_error);
    }
  }

  GIVEN("a scalar dataspace from an hid_t") {
    auto s1 = Dataspace(ObjectHandle(H5Screate(H5S_SCALAR)));
    THEN("assignment construction should work") {
      s2 = s1;
      AND_THEN("the types must be the same") {
        REQUIRE(s1.type() == s2.type());
      }
      AND_THEN("the ids match") { 
        REQUIRE_FALSE(static_cast<hid_t>(s1) ==static_cast<hid_t>(s2));
      }
    }
    THEN("we can assign three objects from this") { 
      Dataspace s3 = s2 = s1;
      AND_THEN("the types must match") { 
        REQUIRE(s1.type() == s1.type());
        REQUIRE(s1.type() == s3.type());
      }
      AND_THEN("the is are different") { 
        REQUIRE_FALSE(static_cast<hid_t>(s1) == static_cast<hid_t>(s2));
        REQUIRE_FALSE(static_cast<hid_t>(s1) == static_cast<hid_t>(s3));
        REQUIRE_FALSE(static_cast<hid_t>(s2) == static_cast<hid_t>(s3));
      }
    }
  }
}