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
// Created on: Nov 20, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>
#include <algorithm>
#include "group_test_fixtures.hpp"

using namespace hdf5;

class RecursiveLinkIteratorTest : public RecursiveIterationFixture
{
  public:
    RecursiveLinkIteratorTest():
      RecursiveIterationFixture("RecursiveLinkIteratorTest.h5")
    {}
};


TEST_F(RecursiveLinkIteratorTest,equality_operator)
{
  using hdf5::node::RecursiveLinkIterator;
  EXPECT_EQ(RecursiveLinkIterator::begin(file.root()),
            RecursiveLinkIterator::begin(file.root()));

  EXPECT_EQ(RecursiveLinkIterator::end(file.root()),
            RecursiveLinkIterator::end(file.root()));
}

TEST_F(RecursiveLinkIteratorTest,test_name_increasing)
{

  using hdf5::node::RecursiveLinkIterator;
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

  node::Group root = node::get_node(file.root(),Path("standard"));
  root.iterator_config().index(IterationIndex::NAME);
  root.iterator_config().order(IterationOrder::INCREASING);
  auto path_iter = node_path.begin();

  EXPECT_TRUE(node::Link(file,Path("/standard/b_group/c_b_group"),"data").is_resolvable());

  auto iter = RecursiveLinkIterator::begin(root);
  auto end  = RecursiveLinkIterator::end(root);
  while(iter!=end)
  {
    node::Link l = *iter;
    std::cout<<l.path()<<std::endl;
    ++iter;
  }
//  std::for_each(RecursiveLinkIterator::begin(root),
//                RecursiveLinkIterator::end(root),
//                [&path_iter](const node::Link &link)
//                { EXPECT_EQ(link.path(),*path_iter++);}
//                );
}

TEST_F(RecursiveLinkIteratorTest,test_name_decreasing)
{

  using hdf5::node::RecursiveLinkIterator;
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

  node::Group root = node::get_node(file.root(),Path("standard"));
  root.iterator_config().index(IterationIndex::NAME);
  root.iterator_config().order(IterationOrder::DECREASING);
  auto path_iter = node_path.begin();

  auto iter = RecursiveLinkIterator::begin(root);
  auto end  = RecursiveLinkIterator::end(root);
  while(iter!=end)
  {
    node::Link l = *iter;
    std::cout<<l.path()<<std::endl;
    ++iter;
  }

//  std::for_each(RecursiveLinkIterator::begin(root),
//                RecursiveLinkIterator::end(root),
//                [&path_iter](const node::Link &link)
//                { EXPECT_EQ(link.path(),*path_iter++);}
//                );
}

TEST_F(RecursiveLinkIteratorTest,test_linked_group)
{
  using hdf5::node::RecursiveLinkIterator;
  node::Group base = node::get_node(file.root(),Path("linkTest"));

  property::LinkAccessList lapl;
  std::cout<<lapl.maximum_link_traversals()<<std::endl;

  auto iter = RecursiveLinkIterator::begin(base);
  auto end  = RecursiveLinkIterator::end(base);
  while(iter!=end)
  {
    node::Link l = *iter;
    std::cout<<l.path()<<std::endl;
    ++iter;
  }

}
