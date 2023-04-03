
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
// Created on: Aug 17, 2017
//
#include <catch2/catch_all.hpp>
#include <h5cpp/property/group_creation.hpp>
#include <h5cpp/property/property_class.hpp>
#include "../utilities.hpp"

namespace pl = hdf5::property;

SCENARIO("construction of a GroupCreationList") {
  GIVEN("a default constructed list") {
    pl::GroupCreationList gcpl;
    THEN("the property list class must match") {
      REQUIRE(gcpl.get_class() == pl::kGroupCreate);
    }
    THEN("the property list has the following default configuration") {
      REQUIRE(gcpl.local_heap_size_hint() == 0);
      REQUIRE(gcpl.estimated_number_of_links() == 4);
      REQUIRE(gcpl.estimated_link_name_length() == 8);
      REQUIRE_FALSE(gcpl.link_creation_order().indexed());
      REQUIRE_FALSE(gcpl.link_creation_order().tracked());
    }
    WHEN("closing the property list") {
      close(gcpl);
      THEN("calling any of the member methods will fail") {
        REQUIRE_THROWS_AS(gcpl.local_heap_size_hint(512ul), std::runtime_error);
        REQUIRE_THROWS_AS(gcpl.local_heap_size_hint(), std::runtime_error);
        REQUIRE_THROWS_AS(gcpl.estimated_number_of_links(33),
                          std::runtime_error);
        REQUIRE_THROWS_AS(gcpl.estimated_number_of_links(), std::runtime_error);
        REQUIRE_THROWS_AS(gcpl.estimated_link_name_length(64),
                          std::runtime_error);
        REQUIRE_THROWS_AS(gcpl.estimated_link_name_length(),
                          std::runtime_error);
        REQUIRE_THROWS_AS(
            gcpl.link_creation_order(pl::CreationOrder().enable_tracked()),
            std::runtime_error);
        REQUIRE_THROWS_AS(gcpl.link_creation_order(), std::runtime_error);
        REQUIRE_THROWS_AS(gcpl.link_storage_maximum_compact(),
                          std::runtime_error);
        REQUIRE_THROWS_AS(gcpl.link_storage_minimum_dense(),
                          std::runtime_error);
      }
    }
  }
  GIVEN("a handle to a group creation list") {
    hdf5::ObjectHandle handle{H5Pcreate(to_hid(pl::kGroupCreate))};
    THEN("a new instance can be constructed from it") {
      REQUIRE_NOTHROW(pl::GroupCreationList{std::move(handle)});
    }
  }
  GIVEN("a handle to a datatype creation list") {
    hdf5::ObjectHandle handle{H5Pcreate(to_hid(pl::kDatatypeCreate))};
    THEN("the construction of a property list fails") {
      REQUIRE_THROWS_AS(pl::GroupCreationList{std::move(handle)},
                        std::runtime_error);
    }
  }
}

SCENARIO("setting the parameters on a GroupCreationList") {
  pl::GroupCreationList gcpl;
  WHEN("setting the local heap size hint to 1024") {
    REQUIRE_NOTHROW(gcpl.local_heap_size_hint(1024));
    THEN("the value should be set") {
      REQUIRE(gcpl.local_heap_size_hint() == 1024ul);
    }
  }
  WHEN("setting the estimated number of links") {
    REQUIRE_NOTHROW(gcpl.estimated_number_of_links(10));
    THEN("the value should be set") {
      REQUIRE(gcpl.estimated_number_of_links() == 10);
    }
  }
  WHEN("setting the length of link name") {
    REQUIRE_NOTHROW(gcpl.estimated_link_name_length(64));
    THEN("the value should be set accordingly") {
      REQUIRE(gcpl.estimated_link_name_length() == 64);
    }
  }
  GIVEN("a creation order flag") {
    pl::CreationOrder order;
    THEN("we can enable indexed on the flag") {
      order.enable_indexed();
      WHEN("we set this to the GroupCreationList") {
        gcpl.link_creation_order(order);
        AND_THEN("we can read them back") {
          auto flags = gcpl.link_creation_order();
          REQUIRE(flags.tracked());
          REQUIRE(flags.indexed());
        }
      }
    }
    THEN("we can enable the tracked flag") {
      order.enable_tracked();
      WHEN("we set this to the GroupCreationList") {
        gcpl.link_creation_order(order);
        AND_THEN("we can read them back") {
          auto flags = gcpl.link_creation_order();
          REQUIRE(flags.tracked());
          REQUIRE_FALSE(flags.indexed());
        }
      }
    }
  }
  GIVEN("a links storage threshold of 100 and 60") {
    unsigned int max_compact_threshold = 100;
    unsigned int min_dense_threshold = 60;
    WHEN("we set the thresholds") {
      REQUIRE_NOTHROW(gcpl.link_storage_thresholds(100, 60));
      THEN("we can read tem back") {
        REQUIRE(gcpl.link_storage_maximum_compact() == max_compact_threshold);
        REQUIRE(gcpl.link_storage_minimum_dense() == min_dense_threshold);
      }
    }
    WHEN("we apply the thresholds in the wrong order the setting fails") {
      REQUIRE_THROWS_AS(gcpl.link_storage_thresholds(min_dense_threshold,
                                                     max_compact_threshold),
                        std::runtime_error);
    }
  }
}
