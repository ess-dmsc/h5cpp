
//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// h5cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// h5cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the imndied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with h5cpp.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 2, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing node creation

#include <h5cpp/node/node.hpp>
#include <h5cpp/node/functions.hpp>

#include "group_test_fixtures.hpp"

using boost::test_tools::output_test_stream;
using namespace hdf5;
namespace nd = hdf5::node;

BOOST_AUTO_TEST_SUITE(NodeTest)

BOOST_FIXTURE_TEST_SUITE(node_basics,BasicTestFixture)

BOOST_AUTO_TEST_CASE(test_default_construction)
{
  nd::Node n;
}

BOOST_AUTO_TEST_CASE(test_equality_operator)
{
  nd::Node m, n;
  BOOST_CHECK(m == n);
  BOOST_CHECK(!(m != n));

  nd::Group g = file.root();
  auto g2 = g.create_group("group_1");
  BOOST_CHECK(g != g2);
}

BOOST_AUTO_TEST_CASE(test_remove_node)
{
  nd::Group f = file.root();

  f.create_group("group");
  BOOST_CHECK(f.exists("group"));
  BOOST_CHECK_NO_THROW(nd::remove(f, Path("group")));
  BOOST_CHECK(!f.exists("group"));

  BOOST_CHECK_THROW(nd::remove(f, Path("group")), std::runtime_error);

  auto g = f.create_group("group2");
  BOOST_CHECK(f.exists("group2"));
  BOOST_CHECK_NO_THROW(nd::remove(g));
  BOOST_CHECK(!f.exists("group2"));
}

BOOST_AUTO_TEST_CASE(test_copy_node)
{
  nd::Group f = file.root();
  auto g1 = f.create_group("group_1");
  auto gt = g1.create_group("target");
  auto g2 = f.create_group("group_2");

  BOOST_CHECK(!g2.exists("gt"));
  BOOST_CHECK_NO_THROW(nd::copy(gt, g2, Path("gt")));
  BOOST_CHECK(g2.exists("gt"));
  BOOST_CHECK_THROW(nd::copy(gt, g2, Path("gt")), std::runtime_error);

  BOOST_CHECK_NO_THROW(nd::copy(gt, g2));
  BOOST_CHECK(g2.exists("target"));

  BOOST_CHECK_NO_THROW(nd::copy(gt, f));
  BOOST_CHECK(f.exists("target"));

  BOOST_CHECK_THROW(nd::copy(gt, f), std::runtime_error);

  //copying root does not work
  BOOST_CHECK_THROW(nd::copy(f, g2), std::runtime_error);
}

BOOST_AUTO_TEST_CASE(test_move_node)
{
  nd::Group f = file.root();
  auto g1 = f.create_group("group_1");
  auto gt = g1.create_group("target");
  auto g2 = f.create_group("group_2");

  BOOST_CHECK(g1.exists("target"));
  BOOST_CHECK(!g2.exists("gt"));
  BOOST_CHECK_NO_THROW(nd::move(gt, g2, Path("gt")));
  BOOST_CHECK(!g1.exists("target"));
  BOOST_CHECK(g2.exists("gt"));

  nd::Group gm = g2["gt"];
  BOOST_CHECK_NO_THROW(nd::move(gm, g1));
  BOOST_CHECK(g1.exists("gt"));
  BOOST_CHECK(!g2.exists("gt"));
  BOOST_CHECK_THROW(nd::move(gm, g1), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()




