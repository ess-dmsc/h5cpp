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
// Created on: Sep 12, 2017
//

#include <vector>
#include "group_test_fixtures.hpp"

using namespace hdf5;

class Group : public BasicFixture
{
};

TEST_F(Group, test_root_group)
{
  node::Group root;
  EXPECT_NO_THROW(root = file_.root());
  EXPECT_TRUE(root.is_valid());
  EXPECT_EQ(root.type(),node::Type::GROUP);
  EXPECT_EQ(root.links.size(),0);
  EXPECT_EQ(root.nodes.size(),0);
  EXPECT_EQ(static_cast<std::string>(root.link().path()),"/");
}

TEST_F(Group, test_default_construction)
{
  node::Group group;
  EXPECT_FALSE(group.is_valid());
}

TEST_F(Group, test_group_creation)
{
  node::Group g = file_.root();
  EXPECT_EQ(g.nodes.size(),0);
  EXPECT_EQ(g.links.size(),0);
  EXPECT_NO_THROW(g.create_group("group_1"));
  EXPECT_EQ(g.nodes.size(),1);
  EXPECT_EQ(g.links.size(),1);
  EXPECT_NO_THROW(g.create_group("group_2"));
  EXPECT_EQ(g.nodes.size(),2);
  EXPECT_EQ(g.links.size(),2);
}

TEST_F(Group, test_group_linkview)
{
  node::Group g = file_.root();
  EXPECT_FALSE(g.links.exists("group_1"));

  node::Group g1 = g.create_group("group_1");

  EXPECT_TRUE(g.links.exists("group_1"));

  node::Link l;
  EXPECT_NO_THROW(l = g.links["group_1"]);
  EXPECT_EQ(l, g1.link());
}

TEST_F(Group, test_group_nodeview)
{
  node::Group g = file_.root();

  EXPECT_THROW(g.nodes.exists("group_1"), std::runtime_error);

  node::Group g1 = g.create_group("group_1");

  EXPECT_TRUE(g.nodes.exists("group_1"));

  node::Group n;
  EXPECT_NO_THROW(n = g.nodes["group_1"]);
  EXPECT_EQ(n.id(), g1.id());
}

TEST_F(Group, test_group_existence)
{
  node::Group g = file_.root();

  EXPECT_FALSE(g.exists("group_1"));

  node::Group g1 = g.create_group("group_1");

  EXPECT_TRUE(g.exists("group_1"));
}

TEST_F(Group, test_group_accessor)
{
  node::Group g = file_.root();
  node::Group g1 = g.create_group("group_1");

  EXPECT_EQ(g1.id(), g["group_1"].id());
}





