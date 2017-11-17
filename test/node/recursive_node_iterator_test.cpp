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

  node::Group g1(root,Path("g1"));
  node::Group g2(root,Path("g2"));
  node::Group g1_1(g1,Path("g1_1"));
  node::Group(g1_1,Path("g1_1_1"));
  node::Group(g1_1,Path("g1_1_2"));
  node::Group(g1,Path("g1_2"));
  node::Group(g2,Path("g2_1"));
  node::Group(g2,Path("g2_2"));
}

TEST_F(RecursiveNodeIteratorTest,test)
{
  node::Group root = file.root();
  node::RecursiveNodeIterator iter(root);
  for(size_t index=0;index<6;index++)
  {

    node::Node n = *iter;
    std::cout<<n.link().path()<<std::endl;
    ++iter;
  }
}
