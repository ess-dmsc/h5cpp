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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: May 14, 2018
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/contrib/nexus/ebool.hpp>


using namespace hdf5;



SCENARIO("Custom enumeration trait construction") {

  GIVEN("the EBool type") {
    auto type = datatype::create<datatype::EBool>();
    THEN("we can get the names by index") {
      REQUIRE(type.name(0) == "FALSE");
      REQUIRE(type.name(1) == "TRUE");
    }
    THEN("we can obtain the values by index") {
      REQUIRE(type.value<datatype::EBool>(0) == datatype::EBool::False);
      REQUIRE(type.value<datatype::EBool>(1) == datatype::EBool::True);
    }
  }
}

SCENARIO("Custom enumeration trait construction with cref") {
  GIVEN("the EBool type") {
    auto type = datatype::Enum(datatype::get<datatype::EBool>());
    THEN("we can get the names by index") {
      REQUIRE(type.name(0) == "FALSE");
      REQUIRE(type.name(1) == "TRUE");
    }
    THEN("we can obtain the values by index") {
      REQUIRE(type.value<datatype::EBool>(0) == datatype::EBool::False);
      REQUIRE(type.value<datatype::EBool>(1) == datatype::EBool::True);
    }
  }
}


SCENARIO("testing EBOOL IO") {
  auto f = file::create("ebool_attribute_test.h5", file::AccessFlags::Truncate);
  auto root = f.root();
  auto type = datatype::create<datatype::EBool>();

  GIVEN("an EBOOL attribute") {
    auto a = root.attributes.create<datatype::EBool>("TRUE");
    AND_GIVEN("an actual true value") {
      auto write_ebool = datatype::EBool::True;
      THEN("we can write this to the attribute") {
        a.write(write_ebool);
        AND_WHEN("we read the value back") {
          auto read_ebool = datatype::EBool::False;
          a.read(read_ebool);
          THEN("the values should match") {
            REQUIRE(write_ebool == read_ebool);
            REQUIRE(1 == read_ebool);
            REQUIRE(true == static_cast<bool>(read_ebool));
          }
        }
      }
    }
  }

  GIVEN("another EBOOL attribute") {
    auto a = root.attributes.create<datatype::EBool>("FALSE");
    AND_GIVEN("an actual false value") {
      auto write_ebool = datatype::EBool::False;
      THEN("we can write this to the attribute") {
        a.write(write_ebool);
        AND_WHEN("we read the value back") {
          auto read_ebool = datatype::EBool::False;
          a.read(read_ebool);
          THEN("the values should match") {
            REQUIRE(write_ebool == read_ebool);
            REQUIRE(0 == read_ebool);
            REQUIRE(false == static_cast<bool>(read_ebool));
          }
        }
      }
    }
  }

  GIVEN("an EBool array attribute") {
    auto a = root.attributes.create<datatype::EBool>("bool_array", {4});

    AND_GIVEN("a vector of bool values") {
      std::vector<datatype::EBool> ref = {
          datatype::EBool::False, datatype::EBool::True, datatype::EBool::True,
          datatype::EBool::False};
      THEN("we can write the values") {
        a.write(ref);
        AND_WHEN("we read them back to EBool") {
          std::vector<datatype::EBool> buffer(4);
          a.read(buffer, a.datatype());
          THEN("the values must match") {
            REQUIRE_THAT(ref, Catch::Matchers::Equals(buffer));
          }
        }
        AND_WHEN("we read them back to integer") {
          std::vector<int> buffer_int(4);
          a.read(buffer_int);
          THEN("the values should match the integers") {
            std::vector<int> ref_int = {0, 1, 1, 0};
            REQUIRE_THAT(ref_int, Catch::Matchers::Equals(buffer_int));
          }
        }
      }
    }
  }
}

SCENARIO("testing EBOOL IO with cref") {
  auto f = file::create("ebool_attribute_test.h5", file::AccessFlags::Truncate);
  auto root = f.root();
  auto type = datatype::get<datatype::EBool>();

  GIVEN("an EBOOL attribute") {
    auto a = root.attributes.create<datatype::EBool>("TRUE");
    AND_GIVEN("an actual true value") {
      auto write_ebool = datatype::EBool::True;
      THEN("we can write this to the attribute") {
        a.write(write_ebool);
        AND_WHEN("we read the value back") {
          auto read_ebool = datatype::EBool::False;
          a.read(read_ebool);
          THEN("the values should match") {
            REQUIRE(write_ebool == read_ebool);
            REQUIRE(1 == read_ebool);
            REQUIRE(true == static_cast<bool>(read_ebool));
          }
        }
      }
    }
  }

  GIVEN("another EBOOL attribute") {
    auto a = root.attributes.create<datatype::EBool>("FALSE");
    AND_GIVEN("an actual false value") {
      auto write_ebool = datatype::EBool::False;
      THEN("we can write this to the attribute") {
        a.write(write_ebool);
        AND_WHEN("we read the value back") {
          auto read_ebool = datatype::EBool::False;
          a.read(read_ebool);
          THEN("the values should match") {
            REQUIRE(write_ebool == read_ebool);
            REQUIRE(0 == read_ebool);
            REQUIRE(false == static_cast<bool>(read_ebool));
          }
        }
      }
    }
  }

  GIVEN("an EBool array attribute") {
    auto a = root.attributes.create<datatype::EBool>("bool_array", {4});

    AND_GIVEN("a vector of bool values") {
      std::vector<datatype::EBool> ref = {
          datatype::EBool::False, datatype::EBool::True, datatype::EBool::True,
          datatype::EBool::False};
      THEN("we can write the values") {
        a.write(ref);
        AND_WHEN("we read them back to EBool") {
          std::vector<datatype::EBool> buffer(4);
          a.read(buffer, a.datatype());
          THEN("the values must match") {
            REQUIRE_THAT(ref, Catch::Matchers::Equals(buffer));
          }
        }
        AND_WHEN("we read them back to integer") {
          std::vector<int> buffer_int(4);
          a.read(buffer_int);
          THEN("the values should match the integers") {
            std::vector<int> ref_int = {0, 1, 1, 0};
            REQUIRE_THAT(ref_int, Catch::Matchers::Equals(buffer_int));
          }
        }
      }
    }
  }
}
