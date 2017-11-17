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
#include "../fixture.hpp"

using namespace hdf5;

class ChunkedDatasetTest : public BasicFixture
{

};

TEST_F(ChunkedDatasetTest,test_construction)
{
  auto type = datatype::create<int>();
  dataspace::Simple space{{0,1024},{dataspace::Simple::UNLIMITED,1024}};
  node::ChunkedDataset dset(root_,Path("data"),type,space,{1024,1024});

  property::DatasetCreationList dcpl = dset.creation_list();
  EXPECT_EQ(dcpl.layout(),property::DatasetLayout::CHUNKED);
}

