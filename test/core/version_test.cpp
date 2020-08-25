//
// (c) Copyright 2017 DESY,ESS
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
// Created on: Oct 11, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/core/hdf5_capi.hpp>
#include <h5cpp/core/version.hpp>
#include <sstream>

SCENARIO("Version construction", "[h5cpp]") {
  GIVEN("a default constructed version") {
    hdf5::Version v;
    THEN("all elements of the version are 0") {
      REQUIRE(v.major_number() == hdf5::Version::NumberType(0));
      REQUIRE(v.minor_number() == hdf5::Version::NumberType(0));
      REQUIRE(v.patch_number() == hdf5::Version::NumberType(0));
    }
  }

  GIVEN("the standard constructor with 10.0.2") {
    hdf5::Version v(10, 0, 2);
    THEN("the major version is 10") {
      REQUIRE(v.major_number() == hdf5::Version::NumberType(10));
    }
    THEN("the minor version is 0") {
      REQUIRE(v.minor_number() == hdf5::Version::NumberType(0));
    }
    THEN("the patch number is 2") {
      REQUIRE(v.patch_number() == hdf5::Version::NumberType(2));
    }
  }
}

SCENARIO("copying versions", "[h5cpp]") {
  GIVEN("a version 3.0.12") {
    hdf5::Version v1(3, 0, 12);
    WHEN("copy construct a new version") {
      hdf5::Version v2(v1);
      THEN("the versions must have equal elements") {
        REQUIRE(v1.major_number() == v2.major_number());
        REQUIRE(v1.minor_number() == v2.minor_number());
        REQUIRE(v1.patch_number() == v2.patch_number());
      }
    }
    WHEN("copy assign to a new version") {
      hdf5::Version v2;
      v2 = v1 THEN("the versions must have equal elements") {
        REQUIRE(v1.major_number() == v2.major_number());
        REQUIRE(v1.minor_number() == v2.minor_number());
        REQUIRE(v1.patch_number() == v2.patch_number());
      }
    }
  }
}



TEST(VersionTest, to_string) {
  hdf5::Version v(21, 0, 2);
  EXPECT_EQ(hdf5::Version::to_string(v), "21.0.2");
}

SCENARIO("comparison of versions") {
  GIVEN("Version 10.0.2") { 
    hdf5::Version v1(10,23,3); 
    WHEN("equality checked with 10.0.2") { 
      hdf5::Version v2(10,23,3);
      THEN("both versions are equal") { REQUIRE(v1 == v2);}
    }

    WHEN("checked against 10.1.2") {
      hdf5::Version v2(10,1,2);
      THEN("the versions are not equal") { REQUIRE(v1 != v2);}
    }
  }

  GIVEN("version 10.12.1") { 
    hdf5::Version v1(10,23,0)
    THEN("version 10.12.1 >= 10.12.1") 
  }
}


TEST(VersionTest, inequality) {
  EXPECT_NE(hdf5::Version(10, 23, 0), hdf5::Version(10, 23, 1));
  EXPECT_NE(hdf5::Version(10, 0, 1), hdf5::Version(10, 1, 1));
  EXPECT_NE(hdf5::Version(0, 10, 1), hdf5::Version(1, 10, 1));
}

TEST(VersionTest, greater_equal_than) {
  EXPECT_GE(hdf5::Version(10, 12, 1), hdf5::Version(10, 12, 1));
  EXPECT_GE(hdf5::Version(10, 12, 1), hdf5::Version(10, 12, 0));
  EXPECT_GE(hdf5::Version(10, 12, 1), hdf5::Version(10, 11, 0));
  EXPECT_GE(hdf5::Version(10, 12, 1), hdf5::Version(9, 111, 2));
}

TEST(VersionTest, greater_than) {
  EXPECT_GT(hdf5::Version(10, 12, 1), hdf5::Version(10, 12, 0));
  EXPECT_GT(hdf5::Version(10, 12, 1), hdf5::Version(10, 11, 0));
  EXPECT_GT(hdf5::Version(10, 12, 1), hdf5::Version(9, 111, 2));
  EXPECT_FALSE(hdf5::Version(10, 12, 1) > hdf5::Version(10, 12, 2));
  EXPECT_FALSE(hdf5::Version(10, 12, 1) > hdf5::Version(10, 13, 2));
  EXPECT_FALSE(hdf5::Version(10, 12, 1) > hdf5::Version(11, 12, 2));
}

TEST(VersionTest, less_equal_than) {
  EXPECT_LE(hdf5::Version(10, 12, 1), hdf5::Version(10, 12, 1));
  EXPECT_LE(hdf5::Version(10, 12, 0), hdf5::Version(10, 12, 1));
  EXPECT_LE(hdf5::Version(10, 11, 0), hdf5::Version(10, 12, 1));
  EXPECT_LE(hdf5::Version(9, 111, 2), hdf5::Version(10, 12, 1));
}

TEST(VersionTest, less_than) {
  EXPECT_LT(hdf5::Version(10, 12, 0), hdf5::Version(10, 12, 1));
  EXPECT_LT(hdf5::Version(10, 11, 0), hdf5::Version(10, 12, 1));
  EXPECT_LT(hdf5::Version(9, 111, 2), hdf5::Version(10, 12, 1));
  EXPECT_FALSE(hdf5::Version(10, 12, 1) < hdf5::Version(10, 12, 0));
  EXPECT_FALSE(hdf5::Version(10, 12, 1) < hdf5::Version(10, 11, 1));
  EXPECT_FALSE(hdf5::Version(10, 12, 1) < hdf5::Version(9, 12, 1));
}

TEST(VersionTest, current_library_version) {
  hdf5::Version current = hdf5::current_library_version();
  EXPECT_EQ(current.major_number(), hdf5::Version::NumberType(H5_VERS_MAJOR));
  EXPECT_EQ(current.minor_number(), hdf5::Version::NumberType(H5_VERS_MINOR));
  EXPECT_EQ(current.patch_number(), hdf5::Version::NumberType(H5_VERS_RELEASE));
}

TEST(VersionTest, stream) {
  hdf5::Version v(21, 0, 2);
  std::stringstream ss;
  ss << v;
  EXPECT_EQ(ss.str(), hdf5::Version::to_string(v));
}
