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
// Created on: Aug 17, 2017
//

#ifdef H5CPP_CATCH2_V2
#include <catch2/catch.hpp>
#else
#include <catch2/catch_all.hpp>
#endif
#include <h5cpp/hdf5.hpp>
#include <h5cpp/property/object_creation.hpp>
#include <h5cpp/property/property_class.hpp>
#include "../utilities.hpp"

namespace pl = hdf5::property;

SCENARIO("Constructing an ObjectCreationList") {
  WHEN("default constructing") {
    pl::ObjectCreationList ocpl;
    THEN("the list will be of class ObjectCreate") {
      REQUIRE(ocpl.get_class() == pl::kObjectCreate);
    }

    AND_WHEN("closing this list") {
      close(ocpl);
      THEN("all methods fail") {
        REQUIRE_THROWS_AS(ocpl.enable_time_tracking(), std::runtime_error);
        REQUIRE_THROWS_AS(ocpl.disable_time_tracking(), std::runtime_error);
        REQUIRE_THROWS_AS(ocpl.time_tracking(), std::runtime_error);
        REQUIRE_THROWS_AS(ocpl.attribute_creation_order(), std::runtime_error);
        REQUIRE_THROWS_AS(
            ocpl.attribute_creation_order(pl::CreationOrder().enable_tracked()),
            std::runtime_error);
        REQUIRE_THROWS_AS(ocpl.attribute_storage_maximum_compact(),
                          std::runtime_error);
        REQUIRE_THROWS_AS(ocpl.attribute_storage_minimum_dense(),
                          std::runtime_error);
      }
    }
  }
  WHEN("trying to construct from a wrong handle") {
    auto handle = hdf5::ObjectHandle(H5Pcreate(to_hid(pl::kGroupAccess)));
    THEN("the creation process fails") {
      REQUIRE_THROWS_AS(pl::ObjectCreationList(std::move(handle)),
                        std::runtime_error);
    }
  }
}

SCENARIO("tesing configuration on ObjectCreationList") {
  GIVEN("a default constructed list") {
    pl::ObjectCreationList ocpl;

    WHEN("enable time tracking") {
      REQUIRE_NOTHROW(ocpl.enable_time_tracking());
      THEN("then the flag will be set") { REQUIRE(ocpl.time_tracking()); }
      AND_WHEN("disabling it again") {
        REQUIRE_NOTHROW(ocpl.disable_time_tracking());
        THEN("the flag will be cleared again") {
          REQUIRE_FALSE(ocpl.time_tracking());
        }
      }
    }
    AND_GIVEN("tracked creation order") {
      auto co = pl::CreationOrder().enable_tracked();
      WHEN("setting the creating order") {
        REQUIRE_NOTHROW(ocpl.attribute_creation_order(co));
        THEN("set get for the creation order") {
          REQUIRE(ocpl.attribute_creation_order().tracked());
          REQUIRE_FALSE(ocpl.attribute_creation_order().indexed());
        }
      }
    }

    AND_GIVEN("indexed creation order") {
      auto co = pl::CreationOrder().enable_indexed();
      WHEN("setting the creation order") {
        REQUIRE_NOTHROW(ocpl.attribute_creation_order(co));
        THEN("get for the creation order") {
          REQUIRE(ocpl.attribute_creation_order().tracked());
          REQUIRE(ocpl.attribute_creation_order().indexed());
        }
      }
    }

    WHEN("settting the storage thresholds") {
      REQUIRE_NOTHROW(ocpl.attribute_storage_thresholds(100, 50));
      THEN("we get for the thresholds") {
        REQUIRE(ocpl.attribute_storage_maximum_compact() == 100ul);
        REQUIRE(ocpl.attribute_storage_minimum_dense() == 50ul);
      }
    }

    WHEN("trying to set the storage thresholds wrong") {
      REQUIRE_THROWS_AS(ocpl.attribute_storage_thresholds(50, 100),
                        std::runtime_error);
    }
  }
}
