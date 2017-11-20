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

using namespace hdf5;

class RecursiveNodeIteratorTest : public testing::Test
{
  public:
    property::FileCreationList fcpl;
    property::FileAccessList   fapl;
    file::File file;
    RecursiveNodeIteratorTest();

    virtual void SetUp();

};

RecursiveNodeIteratorTest::RecursiveNodeIteratorTest():
    fcpl(),
    fapl(),
    file()
{
  fapl.library_version_bounds(property::LibVersion::LATEST,
                              property::LibVersion::LATEST);
}

void RecursiveNodeIteratorTest::SetUp()
{
  file = file::create("RecursiveNodeIteratorTest.h5",
                      file::AccessFlags::TRUNCATE,fcpl,fapl);
  node::Group root = file.root();

  node::Group(root,Path("c_group"));
  node::Group b_group(root,Path("b_group"));
  node::Group a_group(root,Path("a_group"));

  node::Group(a_group,Path("c_a_group"));
  node::Group(a_group,Path("b_a_group"));
  node::Group(a_group,Path("a_a_group"));
  node::Dataset(a_group,Path("d_a_dataset"),datatype::create<int>());
  node::Dataset(a_group,Path("e_a_dataset"),datatype::create<int>());

  node::Group(b_group,Path("c_b_group"));
  node::Group(b_group,Path("b_b_group"));
  node::Group(b_group,Path("a_b_group"));
  file.flush(file::Scope::GLOBAL);
}

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
    Path("/a_group"),
    Path("/a_group/a_a_group"),
    Path("/a_group/b_a_group"),
    Path("/a_group/c_a_group"),
    Path("/a_group/d_a_dataset"),
    Path("/a_group/e_a_dataset"),
    Path("/b_group"),
    Path("/b_group/a_b_group"),
    Path("/b_group/b_b_group"),
    Path("/b_group/c_b_group"),
    Path("/c_group")};

  node::Group root = file.root();
  root.iterator_config().index(IterationIndex::NAME);
  root.iterator_config().order(IterationOrder::INCREASING);
  auto path_iter = node_path.begin();

  std::for_each(RecursiveNodeIterator::begin(root),
                RecursiveNodeIterator::end(root),
                [&path_iter](const node::Node &node)
                { EXPECT_EQ(node.link().path(),*path_iter++);}
                );
}

TEST_F(RecursiveNodeIteratorTest,test_name_decreasing)
{

  using hdf5::node::RecursiveNodeIterator;
  std::vector<Path> node_path{
    Path("/c_group"),
    Path("/b_group"),
    Path("/b_group/c_b_group"),
    Path("/b_group/b_b_group"),
    Path("/b_group/a_b_group"),
    Path("/a_group"),
    Path("/a_group/e_a_dataset"),
    Path("/a_group/d_a_dataset"),
    Path("/a_group/c_a_group"),
    Path("/a_group/b_a_group"),
    Path("/a_group/a_a_group")
   };

  node::Group root = file.root();
  root.iterator_config().index(IterationIndex::NAME);
  root.iterator_config().order(IterationOrder::DECREASING);
  auto path_iter = node_path.begin();

  std::for_each(RecursiveNodeIterator::begin(root),
                RecursiveNodeIterator::end(root),
                [&path_iter](const node::Node &node)
                { EXPECT_EQ(node.link().path(),*path_iter++);}
                );
}
