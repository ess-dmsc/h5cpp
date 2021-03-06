//
// (c) Copyright 2018 DESY,ESS
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
// Created on: Mar 9, 2018
//
#include "group_test_fixtures.hpp"

class NodeExistsTest : public BasicFixture
{

};


TEST_F(NodeExistsTest,only_link_exists)
{
  hdf5::node::link("sensors",file_.root(),"sensors_link");

  EXPECT_TRUE(file_.root().links.exists("sensors_link"));
  EXPECT_FALSE(file_.root().nodes.exists("sensors_link"));
  EXPECT_FALSE(file_.root().links.exists("sensors"));
  EXPECT_FALSE(file_.root().nodes.exists("sensors"));
}

TEST_F(NodeExistsTest,node_exists)
{
  hdf5::node::Group(file_.root(),"sensors");
  hdf5::node::link("sensors",file_.root(),"sensors_link");
  EXPECT_TRUE(file_.root().links.exists("sensors_link"));
  EXPECT_TRUE(file_.root().nodes.exists("sensors_link"));
  EXPECT_TRUE(file_.root().nodes.exists("sensors"));

}

