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
#include <h5cpp/contrib/stl/stl.hpp>

using namespace hdf5;

SCENARIO("ScalaOffset filter tests") {
  GIVEN("a default constructed instance") {
    filter::ScaleOffset filter;
    THEN("we can expect") {
      REQUIRE(filter.id() == H5Z_FILTER_SCALEOFFSET);
      REQUIRE(filter.is_decoding_enabled());
      REQUIRE(filter.is_encoding_enabled());
    }
    THEN("we can set the scale type to FLOAT_DSCALE") {
      filter.scale_type(filter::ScaleOffset::ScaleType::FloatDScale);
      REQUIRE(filter.scale_type() == filter::ScaleOffset::ScaleType::FloatDScale);
    }
    THEN("we can set the scale factor to FLOAT_ESCALE") {
      filter.scale_type(filter::ScaleOffset::ScaleType::FloatEScale);
      REQUIRE(filter.scale_type() == filter::ScaleOffset::ScaleType::FloatEScale);
    }
    THEN("we can set the scale factor to 4") {
      filter.scale_factor(4);
      REQUIRE(filter.scale_factor() == 4);
    }
  }

  GIVEN("a filter constructed for integer") {
    filter::ScaleOffset scaleoffset(filter::ScaleOffset::ScaleType::Int, 2);
    THEN("the filter has the following properties") {
      REQUIRE(scaleoffset.scale_type() == filter::ScaleOffset::ScaleType::Int);
      REQUIRE(scaleoffset.scale_factor() == 2);
    }
    AND_GIVEN("a dataset creation property list") {
      property::DatasetCreationList dcpl;
      THEN("we can apply this filter to the property list") {
        scaleoffset(dcpl);
        REQUIRE(dcpl.nfilters() == 1u);

        AND_GIVEN("an external filter instance") {
          filter::ExternalFilters filters;
          THEN("we can load the filters back from the property list") {
            auto flags = filters.fill(dcpl);
            REQUIRE(filters.size() == 1lu);
            REQUIRE(flags.size() == 1lu);

            // check here the filter parameters
            REQUIRE(flags[0] == filter::Availability::Optional);
            using r = std::vector<unsigned int>;
            REQUIRE_THAT(filters[0].cd_values(), Catch::Matchers::Equals(r{2, 2}));
            REQUIRE(filters[0].is_decoding_enabled());
            REQUIRE(filters[0].is_encoding_enabled());
            REQUIRE(filters[0].id() ==
                    static_cast<int>(H5Z_FILTER_SCALEOFFSET));
            REQUIRE(filters[0].name() == "scaleoffset");
          }
        }
      }
    }
  }
}
