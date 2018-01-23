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
// Created on: Nov 16, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

class GetNodeFunctionTest : public ::testing::Test
{
  public:
    file::File file;
    node::Group root_group;

    GetNodeFunctionTest();

    virtual void SetUp();
};

GetNodeFunctionTest::GetNodeFunctionTest()
{
  file = file::create("GetNodeFunctionTest.h5",file::AccessFlags::TRUNCATE);
  root_group = file.root();
}

void GetNodeFunctionTest::SetUp()
{
  node::Group sensors = root_group.create_group("run_1")
                                  .create_group("sensors");
  sensors.create_group("temperature");
  sensors.create_group("pressure");
  sensors = root_group.create_group("run_2")
                      .create_group("sensors");
  sensors.create_group("humidity");
  sensors.create_group("voltage");
}

TEST_F(GetNodeFunctionTest, views_test)
{
  EXPECT_THROW(root_group.links["/invalid/node"], std::runtime_error);
  EXPECT_THROW(root_group.nodes["/invalid/node"], std::runtime_error);

  EXPECT_TRUE(root_group.nodes.exists("run_1"));
  root_group.create_link("invalid", root_group.nodes["run_1"]);
  root_group.remove("run_1");

  EXPECT_FALSE(root_group.nodes.exists("invalid"));
}

TEST_F(GetNodeFunctionTest,test_empty_search_path)
{
  node::Group base = root_group.nodes["run_1"];
  node::Group run_1 = node::get_node(base,Path());

  //we expect here to get the same object back
  EXPECT_EQ(run_1,base);
  EXPECT_EQ(run_1.link().path().name(),"run_1");
  EXPECT_EQ(static_cast<std::string>(run_1.link().path().parent()),"/");
}

TEST_F(GetNodeFunctionTest,test_search_root)
{
  node::Group base = root_group.nodes["run_1"];
  node::Group root = node::get_node(base,Path("/"));
  //we expect here to get the root group
  EXPECT_EQ(root,root_group);
}

TEST_F(GetNodeFunctionTest,test_pressure_relative)
{
  node::Group base = root_group.nodes["run_1"];
  node::Group pressure = node::get_node(base,Path("sensors/pressure"));

  EXPECT_EQ(pressure.link().path().name(),"pressure");
  EXPECT_EQ(static_cast<std::string>(pressure.link().path().parent()),"/run_1/sensors");
}

TEST_F(GetNodeFunctionTest,test_humidity_absolute)
{
  node::Group base = root_group.nodes["run_1"];
  node::Group humidity = node::get_node(base,Path("/run_2/sensors/humidity"));

  EXPECT_EQ(humidity.link().path().name(),"humidity");
  EXPECT_EQ(static_cast<std::string>(humidity.link().path().parent()),"/run_2/sensors");
}
