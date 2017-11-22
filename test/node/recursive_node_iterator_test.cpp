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
// Created on: Nov 17, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>
#include <algorithm>
#include "group_test_fixtures.hpp"

using namespace hdf5;

class RecursiveNodeIteratorTest : public RecursiveIterationFixture
{
  public:
    RecursiveNodeIteratorTest():
      RecursiveIterationFixture("RecursiveNodeIteratorTest.h5")
    {}



};


TEST_F(RecursiveNodeIteratorTest,equality_operator)
{
  using hdf5::node::RecursiveNodeIterator;
  EXPECT_EQ(RecursiveNodeIterator::begin(file.root()),
            RecursiveNodeIterator::begin(file.root()));

  EXPECT_EQ(RecursiveNodeIterator::end(file.root()),
            RecursiveNodeIterator::end(file.root()));
}

TEST_F(RecursiveNodeIteratorTest,test_name_increasing)
{

  using hdf5::node::RecursiveNodeIterator;
  std::vector<Path> node_path{
    Path("/standard/a_group"),
    Path("/standard/a_group/a_a_group"),
    Path("/standard/a_group/b_a_group"),
    Path("/standard/a_group/c_a_group"),
    Path("/standard/a_group/d_a_dataset"),
    Path("/standard/a_group/e_a_dataset"),
    Path("/standard/b_group"),
    Path("/standard/b_group/a_b_group"),
    Path("/standard/b_group/a_b_group/data"),
    Path("/standard/b_group/b_b_group"),
    Path("/standard/b_group/c_b_group"),
    Path("/standard/b_group/c_b_group/data"),
    Path("/standard/c_group")};

  node::Group base = node::get_node(file.root(),Path("standard"));
  base.iterator_config().index(IterationIndex::NAME);
  base.iterator_config().order(IterationOrder::INCREASING);
  auto path_iter = node_path.begin();

  std::for_each(RecursiveNodeIterator::begin(base),
                RecursiveNodeIterator::end(base),
                [&path_iter](const node::Node &node)
                { EXPECT_EQ(node.link().path(),*path_iter++);}
                );
}

TEST_F(RecursiveNodeIteratorTest,test_name_decreasing)
{

  using hdf5::node::RecursiveNodeIterator;
  std::vector<Path> node_path{
    Path("/standard/c_group"),
    Path("/standard/b_group"),
    Path("/standard/b_group/c_b_group"),
    Path("/standard/b_group/c_b_group/data"),
    Path("/standard/b_group/b_b_group"),
    Path("/standard/b_group/a_b_group"),
    Path("/standard/b_group/a_b_group/data"),
    Path("/standard/a_group"),
    Path("/standard/a_group/e_a_dataset"),
    Path("/standard/a_group/d_a_dataset"),
    Path("/standard/a_group/c_a_group"),
    Path("/standard/a_group/b_a_group"),
    Path("/standard/a_group/a_a_group")
   };

  node::Group base = node::get_node(file.root(),Path("standard"));
  base.iterator_config().index(IterationIndex::NAME);
  base.iterator_config().order(IterationOrder::DECREASING);
  auto path_iter = node_path.begin();

  std::for_each(RecursiveNodeIterator::begin(base),
                RecursiveNodeIterator::end(base),
                [&path_iter](const node::Node &node)
                { EXPECT_EQ(node.link().path(),*path_iter++);}
                );
}
