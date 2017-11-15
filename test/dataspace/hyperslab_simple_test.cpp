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
// Created on: Aug 25, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/dataspace/simple.hpp>
#include <h5cpp/dataspace/selection.hpp>

using namespace hdf5;

TEST(HyperslabSimple, test_case_1)
{
  dataspace::Simple space({10,20});
  EXPECT_EQ(space.rank(),2);
  EXPECT_EQ(space.size(),200);
  dataspace::Hyperslab slab({1,1},{5,5},{1,1},{1,1});
  space.selection(dataspace::SelectionOperation::SET,slab);
  EXPECT_EQ(space.selection.size(),25ul);
  EXPECT_EQ(space.selection.type(),dataspace::SelectionType::HYPERSLAB);

  EXPECT_NO_THROW(space.selection.all());
  EXPECT_EQ(space.selection.type(),dataspace::SelectionType::ALL);
}

TEST(HyperslabSimple, test_case_2)
{
  dataspace::Simple space({10,1024,1024});
  EXPECT_EQ(space.selection.type(),dataspace::SelectionType::ALL);

  dataspace::Hyperslab frame({0,0,0},{1,1024,1024},{1,1,1},{1,1,1});
  EXPECT_NO_THROW(space.selection(dataspace::SelectionOperation::SET,frame));
  frame.offset(0,9);
  EXPECT_NO_THROW(space.selection(dataspace::SelectionOperation::OR,frame));
  EXPECT_EQ(space.selection.size(),2ul*1024ul*1024ul);

}

TEST(HyperslabSimple,test_nothing_and_all_selected)
{
  dataspace::Simple space({10,1024});
  EXPECT_EQ(space.size(),10l*1024l);
  EXPECT_EQ(space.selection.size(),10ul*1024ul);

  space.selection.none();
  EXPECT_EQ(space.size(),10l*1024l);
  EXPECT_EQ(space.selection.size(),0ul);

  space.selection.all();
  EXPECT_EQ(space.size(),10l*1024l);
  EXPECT_EQ(space.selection.size(),10ul*1024ul);
}

TEST(HyperslabSimple,test_roi_construction)
{
  dataspace::Simple space({10,1024});
  dataspace::Hyperslab slice{{0,0},{1,1024}};
  space.selection(dataspace::SelectionOperation::SET,slice);
  EXPECT_EQ(space.selection.size(),1024ul);
}

TEST(HyperslabSimple,test_scatter_construction)
{
  dataspace::Simple space{{20,1024}};
  dataspace::Hyperslab selection{{1,1},{3,10},{2,4}};
  space.selection(dataspace::SelectionOperation::SET,selection);
  EXPECT_EQ(space.selection.size(),30ul);
}

TEST(HyperslabSimple,test_dataspace_copy_with_selection)
{
  dataspace::Simple space{{20,1024}};
  dataspace::Hyperslab selection{{1,1},{3,10},{2,4}};
  space.selection(dataspace::SelectionOperation::SET,selection);
  EXPECT_EQ(space.selection.size(),30ul);

  dataspace::Simple new_space(space);
  EXPECT_EQ(new_space.selection.size(),30ul);
}


