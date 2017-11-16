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
// Authors:
//    Eugen Wintersberger <eugen.wintersberger@desy.de>
//    Martin Shetty <martin.shetty@esss.se>
// Created on: Sep 12, 2017
//

#include <vector>
#include <h5cpp/hdf5.hpp>
#include "group_test_fixtures.hpp"

using namespace hdf5;

class GroupTest : public BasicFixture
{
};

TEST_F(GroupTest, test_root_group)
{
  node::Group root;
  EXPECT_NO_THROW(root = file_.root());
  EXPECT_TRUE(root.is_valid());
  EXPECT_EQ(root.type(),node::Type::GROUP);
  EXPECT_EQ(root.links.size(),0ul);
  EXPECT_EQ(root.nodes.size(),0ul);
  EXPECT_EQ(static_cast<std::string>(root.link().path()),"/");
}

TEST_F(GroupTest, test_default_construction)
{
  node::Group group;
  EXPECT_FALSE(group.is_valid());
}

TEST_F(GroupTest,test_constructor_construction)
{
  node::Group root_group = file_.root();
  node::Group g(root_group,Path("test_group"));
  EXPECT_TRUE(g.is_valid());
  EXPECT_EQ(g.link().path().name(),"test_group");
  EXPECT_EQ(static_cast<std::string>(g.link().path().parent()),"/");
}

TEST_F(GroupTest, test_group_creation)
{
  node::Group g = file_.root();
  EXPECT_EQ(g.nodes.size(),0ul);
  EXPECT_EQ(g.links.size(),0ul);
  EXPECT_NO_THROW(g.create_group("group_1"));
  EXPECT_EQ(g.nodes.size(),1ul);
  EXPECT_EQ(g.links.size(),1ul);
  EXPECT_NO_THROW(g.create_group("group_2"));
  EXPECT_EQ(g.nodes.size(),2ul);
  EXPECT_EQ(g.links.size(),2ul);
}

TEST_F(GroupTest, test_group_linkview)
{
  node::Group g = file_.root();
  EXPECT_FALSE(g.links.exists("group_1"));

  node::Group g1 = g.create_group("group_1");

  EXPECT_TRUE(g.links.exists("group_1"));

  node::Link l;
  EXPECT_NO_THROW(l = g.links["group_1"]);
  EXPECT_EQ(l, g1.link());
}

TEST_F(GroupTest, test_group_nodeview)
{
  node::Group g = file_.root();

  EXPECT_FALSE(g.nodes.exists("group_1"));

  node::Group g1 = g.create_group("group_1");

  EXPECT_TRUE(g.nodes.exists("group_1"));

  node::Group n;
  EXPECT_NO_THROW(n = g.nodes["group_1"]);
  EXPECT_EQ(n.id(), g1.id());
}

TEST_F(GroupTest, test_group_existence)
{
  node::Group g = file_.root();

  EXPECT_FALSE(g.exists("group_1"));

  node::Group g1 = g.create_group("group_1");

  EXPECT_TRUE(g.exists("group_1"));
}

TEST_F(GroupTest, test_group_accessor)
{
  node::Group g = file_.root();
  node::Group g1 = g.create_group("group_1");

  EXPECT_EQ(g1.id(), g["group_1"].id());
}

TEST_F(GroupTest, test_funky_names)
{
  auto f = file::create("funky_names.h5",file::AccessFlags::TRUNCATE);
  node::Group g = f.root();

  EXPECT_NO_THROW(g.create_group("s p a c e y"));
  EXPECT_TRUE(g.exists("s p a c e y"));

  EXPECT_NO_THROW(g.create_group(" sp"));
  EXPECT_TRUE(g.exists(" sp"));

  EXPECT_NO_THROW(g.create_group("sp "));
  EXPECT_TRUE(g.exists("sp "));

  EXPECT_NO_THROW(g.create_group("sp"));
  EXPECT_TRUE(g.exists("sp"));

  EXPECT_NO_THROW(g.create_group(" "));
  EXPECT_TRUE(g.exists(" "));

  EXPECT_NO_THROW(g.create_group("  "));
  EXPECT_TRUE(g.exists("  "));

  EXPECT_NO_THROW(g.create_group("d.o.t.s"));
  EXPECT_TRUE(g.exists("d.o.t.s"));

  EXPECT_NO_THROW(g.create_group(".d.o.t"));
  EXPECT_TRUE(g.exists(".d.o.t"));

  EXPECT_NO_THROW(g.create_group("d..t"));
  EXPECT_TRUE(g.exists("d..t"));

  EXPECT_NO_THROW(g.create_group("..dt"));
  EXPECT_TRUE(g.exists("..dt"));

  EXPECT_NO_THROW(g.create_group(".."));
  EXPECT_TRUE(g.exists(".."));

//  EXPECT_NO_THROW(g.create_group("g/g2"));
//  EXPECT_NO_THROW(g.create_group("./g/g3"));

  EXPECT_THROW(g.create_group("."), std::exception);
}



