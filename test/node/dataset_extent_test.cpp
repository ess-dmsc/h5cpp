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
// Created on: Sep 12, 2017
//

#include <catch2/catch.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

namespace { 

auto int_dtype = []() { return datatype::create<int>(); };
auto link_creation_list = []() { return property::LinkCreationList{}; };
auto dataset_creation_list = []() { return property::DatasetCreationList{}; };
auto dataset_access_list = []() { return property::DatasetAccessList{}; };

auto current_dimension = [](const node::Dataset& dataset, size_t index = 0) {
  return dataspace::Simple{dataset.dataspace()}.current_dimensions()[index];
};
}

SCENARIO("testing the extent of a dataset") {
  using node::resize_by;
  auto f = file::create("dataset_extent_test.h5", file::AccessFlags::Truncate);
  auto r = f.root();
  dataspace::Simple inf_dataspace({0}, {dataspace::Simple::unlimited});
  dataspace::Simple fin_dataspace({0}, {4096});

  auto create_dataset = [&r](const hdf5::Path& p,
                             const dataspace::Dataspace& ds) {
    auto dcpl = dataset_creation_list();
    dcpl.layout(property::DatasetLayout::Chunked);
    dcpl.chunk({1024});
    return node::Dataset(r, p, int_dtype(), ds, link_creation_list(), dcpl,
                         dataset_access_list());
  };

  GIVEN("datasets with inifinte and finite dataspaces") {
    std::vector<node::Dataset> datasets{
        create_dataset("inf_data", inf_dataspace),
        create_dataset("fin_data", fin_dataspace)};
    for (auto dataset : datasets) {
      THEN("then first dimension has actually no elements") {
        REQUIRE(current_dimension(dataset) == 0ul);
      }

      WHEN("setting all dimensions at once using extent()") {
        dataset.extent({1000});
        THEN("the actual dimension becomes 1000") {
          REQUIRE(current_dimension(dataset) == 1000ul);
        }
      }

      WHEN("setting the elements for a single dimension using extent()") {
        REQUIRE_NOTHROW(dataset.extent(0, 123));
        THEN("the actual dimensions reads 123") {
          REQUIRE(current_dimension(dataset) == 123ul);
          AND_WHEN("shrinking the elements for a single dimension using extent()") {
            REQUIRE_NOTHROW(dataset.extent(0, -3));
            THEN("the actual dimensions reads 120") {
              REQUIRE(current_dimension(dataset) == 120ul);
            }
          }
        }
      }

      WHEN("setting all dimensions at once using resize()") {
        REQUIRE_NOTHROW(dataset.resize({100}));
        THEN("the actual dimensions become 100") {
          REQUIRE(current_dimension(dataset) == 100ul);
          AND_WHEN(
              "setting changing the number of elements by a relative value") {
            resize_by(dataset, 0, 12);
            THEN("the new number of dimensions must be 112") {
              REQUIRE(current_dimension(dataset) == 112ul);
            }
          }
        }
      }

      // ======================================================================
      // testing some common error conditions
      // ======================================================================
      WHEN("setting the extent to a negative value (extent)") {
        THEN("the operation must fail") {
          REQUIRE_THROWS_AS(dataset.extent(0, -1000), std::runtime_error);
        }
      }
      WHEN("setting the extent to a negative value (resize_by)") {
        THEN("the operation fails also with resize_by") {
          REQUIRE_THROWS_AS(resize_by(dataset, 0, -100), std::runtime_error);
        }
      }

      WHEN("setting the extent for a non-existing dimension (extent)") {
        THEN("the operation must fail") {
          REQUIRE_THROWS_AS(dataset.extent(1, 100), std::runtime_error);
        }
      }
      WHEN("setting the extent for a non-existing dimension (resize_by)") {
        THEN("operation also fails with resize_by") {
          REQUIRE_THROWS_AS(resize_by(dataset, 1, 100), std::runtime_error);
        }
      }
    }
  }

  GIVEN("a dataset with a finite extent") {
    auto dataset = create_dataset("fin_data", fin_dataspace);
    WHEN("trying to set the absolute extent larger than maximum") {
      THEN("the oepration must fail") {
        REQUIRE_THROWS_AS(dataset.extent({100000}), std::runtime_error);
      }
      THEN("the operation must fail") {
        REQUIRE_THROWS_AS(dataset.resize({100000}), std::runtime_error);
      }
      THEN("the operation must fail by a relative value") { 
        REQUIRE_THROWS_AS(resize_by(dataset,0,1000000), std::runtime_error);
      }
    }
  }
}

/*

TEST_F(Extent, test_infinite_resize_by) {
  sspace = inf_data.dataspace();
  EXPECT_EQ(sspace.current_dimensions()[0], 0ul);
  EXPECT_NO_THROW(resize_by(inf_data, 0, 123));
  sspace = inf_data.dataspace();
  EXPECT_EQ(sspace.current_dimensions()[0], 123ul);

  EXPECT_THROW(resize_by(inf_data, 0, -1000), std::runtime_error);
  EXPECT_THROW(resize_by(inf_data, 1, 100), std::runtime_error);
}
*/
