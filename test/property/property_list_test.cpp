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
// Created on: Oct 23, 2017
//

#ifdef H5CPP_CATCH2_V2
#include <catch2/catch.hpp>
#else
#include <catch2/catch_all.hpp>
#endif
#include <h5cpp/property/property_list.hpp>

using namespace hdf5;
using namespace hdf5::property;

namespace pl = hdf5::property;

SCENARIO("basic property list construction and assignment") {
  GIVEN("a DatasetAccess class") {
    THEN("we can construct a valid property list from it") {
      List c{kDatasetAccess};
      REQUIRE(c.get_class().name() == kDatasetAccess.name());

      AND_WHEN("we copy construct another list from it") {
        List l2{c};
        THEN("the two lists will be of the same class") {
          REQUIRE(l2.get_class().name() == c.get_class().name());
        }
        THEN("they will be different objects") {
          REQUIRE(static_cast<hid_t>(c) != static_cast<hid_t>(l2));
        }
      }

      AND_GIVEN("a DatasetXfer property list") {
        List l3{kDatasetXfer};
        THEN("we can copy assign to this list") {
          l3 = c;
          REQUIRE(l3.get_class().name() == c.get_class().name());
          REQUIRE(static_cast<hid_t>(l3) != static_cast<hid_t>(c));
        }
      }
    }
  }
}
