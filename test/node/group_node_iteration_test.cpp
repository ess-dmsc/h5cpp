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

using namespace hdf5;

BOOST_AUTO_TEST_SUITE(group_test)
BOOST_FIXTURE_TEST_SUITE(group_node_iteration,NodeIterationFixture)

BOOST_AUTO_TEST_CASE(group_index_name_order_access)
{
  BOOST_CHECK_EQUAL(root_group.nodes.size(),5);
  //setup creation order
  root_group.iterator_config().index(hdf5::IterationIndex::NAME);
  root_group.iterator_config().order(hdf5::IterationOrder::DECREASING);

  BOOST_CHECK_EQUAL(root_group.nodes[0].type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[0].path()),"/g3");
  BOOST_CHECK_EQUAL(root_group.nodes[1].type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[1].path()),"/g2");
  BOOST_CHECK_EQUAL(root_group.nodes[2].type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[2].path()),"/g1");
  BOOST_CHECK_EQUAL(root_group.nodes[3].type(),node::Type::DATASET);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[3].path()),"/d2");
  BOOST_CHECK_EQUAL(root_group.nodes[4].type(),node::Type::DATASET);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[4].path()),"/d1");
}

BOOST_AUTO_TEST_CASE(group_index_creation_order_access)
{
  BOOST_CHECK_EQUAL(root_group.nodes.size(),5);
  //setup creation order
  root_group.iterator_config().index(hdf5::IterationIndex::CREATION_ORDER);
  root_group.iterator_config().order(hdf5::IterationOrder::INCREASING);

  BOOST_CHECK_EQUAL(root_group.nodes[0].type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[0].path()),"/g1");
  BOOST_CHECK_EQUAL(root_group.nodes[1].type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[1].path()),"/g2");
  BOOST_CHECK_EQUAL(root_group.nodes[2].type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[2].path()),"/g3");
  BOOST_CHECK_EQUAL(root_group.nodes[3].type(),node::Type::DATASET);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[3].path()),"/d1");
  BOOST_CHECK_EQUAL(root_group.nodes[4].type(),node::Type::DATASET);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.nodes[4].path()),"/d2");
}

BOOST_AUTO_TEST_CASE(group_name_access)
{
  node::Node n;
  BOOST_CHECK_NO_THROW(n=root_group.nodes["g1"]);
  BOOST_CHECK_EQUAL(n.type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(static_cast<std::string>(n.path()),"/g1");
  BOOST_CHECK_NO_THROW(n=root_group.nodes["d1"]);
  BOOST_CHECK_EQUAL(n.type(),node::Type::DATASET);
  BOOST_CHECK_EQUAL(static_cast<std::string>(n.path()),"/d1");

}

BOOST_AUTO_TEST_CASE(group_node_iteration)
{
  BOOST_CHECK_EQUAL(root_group.nodes.size(),5);
  //setup creation order
  root_group.iterator_config().index(hdf5::IterationIndex::NAME);
  root_group.iterator_config().order(hdf5::IterationOrder::DECREASING);

  std::vector<std::string> names{"/g3","/g2","/g1","/d2","/d1"};
  std::vector<node::Type> types{node::Type::GROUP,
                                node::Type::GROUP,
                                node::Type::GROUP,
                                node::Type::DATASET,
                                node::Type::DATASET};
  auto name_iter = names.begin();
  auto type_iter = types.begin();

  for(auto iter = root_group.nodes.begin();iter!=root_group.nodes.end();++iter)
  {
    BOOST_CHECK_EQUAL(static_cast<std::string>(iter->path()),*name_iter++);
    BOOST_CHECK_EQUAL((*iter).type(),*type_iter++);
  }
}

BOOST_AUTO_TEST_CASE(group_node_foreach)
{
  BOOST_CHECK_EQUAL(root_group.nodes.size(),5);
  //setup creation order
  root_group.iterator_config().index(hdf5::IterationIndex::NAME);
  root_group.iterator_config().order(hdf5::IterationOrder::DECREASING);

  std::vector<std::string> names{"/g3","/g2","/g1","/d2","/d1"};
  std::vector<node::Type> types{node::Type::GROUP,
    node::Type::GROUP,
    node::Type::GROUP,
    node::Type::DATASET,
    node::Type::DATASET};
  auto name_iter = names.begin();
  auto type_iter = types.begin();

  for(auto node: root_group.nodes)
  {
    BOOST_CHECK_EQUAL(static_cast<std::string>(node.path()),*name_iter++);
    BOOST_CHECK_EQUAL(node.type(),*type_iter++);
  }

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
