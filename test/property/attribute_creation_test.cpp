//
// (c) Copyright 2017 DESY,ESS
//               2020 Eugen Wintersberger <eugen.wintersbeger@gmail.com>
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

#include <catch2/catch.hpp>
#include <h5cpp/datatype/types.hpp>
#include <h5cpp/property/attribute_creation.hpp>
#include <h5cpp/property/property_class.hpp>
#include "../utilities.hpp"
#include "utilities.hpp"

namespace pl = hdf5::property;
namespace tp = hdf5::datatype;

SCENARIO("instantiating AttributeCreationList") {
  GIVEN("a default constructed instance") {
    pl::AttributeCreationList acpl;
    THEN("we get") { REQUIRE(acpl.get_class() == pl::kAttributeCreate); }
  }
  GIVEN("a handle to a attribute creation property list") {
    auto handle = handle_from_class(pl::kAttributeCreate);
    THEN("we can construct an instance from this handle") {
      REQUIRE_NOTHROW(pl::AttributeCreationList{std::move(handle)});
    }
  }
  GIVEN("a handle to a string creation property list") {
    auto handle = handle_from_class(pl::kStringCreate);
    THEN("instantiation must fail") {
      REQUIRE_THROWS_AS(pl::AttributeCreationList{std::move(handle)},
                        std::runtime_error);
    }
  }
}