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

#include <catch2/catch.hpp>
#include <h5cpp/property/type_creation.hpp>
#include "../utilities.hpp"

namespace pl = hdf5::property;

SCENARIO("create a TypeCreationList property list") {
  GIVEN("a default constructed instance") {
    pl::TypeCreationList tcpl;
    THEN("the property list class will fit") {
      REQUIRE(tcpl.get_class() == pl::kDatatypeCreate);
    }
  }
  GIVEN("a handle to a type creation property list") {
    hdf5::ObjectHandle handle{H5Pcreate(to_hid(pl::kDatatypeCreate))};
    THEN("we can use this to construct a new instance") {
      REQUIRE_NOTHROW(pl::TypeCreationList{std::move(handle)});
    }
  }
  GIVEN("a handle to a group creation property list") {
    hdf5::ObjectHandle handle{H5Pcreate(to_hid(pl::kGroupCreate))};
    THEN("the instantiation of a TypeCreationList will fail") {
      REQUIRE_THROWS_AS(pl::TypeCreationList{std::move(handle)},
                        std::runtime_error);
    }
  }
}
