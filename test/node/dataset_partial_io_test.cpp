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

TEST_F(PartialIO, test_read_write_scalar_int)
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










