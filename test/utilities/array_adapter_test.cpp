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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 25, 2017
//

#include <h5cpp/utilities/array_adapter.hpp>
#include <h5cpp/core/types.hpp>
#include <gtest/gtest.h>
#include "../h5cpp_test_helpers.hpp"
#include "../gtest_print.hpp"

#include <cstring>

using namespace hdf5;

#define bufsize 7000

class ArrayAdapterTest : public testing::Test
{
 protected:
  int *integer_data;

  virtual void SetUp()
  {
    // redirect stderr into buf
    integer_data = new int[bufsize];
  }

  virtual void TearDown()
  {
    delete integer_data;
  }
};

TEST_F(ArrayAdapterTest, default_construction)
{
  ArrayAdapter<int> adapter;
  EXPECT_EQ(adapter.data(),nullptr);
  EXPECT_EQ(adapter.size(),0);
  Dimensions dims = get_dimensions(adapter);
  EXPECT_EQ(dims.size(),1);
  EXPECT_EQ(dims[0],0);
}

TEST_F(ArrayAdapterTest, constructor_construction)
{
  ArrayAdapter<int> adapter(integer_data,bufsize);
  EXPECT_EQ(adapter.data(),integer_data);
  EXPECT_EQ(adapter.size(),bufsize);
  Dimensions dimensions = get_dimensions(adapter);
  EXPECT_EQ(dimensions.size(),1);
  EXPECT_EQ(dimensions[0],bufsize);
}
