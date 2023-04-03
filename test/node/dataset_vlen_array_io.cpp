//
// (c) Copyright 2017 DESY,ESS
//               2021 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Created on: Oct 23, 2017
//
#include <algorithm>
#include <catch2/catch_all.hpp>
#include <examples/h5cpp/hklpoint.hpp>
#include <examples/hklpoint.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

SCENARIO("reading and writing an HKL list") {
  using Catch::Matchers::Equals;
  auto f = file::create("read_write_hkl_list.h5", file::AccessFlags::Truncate);

  GIVEN("a list of HKL Points") {
    HKLPoints write_points{{{1, 2, 3}, {3, 4, 5}, {6, 7, 8}}, {{4, 5, 6}}};
    AND_GIVEN("a dataset able of storing such a list") {
      node::Dataset dset(f.root(), Path("data"),
                         datatype::create<HKLPointList>(),
                         dataspace::Simple({2}));
      THEN("we can write the points to the dataset") {
        dset.write(write_points);
        AND_THEN("we can read the data back") {
          HKLPoints read_points(2);
          dset.read(read_points);
          REQUIRE_THAT(read_points[0],
                       Equals(HKLPointList({{1, 2, 3}, {3, 4, 5}, {6, 7, 8}})));
          REQUIRE_THAT(read_points[1],
                        Equals(HKLPointList({{4, 5, 6}})));
        }
      }
    }
  }

}
