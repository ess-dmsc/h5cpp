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
// Created on: Nov 22, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>
#include "../fixture.hpp"

using namespace hdf5::node;

class IsGroupTest : public BasicFixture
{

};

TEST_F(IsGroupTest, test_with_default_constructed_node)
{
  EXPECT_THROW(is_group(Node()),std::runtime_error);
}

TEST_F(IsGroupTest,test_with_group)
{
  EXPECT_TRUE(is_group(root_));
}

TEST_F(IsGroupTest,test_with_dataset)
{
  Dataset dset(root_,hdf5::Path("data"),hdf5::datatype::create<int>());
  EXPECT_FALSE(is_group(dset));
}
