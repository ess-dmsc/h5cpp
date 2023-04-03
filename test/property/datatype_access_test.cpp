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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Aug 22, 2017
//

#include <catch2/catch_amalgamated.hpp>
#include <h5cpp/property/datatype_access.hpp>
#include <h5cpp/property/property_class.hpp>
#include "../utilities.hpp"
#include "utilities.hpp"

namespace pl = hdf5::property;

SCENARIO("constructing a DatatypeAccessList instance") {
  GIVEN("a default constructed instance") {
    pl::DatatypeAccessList dapl;
    THEN("we get") { REQUIRE(dapl.get_class() == pl::kDatatypeAccess); }
  }
  GIVEN("a handle to a datatype access property list") {
    auto handle = handle_from_class(pl::kDatatypeAccess);
    THEN("we can construct a list instance") {
      REQUIRE_NOTHROW(pl::DatatypeAccessList{std::move(handle)});
    }
  }
  GIVEN("a handle to a group access list") {
    auto handle = handle_from_class(pl::kGroupAccess);
    THEN(
        "any attemp to construct an instance from DatatypeAccessList must "
        "fail") {
      REQUIRE_THROWS_AS(pl::DatatypeAccessList{std::move(handle)},
                        std::runtime_error);
    }
  }
}
