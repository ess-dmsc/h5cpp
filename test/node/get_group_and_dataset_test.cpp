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
// Created on: Nov 22, 2017
//
#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

SCENARIO("testing the get_group function") {
  auto f = file::create("get_group_test.h5", file::AccessFlags::TRUNCATE);

  GIVEN("a default constructed node") {
    node::Node n;
    THEN("get_group and get_dataset must throw an exception") {
      REQUIRE_THROWS_AS(node::get_group(n, "/data"), std::runtime_error);
      REQUIRE_THROWS_AS(node::get_dataset(n, "/data"), std::runtime_error);
    }
  }

  GIVEN("a dataset") {
    node::Dataset dset(f.root(), "data", datatype::create<int>());
    THEN("get_group must throw an exception") {
      REQUIRE_THROWS_AS(node::get_group(f.root(), "/data"), std::runtime_error);
    }
    THEN("get_dataset must return the dataset") {
      REQUIRE(node::get_dataset(f.root(), "/data").link().path() == "/data");
      REQUIRE(node::get_dataset(f.root(), "data").link().path() == "/data");
    }
  }

  GIVEN("a hierarchy of groups") {
    f.root().create_group("run_001").create_group("instrument");
    f.root().create_group("run_002").create_group("detector");
    WHEN("trying to get non-existing groups") {
      THEN("get_group must throw an exception") {
        REQUIRE_THROWS_AS(f.root().get_group("/run_003"), std::runtime_error);
        REQUIRE_THROWS_AS(f.root().get_group("run_003"), std::runtime_error);
      }
    }
    THEN("we can access direct child groups") {
      REQUIRE(node::get_group(f.root(), "/run_001").link().path().name() ==
              "run_001");
      REQUIRE(node::get_group(f.root(), "run_002").link().path().name() ==
              "run_002");
    }
    THEN("we can access we can access indirect children ") {
      REQUIRE(node::get_group(f.root(), "run_001/instrument").link().path() ==
              "/run_001/instrument");
      REQUIRE(node::get_group(f.root(), "/run_001/instrument").link().path() ==
              "/run_001/instrument");
    }
    AND_GIVEN("datasets below run_001") {
      node::Dataset(f.root(), "/run_001/data_001", datatype::create<float>());
      THEN("we can access this dataset with") {
        REQUIRE(node::get_dataset(f.root(),"/run_001/data_001").link().path() == "/run_001/data_001");
      }
    }
  }
}
