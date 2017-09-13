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
#include <boost/test/unit_test.hpp>

#include "group_test_fixtures.hpp"
#include <h5cpp/node/link.hpp>

using namespace hdf5;

BOOST_AUTO_TEST_SUITE(group_test)
BOOST_FIXTURE_TEST_SUITE(group_link_iteration,LinkIterationFixture)

BOOST_AUTO_TEST_CASE(group_index_name_order_access)
{
  BOOST_CHECK_EQUAL(root_group.links.size(),5);
  //setup creation order
  root_group.iterator_config().index(hdf5::IterationIndex::NAME);
  root_group.iterator_config().order(hdf5::IterationOrder::DECREASING);

  BOOST_CHECK_EQUAL(root_group.links[0].type(),node::LinkType::HARD);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.links[0].path()),"/g3");
  BOOST_CHECK_EQUAL(root_group.links[1].type(),node::LinkType::HARD);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.links[1].path()),"/g2");
  BOOST_CHECK_EQUAL(root_group.links[2].type(),node::LinkType::HARD);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.links[2].path()),"/g1");
  BOOST_CHECK_EQUAL(root_group.links[3].type(),node::LinkType::HARD);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.links[3].path()),"/d2");
  BOOST_CHECK_EQUAL(root_group.links[4].type(),node::LinkType::HARD);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.links[4].path()),"/d1");
}

BOOST_AUTO_TEST_CASE(group_index_creation_order_access)
{
  BOOST_CHECK_EQUAL(root_group.links.size(),5);
  //setup creation order
  root_group.iterator_config().index(hdf5::IterationIndex::CREATION_ORDER);
  root_group.iterator_config().order(hdf5::IterationOrder::INCREASING);

  BOOST_CHECK_EQUAL(root_group.links[0].type(),node::LinkType::HARD);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.links[0].path()),"/g1");
  BOOST_CHECK_EQUAL(root_group.links[1].type(),node::LinkType::HARD);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.links[1].path()),"/g2");
  BOOST_CHECK_EQUAL(root_group.links[2].type(),node::LinkType::HARD);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.links[2].path()),"/g3");
  BOOST_CHECK_EQUAL(root_group.links[3].type(),node::LinkType::HARD);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.links[3].path()),"/d1");
  BOOST_CHECK_EQUAL(root_group.links[4].type(),node::LinkType::HARD);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root_group.links[4].path()),"/d2");
}

BOOST_AUTO_TEST_CASE(group_name_access)
{
  node::Link l;
  BOOST_CHECK_NO_THROW(l=root_group.links["g1"]);
  BOOST_CHECK_EQUAL(l.type(),node::LinkType::HARD);
  BOOST_CHECK_EQUAL(static_cast<std::string>(l.path()),"/g1");
  BOOST_CHECK_NO_THROW(l=root_group.links["d1"]);
  BOOST_CHECK_EQUAL(l.type(),node::LinkType::HARD);
  BOOST_CHECK_EQUAL(static_cast<std::string>(l.path()),"/d1");

}

BOOST_AUTO_TEST_CASE(group_node_iteration)
{
  BOOST_CHECK_EQUAL(root_group.links.size(),5);
  //setup creation order
  root_group.iterator_config().index(hdf5::IterationIndex::NAME);
  root_group.iterator_config().order(hdf5::IterationOrder::DECREASING);

  std::vector<std::string> names{"/g3","/g2","/g1","/d2","/d1"};
  auto name_iter = names.begin();

  for(auto iter = root_group.links.begin();iter!=root_group.links.end();++iter)
  {
    BOOST_CHECK_EQUAL(static_cast<std::string>(iter->path()),*name_iter++);
    BOOST_CHECK_EQUAL((*iter).type(),node::LinkType::HARD);
  }
}

BOOST_AUTO_TEST_CASE(group_node_foreach)
{
  BOOST_CHECK_EQUAL(root_group.links.size(),5);
  //setup creation order
  root_group.iterator_config().index(hdf5::IterationIndex::NAME);
  root_group.iterator_config().order(hdf5::IterationOrder::DECREASING);

  std::vector<std::string> names{"/g3","/g2","/g1","/d2","/d1"};
  auto name_iter = names.begin();

  for(auto link: root_group.links)
  {
    BOOST_CHECK_EQUAL(static_cast<std::string>(link.path()),*name_iter++);
    BOOST_CHECK_EQUAL(link.type(),node::LinkType::HARD);
  }

}

BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
