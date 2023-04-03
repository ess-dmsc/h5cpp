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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Nov 10, 2017
//
#include <algorithm>
#include <catch2/catch_all.hpp>
#include <h5cpp/hdf5.hpp>
#include <vector>

using namespace hdf5;

using PathVector = std::vector<fs::path>;
using DataVector = std::vector<int>;
using dataspace::Hyperslab;
using dataspace::View;
using hdf5::Path;


#if H5_VERSION_GE(1, 10, 0)

namespace { 

  static const size_t kModuleSize = 30;
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#pragma clang diagnostic ignored "-Wexit-time-destructors"
#endif
  const static PathVector vds_files = {"vds_source_1.h5", "vds_source_2.h5",
                                     "vds_source_3.h5"};

  const static dataspace::Simple module_space{{kModuleSize}};
  const static auto module_type = datatype::create<int>();
#ifdef __clang__
#pragma clang diagnostic pop
#endif

  static void create_module_file(const fs::path& filename, const DataVector& data) {
    const property::FileCreationList gfcpl;
    const property::FileAccessList gfapl;
    file::File f =
        file::create(filename, file::AccessFlags::Truncate, gfcpl, gfapl);
    node::Dataset dataset(f.root(), Path("module_data"), module_type,
                          module_space);
    dataset.write(data);
  }

  static DataVector create_data(size_t size, int initial_value) {
    DataVector data(size);
    std::fill(std::begin(data), std::end(data), initial_value);
    return data;
  }
}




SCENARIO("testing virtual datasets") {
  const property::FileCreationList gfcpl;
  const property::FileAccessList gfapl;
  auto data_module_1 = create_data(kModuleSize, 1);
  auto data_module_2 = create_data(kModuleSize, 2);
  auto data_module_3 = create_data(kModuleSize, 3);
  create_module_file("vds_source_1.h5", data_module_1);
  create_module_file("vds_source_2.h5", data_module_2);
  create_module_file("vds_source_3.h5", data_module_3);
  auto f = file::create("VirtualDatasetTest.h5", file::AccessFlags::Truncate,
                        gfcpl, gfapl);

  GIVEN("a virtual data map connecting the individual modules") {
    dataspace::Simple file_space{{3, kModuleSize}};
    property::VirtualDataMaps vds_map = {
        {View{file_space, Hyperslab{{0, 0}, {1, 30}}}, "vds_source_1.h5",
         Path("/module_data"), View{module_space}},
        {View{file_space, Hyperslab{{1, 0}, {1, 30}}}, "vds_source_2.h5",
         Path("/module_data"), View{module_space}},
        {View{file_space, Hyperslab{{2, 0}, {1, 30}}}, "vds_source_3.h5",
         Path("/module_data"), View{module_space}}};
    THEN("we can create a new virtual dataset") {
      node::VirtualDataset vds(f.root(), Path("all"), module_type, file_space,
                               vds_map);
      AND_THEN("the size of the total dataspace should be 90") {
        REQUIRE(vds.dataspace().size() == 90);
      }
      AND_THEN("we can read the data of the individual modules back") {
        DataVector read(kModuleSize);
        Hyperslab slab{{0, 0}, {1, kModuleSize}};
        REQUIRE_NOTHROW(vds.read(read, slab));
        REQUIRE_THAT(read, Catch::Matchers::Equals(data_module_1));
        slab.offset({1, 0});
        REQUIRE_NOTHROW(vds.read(read, slab));
        REQUIRE_THAT(read, Catch::Matchers::Equals(data_module_2));

        slab.offset({2, 0});
        REQUIRE_NOTHROW(vds.read(read, slab));
        REQUIRE_THAT(read, Catch::Matchers::Equals(data_module_3));
      }
    }
  }
  // Create the virtual data maps
  GIVEN("a virtual data map for interleaving data") {
    dataspace::Simple file_space{{3* kModuleSize}};
    Dimensions count{kModuleSize};
    Dimensions stride{3};
    Dimensions block{1};
    property::VirtualDataMaps vds_map = {
        {View{file_space, Hyperslab{{0}, block, count, stride}},
         "vds_source_1.h5", Path("/module_data"), View{module_space}},
        {View{file_space, Hyperslab{{1}, block, count, stride}},
         "vds_source_2.h5", Path("/module_data"), View{module_space}},
        {View{file_space, Hyperslab{{2}, block, count, stride}},
         "vds_source_3.h5", Path("/module_data"), View{module_space}}};
    THEN("we can create a virtual dataset") {
      node::VirtualDataset vds(f.root(), Path("interleave"), module_type, file_space,
                               vds_map);
      AND_THEN("the size of the virtual dataset must be the total size") {
        REQUIRE(vds.dataspace().size() == 90);
      }
      AND_THEN("we can read the interleaved data back") {
        DataVector data(3);
        for (size_t offset = 0; offset < kModuleSize * 3; offset += 3) {
          REQUIRE_NOTHROW(vds.read(data, Hyperslab{{offset}, {3}}));
          REQUIRE_THAT(data, Catch::Matchers::Equals(DataVector{1,2,3}));
        }
      }
    }
  }
}


#endif
