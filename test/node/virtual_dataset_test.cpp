//
// (c) Copyright 2017 DESY,ESS
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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Nov 10, 2017
//

#include <gtest/gtest.h>

#include <h5cpp/hdf5.hpp>
#include <algorithm>
#include <vector>

using namespace hdf5;

using PathVector = std::vector<boost::filesystem::path>;
using DataVector = std::vector<int>;

static const size_t kModuleSize = 30;

class VirtualDatasetTest : public testing::Test
{
  protected:
    property::FileCreationList gfcpl;
    property::FileAccessList gfapl;
    DataVector data_module_1;
    DataVector data_module_2;
    DataVector data_module_3;
    dataspace::Simple module_space;
    datatype::Integer module_type;
    VirtualDatasetTest();

    virtual void SetUp();
    virtual void TearDown();
    virtual ~VirtualDatasetTest() {}

  private:

    void create_source(const boost::filesystem::path &filename,
                       const DataVector &data);

    static const PathVector files_to_delete;
};

const PathVector VirtualDatasetTest::files_to_delete = {
    "vds_source_1.h5","vds_source_2.h5","vds_source_3.h5"
};

void VirtualDatasetTest::create_source(const boost::filesystem::path &filename,
                                       const DataVector &data)
{
  file::File f = file::create(filename,file::AccessFlags::TRUNCATE,gfcpl,gfapl);
  node::Group root_group = f.root();
  node::Dataset dataset = root_group.create_dataset("module_data",
                                                    module_type,
                                                    module_space);
  dataset.write(data);
}

VirtualDatasetTest::VirtualDatasetTest():
    gfcpl(),
    gfapl(),
    data_module_1(kModuleSize),
    data_module_2(kModuleSize),
    data_module_3(kModuleSize),
    module_space(dataspace::Simple{{kModuleSize}}),
    module_type(datatype::create<int>())
{
  gfapl.library_version_bounds(property::LibVersion::LATEST,
                               property::LibVersion::LATEST);
  std::fill(data_module_1.begin(),data_module_1.end(),1);
  std::fill(data_module_2.begin(),data_module_2.end(),2);
  std::fill(data_module_3.begin(),data_module_3.end(),3);

}

void VirtualDatasetTest::SetUp()
{
  create_source("vds_source_1.h5",data_module_1);
  create_source("vds_source_2.h5",data_module_2);
  create_source("vds_source_3.h5",data_module_3);
}

void VirtualDatasetTest::TearDown()
{
//  for(auto filename: files_to_delete)
//    boost::filesystem::remove(filename);
}

using Mappings = std::vector<property::VirtualDataMap>;

TEST_F(VirtualDatasetTest,test_concatenation)
{
  using dataspace::Hyperslab;
  using hdf5::Path;
  using dataspace::View;

  file::File f = file::create("VirtualDatasetTest.h5",file::AccessFlags::TRUNCATE,gfcpl,gfapl);
  node::Group root = f.root();

  dataspace::Simple file_space{{3,kModuleSize}};
  property::DatasetCreationList dcpl;

  // Create the virtual data maps
  Mappings vds_map = {
      {View{file_space,Hyperslab{{0,0},{1,30}}},"vds_source_1.h5",Path("/module_data"),View{module_space}},
      {View{file_space,Hyperslab{{1,0},{1,30}}},"vds_source_2.h5",Path("/module_data"),View{module_space}},
      {View{file_space,Hyperslab{{2,0},{1,30}}},"vds_source_3.h5",Path("/module_data"),View{module_space}}
  };

  // apply the maps to the datset creation list
  std::for_each(vds_map.begin(),vds_map.end(),
                [&dcpl](const property::VirtualDataMap &map) {map(dcpl);});


  node::Dataset dataset;
  EXPECT_NO_THROW((dataset = root.create_dataset("all",module_type,file_space,
                                              property::LinkCreationList(),
                                              dcpl)));
  EXPECT_EQ(dataset.dataspace().size(),90);

  DataVector read(kModuleSize);
  Hyperslab slab{{0,0},{1,kModuleSize}};
  EXPECT_NO_THROW(dataset.read(read,slab));
  EXPECT_EQ(read,data_module_1);

  slab.offset({1,0});
  EXPECT_NO_THROW(dataset.read(read,slab));
  EXPECT_EQ(read,data_module_2);

  slab.offset({2,0});
  EXPECT_NO_THROW(dataset.read(read,slab));
  EXPECT_EQ(read,data_module_3);

}

TEST_F(VirtualDatasetTest,test_interleaving)
{
  using dataspace::Hyperslab;
  using hdf5::Path;
  using dataspace::View;
  using hdf5::Dimensions;

  file::File f = file::create("VirtualDatasetTest_Interleaving.h5",file::AccessFlags::TRUNCATE,gfcpl,gfapl);
  node::Group root = f.root();

  dataspace::Simple file_space{{3*kModuleSize}};
  property::DatasetCreationList dcpl;

  // Create the virtual data maps

  Dimensions count{kModuleSize};
  Dimensions stride{3};
  Dimensions block{1};
  Mappings vds_map = {
      {View{file_space,Hyperslab{{0},block,count,stride}},"vds_source_1.h5",Path("/module_data"),View{module_space}},
      {View{file_space,Hyperslab{{1},block,count,stride}},"vds_source_2.h5",Path("/module_data"),View{module_space}},
      {View{file_space,Hyperslab{{2},block,count,stride}},"vds_source_3.h5",Path("/module_data"),View{module_space}}
  };

  // apply the maps to the datset creation list
  std::for_each(vds_map.begin(),vds_map.end(),
                [&dcpl](const property::VirtualDataMap &map) {map(dcpl);});


  node::Dataset dataset;
  EXPECT_NO_THROW((dataset = root.create_dataset("all",module_type,file_space,
                                                 property::LinkCreationList(),
                                                 dcpl)));
  EXPECT_EQ(dataset.dataspace().size(),90);
  //readback data
  DataVector data(3);
  DataVector ref_data{1,2,3};
  for(size_t offset=0;offset<kModuleSize*3;offset+=3)
  {
    EXPECT_NO_THROW(dataset.read(data,Hyperslab{{offset},{3}}));
    EXPECT_EQ(data,ref_data);
  }
}


