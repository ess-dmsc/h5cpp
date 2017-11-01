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
#include <h5cpp/node/node_iterator.hpp>

using namespace hdf5;

class NodeIteration : public NodeIterationFixture
{
};

TEST_F(NodeIteration, group_index_name_order_access)
{
  EXPECT_EQ(root_.nodes.size(),5ul);
  //setup creation order
  root_.iterator_config().index(hdf5::IterationIndex::NAME);
  root_.iterator_config().order(hdf5::IterationOrder::DECREASING);

  EXPECT_EQ(root_.nodes[0].type(),node::Type::GROUP);
  EXPECT_EQ(static_cast<std::string>(root_.nodes[0].link().path()),"/g3");
  EXPECT_EQ(root_.nodes[1].type(),node::Type::GROUP);
  EXPECT_EQ(static_cast<std::string>(root_.nodes[1].link().path()),"/g2");
  EXPECT_EQ(root_.nodes[2].type(),node::Type::GROUP);
  EXPECT_EQ(static_cast<std::string>(root_.nodes[2].link().path()),"/g1");
  EXPECT_EQ(root_.nodes[3].type(),node::Type::DATASET);
  EXPECT_EQ(static_cast<std::string>(root_.nodes[3].link().path()),"/d2");
  EXPECT_EQ(root_.nodes[4].type(),node::Type::DATASET);
  EXPECT_EQ(static_cast<std::string>(root_.nodes[4].link().path()),"/d1");
}

TEST_F(NodeIteration, group_index_creation_order_access)
{
  EXPECT_EQ(root_.nodes.size(),5ul);
  //setup creation order
  root_.iterator_config().index(hdf5::IterationIndex::CREATION_ORDER);
  root_.iterator_config().order(hdf5::IterationOrder::INCREASING);

  EXPECT_EQ(root_.nodes[0].type(),node::Type::GROUP);
  EXPECT_EQ(static_cast<std::string>(root_.nodes[0].link().path()),"/g1");
  EXPECT_EQ(root_.nodes[1].type(),node::Type::GROUP);
  EXPECT_EQ(static_cast<std::string>(root_.nodes[1].link().path()),"/g2");
  EXPECT_EQ(root_.nodes[2].type(),node::Type::GROUP);
  EXPECT_EQ(static_cast<std::string>(root_.nodes[2].link().path()),"/g3");
  EXPECT_EQ(root_.nodes[3].type(),node::Type::DATASET);
  EXPECT_EQ(static_cast<std::string>(root_.nodes[3].link().path()),"/d1");
  EXPECT_EQ(root_.nodes[4].type(),node::Type::DATASET);
  EXPECT_EQ(static_cast<std::string>(root_.nodes[4].link().path()),"/d2");
}

TEST_F(NodeIteration, group_name_access)
{
  node::Node n;
  EXPECT_NO_THROW(n=root_.nodes["g1"]);
  EXPECT_EQ(n.type(),node::Type::GROUP);
  EXPECT_EQ(static_cast<std::string>(n.link().path()),"/g1");
  EXPECT_NO_THROW(n=root_.nodes["d1"]);
  EXPECT_EQ(n.type(),node::Type::DATASET);
  EXPECT_EQ(static_cast<std::string>(n.link().path()),"/d1");

}

TEST_F(NodeIteration, group_node_iteration)
{
  EXPECT_EQ(root_.nodes.size(),5ul);
  //setup creation order
  root_.iterator_config().index(hdf5::IterationIndex::NAME);
  root_.iterator_config().order(hdf5::IterationOrder::DECREASING);

  std::vector<std::string> names{"/g3","/g2","/g1","/d2","/d1"};
  std::vector<node::Type> types{node::Type::GROUP,
                                node::Type::GROUP,
                                node::Type::GROUP,
                                node::Type::DATASET,
                                node::Type::DATASET};
  auto name_iter = names.begin();
  auto type_iter = types.begin();

  for(auto iter = root_.nodes.begin();iter!=root_.nodes.end();++iter)
  {
    EXPECT_EQ(static_cast<std::string>(iter->link().path()),*name_iter++);
    EXPECT_EQ((*iter).type(),*type_iter++);
  }
}

TEST_F(NodeIteration, group_node_foreach)
{
  EXPECT_EQ(root_.nodes.size(),5ul);
  //setup creation order
  root_.iterator_config().index(hdf5::IterationIndex::NAME);
  root_.iterator_config().order(hdf5::IterationOrder::DECREASING);

  std::vector<std::string> names{"/g3","/g2","/g1","/d2","/d1"};
  std::vector<node::Type> types{node::Type::GROUP,
    node::Type::GROUP,
    node::Type::GROUP,
    node::Type::DATASET,
    node::Type::DATASET};
  auto name_iter = names.begin();
  auto type_iter = types.begin();

  for(auto node: root_.nodes)
  {
    EXPECT_EQ(static_cast<std::string>(node.link().path()),*name_iter++);
    EXPECT_EQ(node.type(),*type_iter++);
  }

}



