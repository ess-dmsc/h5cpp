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

using namespace hdf5;

using PathVector = std::vector<boost::filesystem::path>;
using DataVector = std::vector<int>;

class VirtualDatasetTest : public testing::Test
{
  protected:
    property::FileCreationList gfcpl;
    property::FileAccessList gfapl;
    VirtualDatasetTest();

    virtual void SetUp();
    virtual void TearDown();
    virtual ~VirtualDatasetTest() {}

  private:

    void create_source(const boost::filesystem::path &filename,int value);

    static const PathVector files_to_delete;
};

const PathVector VirtualDatasetTest::files_to_delete = {
    "vds_source_1.h5","vds_source_2.h5","vds_source_3.h5"
};

void VirtualDatasetTest::create_source(const boost::filesystem::path &filename,int value)
{
  file::File f = file::create(filename,file::AccessFlags::TRUNCATE,gfcpl,gfapl);
  node::Group root_group = f.root();

  auto file_type = datatype::create<int>();
  dataspace::Simple file_space{{30}};
  DataVector data(file_space.size());
  std::fill(data.begin(),data.end(),value);

  node::Dataset dataset = root_group.create_dataset("module_data",
                                                    file_type,
                                                    file_space);
  dataset.write(data);
}

VirtualDatasetTest::VirtualDatasetTest():
    gfcpl(),
    gfapl()
{
  gfapl.library_version_bounds(property::LibVersion::LATEST,
                               property::LibVersion::LATEST);
}

void VirtualDatasetTest::SetUp()
{
  create_source("vds_source_1.h5",1);
  create_source("vds_source_2.h5",2);
  create_source("vds_source_3.h5",3);
}

void VirtualDatasetTest::TearDown()
{
//  for(auto filename: files_to_delete)
//    boost::filesystem::remove(filename);
}


TEST_F(VirtualDatasetTest,test_concatenation)
{
  using property::VirtualDataMap;
  using dataspace::Hyperslab;
  using dataspace::SelectionOperation;
  using hdf5::Path;
  file::File f = file::create("VirtualDatasetTest.h5",file::AccessFlags::TRUNCATE,gfcpl,gfapl);
  node::Group root = f.root();

  auto file_type = datatype::create<int>();
  dataspace::Simple file_space{{3,30}};
  dataspace::Simple module_space{{30}};
  property::DatasetCreationList dcpl;

  dataspace::Simple m1_space(file_space);
  m1_space.selection(SelectionOperation::SET,Hyperslab{{0,0},{1,30}});
  VirtualDataMap module_1(m1_space,"vds_source_1.h5",Path("/module_data"),module_space);

  dataspace::Simple m2_space(file_space);
  m2_space.selection(SelectionOperation::SET,Hyperslab{{1,0},{1,30}});
  VirtualDataMap module_2(m2_space,"vds_source_2.h5",Path("/module_data"),module_space);

  dataspace::Simple m3_space(file_space);
  m3_space.selection(SelectionOperation::SET,Hyperslab{{2,0},{1,30}});
  VirtualDataMap module_3(m3_space,"vds_source_3.h5",Path("/module_data"),module_space);

  EXPECT_NO_THROW(module_1(dcpl));
  EXPECT_NO_THROW(module_2(dcpl));
  EXPECT_NO_THROW(module_3(dcpl));

  node::Dataset dataset;
  EXPECT_NO_THROW((dataset = root.create_dataset("all",file_type,file_space,
                                              property::LinkCreationList(),
                                              dcpl)));
  EXPECT_EQ(dataset.dataspace().size(),90);

  DataVector m1_data(30),m2_data(30),m3_data(30);
  std::fill(m1_data.begin(),m1_data.end(),1);
  std::fill(m2_data.begin(),m2_data.end(),2);
  std::fill(m3_data.begin(),m3_data.end(),3);
  f.flush(file::Scope::GLOBAL);

  DataVector read(30);
  Hyperslab slab{{0,0},{1,30}};
  dataset.read(read,slab);
  EXPECT_EQ(read,m1_data);

}
