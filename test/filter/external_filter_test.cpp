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
// Author: Jan Kotanski <jan.kotanski@desy.de>
//         Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Sep 3, 2019
//
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

using CdValues = std::vector<unsigned int>;
using Catch::Matchers::Equals;

SCENARIO("External filter LZ4") {
  const unsigned int FILTER_LZ4 = 32004;
  GIVEN("a filter instance") {
    filter::ExternalFilter filter(FILTER_LZ4, {0u, 0u});
    THEN("the id must be") {
      REQUIRE(filter.id() == static_cast<int>(FILTER_LZ4));
    }
    THEN("the filter parameters must be") {
      REQUIRE_THAT(filter.cd_values(), Equals(CdValues{0u, 0u}));
    }
  }
}

SCENARIO("External filter BitShuffle with LZ4") {
  const unsigned int FILTER_BITSHUFFLE = 32008;
  CdValues params{0u, 2u};
  GIVEN("a filter instance") {
    filter::ExternalFilter bfilter(FILTER_BITSHUFFLE, {0u, 2u});
    THEN("we can expect for the id") {
      REQUIRE(bfilter.id() == static_cast<int>(FILTER_BITSHUFFLE));
    }
    THEN("we get for the filter paramters") {
      REQUIRE_THAT(bfilter.cd_values(), Equals(params));
    }
    if (filter::is_filter_available(FILTER_BITSHUFFLE)) {
      AND_GIVEN("a dataset creation property list") {
        property::DatasetCreationList dcpl;
        WHEN("we appy the filter to the property list") {
          REQUIRE_NOTHROW(bfilter(dcpl));
          THEN("we can retrieve the filters back from the list") {
            filter::ExternalFilters filters;
            auto flags = filters.fill(dcpl);
            REQUIRE(filters.size() == 1lu);
            REQUIRE(flags.size() == 1lu);
            REQUIRE(flags[0] == filter::Availability::Mandatory);
            REQUIRE_THAT(filters[0].cd_values(), Equals(params));
            REQUIRE(filters[0].id() == static_cast<int>(FILTER_BITSHUFFLE));
            REQUIRE(filters[0].name() ==
                    "bitshuffle; see https://github.com/kiyo-masui/bitshuffle");
          }
        }
      }
    }
  }
}

SCENARIO("deflate filter as external filter") {
  CdValues params{8u};

  GIVEN("a filter instance") {
    filter::ExternalFilter filter(H5Z_FILTER_DEFLATE, params);
    AND_GIVEN("an instance of a dataset creation property list") {
      property::DatasetCreationList dcpl;
      WHEN("we apply the filter to the list") {
        filter(dcpl);
        AND_THEN("there should be one filter attached to the list") {
          REQUIRE(dcpl.nfilters() == 1u);
        }
        THEN("we can read the filter list from the property list") {
          filter::ExternalFilters filters;
          auto flags = filters.fill(dcpl);
          AND_THEN("we ge the following parameters") {
            REQUIRE(filters.size() == 1lu);
            REQUIRE(flags.size() == 1lu);
            REQUIRE(flags[0] == filter::Availability::Mandatory);
            REQUIRE_THAT(filters[0].cd_values(), Equals(params));
            REQUIRE(filters[0].id() == static_cast<int>(H5Z_FILTER_DEFLATE));
            REQUIRE(filters[0].name() == "deflate");
          }
        }
      }
    }
  }
}

SCENARIO("deflate and shuffle filters as external filter") {
  CdValues deflate_params{8u};
  CdValues shuffle_params{};
  GIVEN("a shuffle filter instance") {
    filter::Shuffle shuffle;
    AND_GIVEN("a deflate filter instance") {
      filter::ExternalFilter filter(H5Z_FILTER_DEFLATE, {8u});
      AND_GIVEN("a dataset creation property list") {
        property::DatasetCreationList dcpl;
        WHEN("we apply the two filters to the list") {
          filter(dcpl);
          shuffle(dcpl);
          THEN("two lists should be attached to the property list") {
            REQUIRE(dcpl.nfilters() == 2u);
          }
          THEN("we can read the filters back to an external filters instance") {
            filter::ExternalFilters filters;
            auto flags = filters.fill(dcpl);
            AND_THEN("we get") {
              REQUIRE(filters.size() == 2lu);
              REQUIRE(flags.size() == 2lu);
              REQUIRE(flags[0] == filter::Availability::Mandatory);
              REQUIRE(flags[1] == filter::Availability::Optional);
              REQUIRE_THAT(filters[0].cd_values(), Equals(deflate_params));
              REQUIRE(filters[0].id() == static_cast<int>(H5Z_FILTER_DEFLATE));
              REQUIRE(filters[0].name() == "deflate");
              REQUIRE(filters[0].is_decoding_enabled());
              REQUIRE(filters[0].is_encoding_enabled());
              REQUIRE_THAT(filters[1].cd_values(), Equals(shuffle_params));
              REQUIRE(filters[1].id() == static_cast<int>(H5Z_FILTER_SHUFFLE));
              REQUIRE(filters[1].is_decoding_enabled());
              REQUIRE(filters[1].is_encoding_enabled());
              REQUIRE(filters[1].name() == "shuffle");
            }
          }
        }
      }
    }
  }
}
