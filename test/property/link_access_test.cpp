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

#include <catch2/catch_amalgamated.hpp>
#include <h5cpp/property/link_access.hpp>
#include <h5cpp/property/property_class.hpp>
#include <h5cpp/core/utilities.hpp>
#include "../utilities.hpp"
#include "utilities.hpp"

namespace pl = hdf5::property;

SCENARIO("creating an instance of LinkAccessList") {
  GIVEN("a default constructed instance") {
    pl::LinkAccessList lapl;
    THEN("the class must be LinkAccess") {
      REQUIRE(lapl.get_class() == pl::kLinkAccess);
    }
    WHEN("closing this instance") {
      close(lapl);
      THEN("all requests to the variable fails") {
        REQUIRE_THROWS_AS(lapl.maximum_link_traversals(2000),
                          std::runtime_error);
        REQUIRE_THROWS_AS(lapl.maximum_link_traversals(), std::runtime_error);
        REQUIRE_THROWS_AS(lapl.external_link_prefix("/home/wintersb"),
                          std::runtime_error);
      }
    }
  }
  GIVEN("a handle to a link access list") {
    auto handle = handle_from_class(pl::kLinkAccess);
    THEN("we can construct a new list from this") {
      REQUIRE_NOTHROW(pl::LinkAccessList{std::move(handle)});
    }
  }
  GIVEN("a handle to a group access list") {
    auto handle = handle_from_class(pl::kGroupCreate);
    THEN("construction of a new LinkAccessList fails") {
      REQUIRE_THROWS_AS(pl::LinkAccessList{std::move(handle)},
                        std::runtime_error);
    }
  }
}

SCENARIO("setting the maximum traversal on a LinkAccessList") {
  pl::LinkAccessList lapl;
  GIVEN("valid values for the maximum link traversal") {
    auto m = GENERATE(1000, 2000);
    THEN("we can set the maximum link traversal to this value") {
      REQUIRE_NOTHROW(lapl.maximum_link_traversals(signed2unsigned<size_t>(m)));
      AND_THEN("check its value") {
        REQUIRE(lapl.maximum_link_traversals() == signed2unsigned<size_t>(m));
      }
    }
  }
}

SCENARIO("setting the external link prefix on a LinkAccessList") {
  pl::LinkAccessList lapl;
  GIVEN("a prefix value") {
#ifndef _MSC_VER
    std::string prefix = "/home/wintersb";
#else
    std::string prefix = "C:\\home\\wintersb";
#endif
    THEN("we can set this to the list") {
      REQUIRE_NOTHROW(lapl.external_link_prefix(prefix));
      AND_THEN("read it back") {
        REQUIRE(lapl.external_link_prefix().string() == prefix);
      }
    }
  }
}
