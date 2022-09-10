//
// (c) Copyright 2017 DESY,ESS
//               2021 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Nov 22, 2017
//
#include <catch2/catch.hpp>
#include <h5cpp/h5cpp.hpp>

using namespace hdf5;

SCENARIO("testing the is_group and is_dataset functions") {
  auto f = file::create("is_group_test.h5", file::AccessFlags::Truncate);
  GIVEN("a default constructed node") {
    node::Node n;
    THEN("is_group and is_dataset will throw an exception") {
      REQUIRE_THROWS_AS(node::is_group(n), std::runtime_error);
      REQUIRE_THROWS_AS(node::is_dataset(n), std::runtime_error);
    }
  }
  GIVEN("a group") {
    THEN("is_group will return true") { REQUIRE(node::is_group(f.root())); }
    THEN("is_dataset will return false") {
      REQUIRE_FALSE(node::is_dataset(f.root()));
    }
  }
  GIVEN("a dataset") {
    node::Dataset dset(f.root(), hdf5::Path("data"),
                       hdf5::datatype::create<int>());
    THEN("is_group will return false") { REQUIRE_FALSE(node::is_group(dset)); }
    THEN("is_dataset will return true") { 
      REQUIRE(node::is_dataset(dset));
    }
  }
}
