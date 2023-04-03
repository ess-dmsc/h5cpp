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
// Created on: Sep 12, 2017
//

#include <catch2/catch_all.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

SCENARIO("dataset construction") {
  auto f = file::create("dataset_test.h5", file::AccessFlags::Truncate);
  auto r = f.root();

  GIVEN("a default constructed dataset") {
    node::Dataset dset;
    THEN("method access throws exceptions") {
      REQUIRE_THROWS_AS(dset.dataspace(), std::runtime_error);
      REQUIRE_THROWS_AS(dset.datatype(), std::runtime_error);
      REQUIRE_THROWS_AS(dset.extent({10, 100}), std::runtime_error);
    }
  }

  GIVEN("a node reference to the root group") {
    const node::Node& root_node = r;
    THEN("attempting to construct a dataset from this reference will fail") {
      REQUIRE_THROWS_AS(node::Dataset(root_node), std::runtime_error);
    }
  }

  GIVEN("an integer datatype") {
    auto dt = datatype::create<int>();
    AND_GIVEN("a scalar datatspace") {
      auto ds = dataspace::Scalar{};
      THEN("we can construct a dataset from this below the root group") {
        node::Dataset dset(r, "data", dt, ds);
        WHEN("checking the dataset properties") {
          REQUIRE(dset.dataspace().type() == dataspace::Type::Scalar);
          REQUIRE(dset.datatype().get_class() == datatype::Class::Integer);
        }
        WHEN("trying to set the extend") {
          THEN("the operation must fail") {
            REQUIRE_THROWS_AS(dset.extent({10}), std::runtime_error);
          }
        }
        GIVEN("a node reference to the dataset") {
          const node::Node& dset_ref = dset;
          THEN("a copy of the dataset can be constructed") {
            node::Dataset dset_copy(dset_ref);
            AND_THEN("the path must be the same as to the original") { 
              REQUIRE(dset_copy.link().path().name() == "data");
            }
          }
        }
      }
    }
  }
}
