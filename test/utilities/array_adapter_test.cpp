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
#include <h5cpp/hdf5.hpp>
#include <gtest/gtest.h>
#include "../h5cpp_test_helpers.hpp"
#include "../gtest_print.hpp"

#include <cstring>

using namespace hdf5;

#define bufsize 7

using IntegerArrayAdapter = ArrayAdapter<int>;
using DoubleArrayAdapter = ArrayAdapter<double>;

class ArrayAdapterTest : public testing::Test
{
 protected:
  int *integer_data;

  virtual void SetUp()
  {
    // redirect stderr into buf
    integer_data = new int[bufsize];
    for(size_t index=0;index<bufsize;index++)
      integer_data[index] = index;
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

TEST_F(ArrayAdapterTest, copy_construction)
{
  ArrayAdapter<int> a1(integer_data,bufsize);
  ArrayAdapter<int> a2(a1);

  EXPECT_EQ(a1.data(),integer_data);
  EXPECT_EQ(a1.size(),a2.size());
  EXPECT_EQ(a1.data(),a2.data());
}

TEST_F(ArrayAdapterTest, move_construction)
{
  ArrayAdapter<int> a1(integer_data,bufsize);
  ArrayAdapter<int> a2(std::move(a1));

  EXPECT_EQ(a1.data(),nullptr);
  EXPECT_EQ(a1.size(),0);

  EXPECT_EQ(a2.data(),integer_data);
  EXPECT_EQ(a2.size(),bufsize);
}

TEST_F(ArrayAdapterTest, copy_assignment)
{
  ArrayAdapter<int> a1(integer_data,bufsize);
  ArrayAdapter<int> a2;

  a2 = a1;
  EXPECT_EQ(a1.data(),a2.data());
  EXPECT_EQ(a1.size(),a2.size());
}

TEST_F(ArrayAdapterTest, move_assignment)
{
  ArrayAdapter<int> a1(integer_data,bufsize);
  ArrayAdapter<int> a2;

  a2 = std::move(a1);
  EXPECT_EQ(a1.data(),nullptr);
  EXPECT_EQ(a1.size(),0);
  EXPECT_EQ(a2.data(),integer_data);
  EXPECT_EQ(a2.size(),bufsize);
}

TEST_F(ArrayAdapterTest, datatype_type_trait)
{
  datatype::Datatype itype = datatype::TypeTrait<IntegerArrayAdapter>::create();
  EXPECT_EQ(itype.get_class(),datatype::Class::INTEGER);
  datatype::Integer it(itype);
  EXPECT_EQ(it.size(),4);


  datatype::Datatype dtype = datatype::TypeTrait<DoubleArrayAdapter>::create();
  EXPECT_EQ(dtype.get_class(),datatype::Class::FLOAT);
  datatype::Float dt(dtype);
  EXPECT_EQ(dt.size(),8);
}

TEST_F(ArrayAdapterTest, dataset_io)
{
  file::File file = file::create("ArrayAdapterTest.h5",file::AccessFlags::TRUNCATE);
  node::Group root = file.root();
  node::Dataset dataset(root,"data",datatype::create<int>(),dataspace::Simple(Dimensions{bufsize}));

  dataset.write(IntegerArrayAdapter(integer_data,bufsize));

  int read_data[bufsize];
  IntegerArrayAdapter adapter(read_data,bufsize);
  dataset.read(adapter);
  EXPECT_EQ(read_data[0],0);
  EXPECT_EQ(read_data[1],1);
  EXPECT_EQ(read_data[2],2);
  EXPECT_EQ(read_data[3],3);
  EXPECT_EQ(read_data[4],4);
  EXPECT_EQ(read_data[5],5);
  EXPECT_EQ(read_data[6],6);

}

