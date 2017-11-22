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
// Created on: Sep 13, 2017
//
#include "group_test_fixtures.hpp"
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

class LinkIteration : public NodeIterationFixture
{
};


TEST_F(LinkIteration, group_index_name_order_access)
{
  EXPECT_EQ(root_.links.size(),10ul);
  //setup creation order
  root_.iterator_config().index(hdf5::IterationIndex::NAME);
  root_.iterator_config().order(hdf5::IterationOrder::DECREASING);

  EXPECT_EQ(root_.links[0].type(),node::LinkType::SOFT);
  EXPECT_EQ(static_cast<std::string>(root_.links[0].path()),"/g3_soft_link");
  EXPECT_EQ(root_.links[1].type(),node::LinkType::HARD);
  EXPECT_EQ(static_cast<std::string>(root_.links[1].path()),"/g3");

  EXPECT_EQ(root_.links[2].type(),node::LinkType::SOFT);
  EXPECT_EQ(static_cast<std::string>(root_.links[2].path()),"/g2_soft_link");
  EXPECT_EQ(root_.links[3].type(),node::LinkType::HARD);
  EXPECT_EQ(static_cast<std::string>(root_.links[3].path()),"/g2");

  EXPECT_EQ(root_.links[4].type(),node::LinkType::SOFT);
  EXPECT_EQ(static_cast<std::string>(root_.links[4].path()),"/g1_soft_link");
  EXPECT_EQ(root_.links[5].type(),node::LinkType::HARD);
  EXPECT_EQ(static_cast<std::string>(root_.links[5].path()),"/g1");


  EXPECT_EQ(root_.links[6].type(),node::LinkType::SOFT);
  EXPECT_EQ(static_cast<std::string>(root_.links[6].path()),"/d2_soft_link");
  EXPECT_EQ(root_.links[7].type(),node::LinkType::HARD);
  EXPECT_EQ(static_cast<std::string>(root_.links[7].path()),"/d2");

  EXPECT_EQ(root_.links[8].type(),node::LinkType::SOFT);
  EXPECT_EQ(static_cast<std::string>(root_.links[8].path()),"/d1_soft_link");
  EXPECT_EQ(root_.links[9].type(),node::LinkType::HARD);
  EXPECT_EQ(static_cast<std::string>(root_.links[9].path()),"/d1");
}

TEST_F(LinkIteration, group_index_creation_order_access)
{
  EXPECT_EQ(root_.links.size(),10ul);
  //setup creation order
  root_.iterator_config().index(hdf5::IterationIndex::CREATION_ORDER);
  root_.iterator_config().order(hdf5::IterationOrder::INCREASING);

  EXPECT_EQ(root_.links[0].type(),node::LinkType::HARD);
  EXPECT_EQ(static_cast<std::string>(root_.links[0].path()),"/g1");
  EXPECT_EQ(root_.links[1].type(),node::LinkType::HARD);
  EXPECT_EQ(static_cast<std::string>(root_.links[1].path()),"/g2");
  EXPECT_EQ(root_.links[2].type(),node::LinkType::HARD);
  EXPECT_EQ(static_cast<std::string>(root_.links[2].path()),"/g3");
  EXPECT_EQ(root_.links[3].type(),node::LinkType::HARD);
  EXPECT_EQ(static_cast<std::string>(root_.links[3].path()),"/d1");
  EXPECT_EQ(root_.links[4].type(),node::LinkType::HARD);
  EXPECT_EQ(static_cast<std::string>(root_.links[4].path()),"/d2");
}

TEST_F(LinkIteration, group_name_access)
{
  node::Link l;
  EXPECT_NO_THROW(l=root_.links["g1"]);
  EXPECT_EQ(l.type(),node::LinkType::HARD);
  EXPECT_EQ(static_cast<std::string>(l.path()),"/g1");
  EXPECT_NO_THROW(l=root_.links["d1"]);
  EXPECT_EQ(l.type(),node::LinkType::HARD);
  EXPECT_EQ(static_cast<std::string>(l.path()),"/d1");

}

TEST_F(LinkIteration, group_node_iteration)
{
  EXPECT_EQ(root_.links.size(),10ul);
  //setup creation order
  root_.iterator_config().index(hdf5::IterationIndex::NAME);
  root_.iterator_config().order(hdf5::IterationOrder::DECREASING);

  std::vector<std::string> names{"/g3_soft_link","/g3",
    "/g2_soft_link","/g2","/g1_soft_link","/g1","/d2_soft_link","/d2",
    "/d1_soft_link","/d1"};
  std::vector<node::LinkType> types {
    node::LinkType::SOFT,node::LinkType::HARD,
    node::LinkType::SOFT,node::LinkType::HARD,
    node::LinkType::SOFT,node::LinkType::HARD,
    node::LinkType::SOFT,node::LinkType::HARD,
    node::LinkType::SOFT,node::LinkType::HARD
  };

  auto name_iter = names.begin();
  auto type_iter = types.begin();

  for(auto iter = root_.links.begin();iter!=root_.links.end();++iter)
  {
    EXPECT_EQ(static_cast<std::string>(iter->path()),*name_iter++);
    EXPECT_EQ((*iter).type(),*type_iter++);
  }
}

TEST_F(LinkIteration, group_node_foreach)
{
  EXPECT_EQ(root_.links.size(),10ul);
  //setup creation order
  root_.iterator_config().index(hdf5::IterationIndex::NAME);
  root_.iterator_config().order(hdf5::IterationOrder::DECREASING);

  std::vector<std::string> names{"/g3_soft_link","/g3",
    "/g2_soft_link","/g2","/g1_soft_link","/g1","/d2_soft_link","/d2",
    "/d1_soft_link","/d1"};
  std::vector<node::LinkType> types {
    node::LinkType::SOFT,node::LinkType::HARD,
    node::LinkType::SOFT,node::LinkType::HARD,
    node::LinkType::SOFT,node::LinkType::HARD,
    node::LinkType::SOFT,node::LinkType::HARD,
    node::LinkType::SOFT,node::LinkType::HARD
  };

  auto name_iter = names.begin();
  auto type_iter = types.begin();

  for(auto link: root_.links)
  {
    EXPECT_EQ(static_cast<std::string>(link.path()),*name_iter++);
    EXPECT_EQ(link.type(),*type_iter++);
  }

}



