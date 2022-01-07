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
//         Eugen Wintersberger <eugen.wintersberger@gmail.com>
//         Jan Kotanski <jan.kotanski@desy.de>
// Created on: Dec 20, 2020
//
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

SCENARIO("testing the NBit filter") {
  GIVEN("a default constructed instance") {
    filter::NBit filter;
    THEN("we get for the id") {
      REQUIRE(filter.id() == H5Z_FILTER_NBIT);
      REQUIRE(filter.is_decoding_enabled());
      REQUIRE(filter.is_encoding_enabled());
    }
    AND_GIVEN("a dataset creation property list") {
      property::DatasetCreationList dcpl;
      if (filter::is_filter_available(H5Z_FILTER_NBIT)) {
        WHEN("we apply the filter to the list") {
          filter(dcpl);
          THEN("there should be on  filter attached to the list") {
            REQUIRE(dcpl.nfilters() == 1u);
          }
          AND_GIVEN("an external filter instance") {
            filter::ExternalFilters filters;
            THEN("we can load the filter into it") {
              auto flags = filters.fill(dcpl);
              REQUIRE(filters.size() == 1lu);
              REQUIRE(flags.size() == 1lu);
              REQUIRE(flags[0] == filter::Availability::Optional);
              REQUIRE_THAT(filters[0].cd_values(),
                           Catch::Matchers::Equals(std::vector<unsigned int>{}));
              REQUIRE(filters[0].is_decoding_enabled());
              REQUIRE(filters[0].is_encoding_enabled());
              REQUIRE(filters[0].id() == static_cast<int>(H5Z_FILTER_NBIT));
              REQUIRE(filters[0].name() == "nbit");
            }
          }
        }
      }
    }
  }
}
