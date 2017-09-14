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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing group creation
#include <vector>
#include "group_test_fixtures.hpp"

using boost::test_tools::output_test_stream;
using namespace hdf5;


BOOST_AUTO_TEST_SUITE(group_test)

BOOST_FIXTURE_TEST_SUITE(group_basics,BasicTestFixture)

BOOST_AUTO_TEST_CASE(test_root_group)
{
  node::Group root;
  BOOST_CHECK_NO_THROW(root = file.root());
  BOOST_CHECK(root.is_valid());
  BOOST_CHECK_EQUAL(root.type(),node::Type::GROUP);
  BOOST_CHECK_EQUAL(root.links.size(),0);
  BOOST_CHECK_EQUAL(root.nodes.size(),0);
  BOOST_CHECK_EQUAL(static_cast<std::string>(root.path()),"/");
}

BOOST_AUTO_TEST_CASE(test_default_construction)
{
  node::Group group;
  BOOST_CHECK(!group.is_valid());
}

BOOST_AUTO_TEST_CASE(test_group_creation)
{
  node::Group g = file.root();
  BOOST_CHECK_NO_THROW(g.create_group("group_1"));
  BOOST_CHECK_NO_THROW(g.create_group("group_2"));
  BOOST_CHECK_EQUAL(g.nodes.size(),2);
  BOOST_CHECK_EQUAL(g.links.size(),2);

}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()
