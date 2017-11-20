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

using namespace hdf5;

class RecursiveNodeIteratorTest : public testing::Test
{
  public:
    file::File file;
    RecursiveNodeIteratorTest() = default;

    virtual void SetUp();

};

void RecursiveNodeIteratorTest::SetUp()
{
  file = file::create("RecursiveNodeIteratorTest.h5",file::AccessFlags::TRUNCATE);
  node::Group root = file.root();

  node::Group(root,Path("g0"));
  node::Group g1(root,Path("g1"));
  node::Group g2(root,Path("g2"));
  node::Dataset(g2,Path("data_1"),datatype::create<int>());
  node::Dataset(g2,Path("data_2"),datatype::create<float>());
  node::Group g1_1(g1,Path("g1_1"));
  node::Group(g1_1,Path("g1_1_1"));
  node::Group(g1_1,Path("g1_1_2"));
  node::Group(g1,Path("g1_2"));
  node::Group(g2,Path("g2_1"));
  node::Group(g2,Path("g2_2"));
}

TEST_F(RecursiveNodeIteratorTest,equality_operator)
{
  using hdf5::node::RecursiveNodeIterator;
  EXPECT_EQ(RecursiveNodeIterator::begin(file.root()),
            RecursiveNodeIterator::begin(file.root()));

  EXPECT_EQ(RecursiveNodeIterator::end(file.root()),
            RecursiveNodeIterator::end(file.root()));


}

TEST_F(RecursiveNodeIteratorTest,test)
{
  using hdf5::node::RecursiveNodeIterator;
  std::vector<Path> node_path{
    Path("/g0"),
    Path("/g1"),
    Path("/g1/g1_1"),
    Path("/g1/g1_1/g1_1_1"),
    Path("/g1/g1_1/g1_1_2"),
    Path("/g1/g1_2"),
    Path("/g2"),
    Path("/g2/data_1"),
    Path("/g2/data_2"),
    Path("/g2/g2_1"),
    Path("/g2/g2_2")
  };

  auto iter = RecursiveNodeIterator::begin(file.root());
  auto end  = RecursiveNodeIterator::end(file.root());
  auto path_iter = node_path.begin();
  while(iter != end)
  {
    node::Node n = *iter++;
    EXPECT_EQ(n.link().path(),*path_iter++);
  }
}
