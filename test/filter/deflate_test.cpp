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
// Created on: Nov 6, 2017
//
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/contrib/stl/stl.hpp>
#include "../utilities.hpp"

using namespace hdf5;

SCENARIO("DeflateFilter construction") {
  GIVEN("a default constructed filter ") {
    filter::Deflate filter;
    REQUIRE(filter.id() == H5Z_FILTER_DEFLATE);
    REQUIRE(filter.level() == 0u);
    WHEN("trying to set an invalid level") { 
      THEN("the operation will fail") { 
        REQUIRE_THROWS_AS(filter.level(10), std::runtime_error);
      }
    }
  }
  GIVEN("a filter constructed from the compression level") {
    filter::Deflate filter(7u);
    REQUIRE(filter.level() == 7u);
    REQUIRE(filter.id() == H5Z_FILTER_DEFLATE);
    AND_GIVEN("a dataset creation property list") {
      property::DatasetCreationList dcpl;
      THEN("we can set the filter on the property list") {
        filter(dcpl);
        AND_THEN("the list should have one filter attached to it") {
          REQUIRE(H5Pget_nfilters(to_hid(dcpl)) == 1);
        }
      }
    }
  }
  WHEN("we try to construct the filter with an invalid level") { 
    THEN("the construction will fail") { 
      REQUIRE_THROWS_AS(filter::Deflate(10), std::runtime_error);
    }
  }
}
