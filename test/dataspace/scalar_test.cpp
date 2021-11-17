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
// Created on: Aug 24, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

using Scalar = dataspace::Scalar;
using Type = dataspace::Type;
using Dataspace = dataspace::Dataspace;

template <typename T>
hid_t to_id(const T& object) {
  return static_cast<hid_t>(object);
}

SCENARIO("default construction of a scalar dataspace") {
  GIVEN("a default constructed dataspace") {
    Scalar space;
    THEN("the size is 1") { REQUIRE(space.size() == 1); }
    THEN("type must be scalar") { REQUIRE(space.type() == Type::Scalar); }
    THEN("the dimensions must be empty") {
      REQUIRE(space.current_dimensions().empty());
    }
  }
}

SCENARIO("construction from a hid_t") {
  GIVEN("a valid id for a scalar dataspace") {
    hid_t id = H5Screate(H5S_SCALAR);
    THEN("we can construct a scalar dataspace") {
      Scalar space{ObjectHandle(id)};
      AND_THEN("the size is 1") { REQUIRE(space.size() == 1); }
      AND_THEN("type must be scalar") { REQUIRE(space.type() == Type::Scalar); }
      AND_THEN("the dimensions must be empty") {
        REQUIRE(space.current_dimensions().empty());
      }
    }
  }

  GIVEN("the valid id for a simple dataspace") {
    hid_t id = H5Screate(H5S_SIMPLE);
    THEN("the construction of a scalar dataspace will fail") {
      REQUIRE_THROWS_AS(Scalar{ObjectHandle(id)}, std::runtime_error);
    }
  }
}

SCENARIO("copy construction of a scalar dataspace") {
  GIVEN("a default constructed scalar dataspace") {
    Scalar space1;
    THEN("we can copy construct from this") {
      Scalar space2(space1);
      AND_THEN("the new space must be valie") { REQUIRE(space2.is_valid()); }
      AND_THEN("the ids must be different") {
        REQUIRE_FALSE(to_id(space1) == to_id(space2));
      }
    }
    AND_GIVEN("a reference to a Dataspace") {
      Dataspace& s = space1;
      THEN("we can construct another scala instance form it") {
        Scalar space2(s);
        AND_THEN("the new dataspace must be valid") {
          REQUIRE(space2.is_valid());
        }
        AND_THEN("the ids must be different") {
          REQUIRE_FALSE(to_id(space2) == to_id(space1));
        }
      }
    }
  }

  GIVEN("a reference to a simple dataspace") {
    Dataspace s{ObjectHandle(H5Screate(H5S_SIMPLE))};
    THEN("the construction must fail") {
      REQUIRE_THROWS_AS(Scalar(s), std::runtime_error);
    }
  }
}

SCENARIO("scalar dataspace copy assignment") {
  GIVEN("a default constructed scalar dataspace") {
    Scalar space1;
    AND_GIVEN("a second scalar dataspace") {
      Scalar space2;
      auto space2_id = to_id(space2);  // keep the original id
      THEN("they must have different ids") {
        REQUIRE_FALSE(to_id(space1) == to_id(space2));
      }
      THEN("we can assign them to each other") {
        space2 = space1;
        AND_THEN("space2 must have a different id than before") {
          REQUIRE_FALSE(to_id(space1) == space2_id);
        }
      }
    }
    AND_GIVEN("a reference to a simple dataspace") {
      Dataspace simple{ObjectHandle(H5Screate(H5S_SIMPLE))};
      THEN("the assignment to an existing scalar space should fail") {
        REQUIRE_THROWS_AS((space1 = simple), std::runtime_error);
      }
    }
  }
}
