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
// Created on: Aug 21, 2017
//

#ifdef H5CPP_CATCH2_V2
#include <catch2/catch.hpp>
#else
#include <catch2/catch_all.hpp>
#endif
#include <h5cpp/datatype/types.hpp>
#include <h5cpp/property/link_creation.hpp>
#include <h5cpp/property/property_class.hpp>
#include "../utilities.hpp"
#include "utilities.hpp"

namespace pl = hdf5::property;
namespace tp = hdf5::datatype;

SCENARIO("LinkCreationList instantiation") {
  GIVEN("a default constructed list") {
    pl::LinkCreationList lcpl;
    THEN("we get the configuration") {
      REQUIRE(lcpl.get_class() == pl::kLinkCreate);
      REQUIRE_FALSE(lcpl.intermediate_group_creation());
    }
    WHEN("closing this instance") {
      close(lcpl);
      THEN("all methods must throw exceptions") {
        REQUIRE_THROWS_AS(lcpl.enable_intermediate_group_creation(),
                          std::runtime_error);
        REQUIRE_THROWS_AS(lcpl.disable_intermediate_group_creation(),
                          std::runtime_error);
        REQUIRE_THROWS_AS(lcpl.intermediate_group_creation(),
                          std::runtime_error);
      }
    }
  }
  GIVEN("a handle to a link creation property list") {
    auto handle = handle_from_class(pl::kLinkCreate);
    THEN("we can use this to construct a new instance") {
      REQUIRE_NOTHROW(pl::LinkCreationList{std::move(handle)});
    }
  }
  GIVEN("a handle to a group creation property list") {
    auto handle = handle_from_class(pl::kGroupCreate);
    THEN("then instantiation must fail") {
      REQUIRE_THROWS_AS(pl::LinkCreationList{std::move(handle)},
                        std::runtime_error);
    }
  }
}

SCENARIO("activate intermediate group creation on a LinkCreationList") {
  GIVEN("a default constructed list") {
    pl::LinkCreationList lcpl;
    THEN("we can activate intermediate group creation") {
      REQUIRE_NOTHROW(lcpl.enable_intermediate_group_creation());
      REQUIRE(lcpl.intermediate_group_creation());
      AND_THEN("turn it off again") {
        REQUIRE_NOTHROW(lcpl.disable_intermediate_group_creation());

        // How does this make sense ???
        REQUIRE_FALSE(lcpl.intermediate_group_creation());
      }
    }
  }
}
