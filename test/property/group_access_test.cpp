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
// Created on: Aug 22, 2017
//

#ifdef H5CPP_CATCH2_V2
#include <catch2/catch.hpp>
#else
#include <catch2/catch_all.hpp>
#endif
#include <h5cpp/property/group_access.hpp>
#include <h5cpp/property/property_class.hpp>
#include "../utilities.hpp"
#include "utilities.hpp"

namespace pl = hdf5::property;

SCENARIO("creating an instance of a GroupAccessList class") {
  GIVEN("a default constructed instance") {
    pl::GroupAccessList gapl;
    THEN("we get") { REQUIRE(gapl.get_class() == pl::kGroupAccess); }
  }
  GIVEN("a handle to a group access property list") {
    auto handle = handle_from_class(pl::kGroupAccess);
    THEN("we can construct an instance from this handle") {
      REQUIRE_NOTHROW(pl::GroupAccessList{std::move(handle)});
    }
  }
  GIVEN("a handle to a group create property list") {
    auto handle = handle_from_class(pl::kGroupCreate);
    THEN("instantiation fails") {
      REQUIRE_THROWS_AS(pl::GroupAccessList{std::move(handle)},
                        std::runtime_error);
    }
  }
}
