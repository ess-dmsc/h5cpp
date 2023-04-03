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

#include <catch2/catch_all.hpp>
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
      v2 = v1;
      THEN("the versions must have equal elements") {
        REQUIRE(v1.major_number() == v2.major_number());
        REQUIRE(v1.minor_number() == v2.minor_number());
        REQUIRE(v1.patch_number() == v2.patch_number());
      }
    }
  }
}

SCENARIO("output a versin") {
  GIVEN("the version 21.0.2") {
    hdf5::Version v(21, 0, 2);
    THEN("string conversion yields") {
      REQUIRE(hdf5::Version::to_string(v) == "21.0.2");
    }

    WHEN("written to a stream") {
      std::stringstream ss;
      ss << v;
      THEN("the stream contains a string") {
        REQUIRE(ss.str() == hdf5::Version::to_string(v));
      }
    }
  }
}

SCENARIO("comparison of versions") {
  GIVEN("Version 10.23.3") {
    hdf5::Version v1(10, 23, 3);
    WHEN("equality checked with 10.23.3") {
      hdf5::Version v2(10, 23, 3);
      THEN("both versions are equal") { REQUIRE(v1 == v2); }
    }

    WHEN("checked for inequality") {
      THEN("10.23.3 != 10.23.2") { REQUIRE(v1 != hdf5::Version(10, 23, 1)); }
      THEN("10.23.3 != 9.23.3") { REQUIRE(v1 != hdf5::Version(9, 23, 3)); }
    }
  }

  GIVEN("version 10.12.1") {
    hdf5::Version v(10, 12, 1);
    THEN("10.12.1 >= 10.12.1 ") { REQUIRE(v >= hdf5::Version(10, 12, 1)); }
    THEN("10.12.1 >= 10.12.0") { REQUIRE(v >= hdf5::Version(10, 12, 0)); }
    THEN("10.12.1 >= 10.11.0") { REQUIRE(v >= hdf5::Version(10, 11, 0)); }
    THEN("10.12.1 >= 9.111.2") { REQUIRE(v >= hdf5::Version(9, 111, 2)); }

    THEN("10.12.1 > 10.12.0") { REQUIRE(v > hdf5::Version(10, 12, 0)); }
    THEN("10.12.1 > 10.11.0") { REQUIRE(v > hdf5::Version(10, 11, 0)); }
    THEN("10.12.1 > 9.11.2") { REQUIRE(v > hdf5::Version(9, 111, 2)); }

    THEN("10.12.1 <= 10.12.1 ") { REQUIRE(v <= hdf5::Version(10, 12, 1)); }
    THEN("10.12.1 < 10.12.1") { REQUIRE(v < hdf5::Version(10, 12, 2)); }
    THEN("10.12.1 < 10.13.2") { REQUIRE(v < hdf5::Version(10, 13, 2)); }
    THEN("10.12.1 < 11.12.1") { REQUIRE(v < hdf5::Version(11, 12, 2)); }
  }
}

SCENARIO("the current version would be", "[h5cpp]") {
  hdf5::Version current = hdf5::current_library_version();
  REQUIRE(current.major_number() == hdf5::Version::NumberType(H5_VERS_MAJOR));
  REQUIRE(current.minor_number() == hdf5::Version::NumberType(H5_VERS_MINOR));
  REQUIRE(current.patch_number() == hdf5::Version::NumberType(H5_VERS_RELEASE));
}
