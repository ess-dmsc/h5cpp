//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5cpp.
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
// Created on: Oct 11, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/dataspace/points.hpp>
#include "group_test_fixtures.hpp"

using namespace hdf5;

class PartialIO : public BasicFixture
{
  protected:
    property::LinkCreationList lcpl;
    property::DatasetCreationList dcpl;

    virtual void SetUp()
    {
      BasicFixture::SetUp();
      dcpl.layout(property::DatasetLayout::CHUNKED);
    }

};

TEST_F(PartialIO, test_read_write_hyperslab)
{
  dataspace::Simple space{{0},{dataspace::Simple::UNLIMITED}};
  auto type = datatype::create<int>();
  int write_value = 0,
      read_value = 0;
  dcpl.chunk({1024});

  node::Dataset dset(root_,Path("data"),type,space,lcpl,dcpl);

  dataspace::Hyperslab slab{{0},{1},{1},{1}};

  for(size_t index=0;index<100;index++)
  {
    dset.extent(0,1);
    slab.offset(0,index);
    dset.write(write_value,slab);
    dset.read(read_value,slab);
    EXPECT_EQ(write_value,read_value);
  }
}


TEST_F(PartialIO, test_read_write_points)
{
  dataspace::Simple space{{10,10}};
  auto type = datatype::create<int>();

  node::Dataset dset(root_,Path("data"),type,space);

  dataspace::Points pts{2};
  pts.add({1,1});
  pts.add({2,2});
  pts.add({3,3});
  pts.add({4,4});
  pts.add({5,5});
  std::vector<int> write {1,2,3,4,5};
  dset.write(write, pts);

  dataspace::Points pts2{2};
  pts2.add({1,1});
  pts2.add({3,3});
  pts2.add({5,5});
  std::vector<int> read(3);
  dset.read(read, pts2);

  EXPECT_EQ(read, std::vector<int>({1,3,5}));
}









