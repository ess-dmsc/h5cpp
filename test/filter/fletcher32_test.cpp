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
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/contrib/stl/stl.hpp>
#include "../utilities.hpp"

using namespace hdf5;

SCENARIO("using the Fletcher32 filter") {
  GIVEN("a default constructed filter") {
    filter::Fletcher32 filter;
    REQUIRE(filter.id() == H5Z_FILTER_FLETCHER32);
    AND_GIVEN("a dataset creation property list") {
      property::DatasetCreationList dcpl;
      WHEN("we add the filter to the list") {
        filter(dcpl);
        THEN("the list should have one filter attached") {
          REQUIRE(H5Pget_nfilters(to_hid(dcpl)) == 1);
        }
      }
    }
  }
}
