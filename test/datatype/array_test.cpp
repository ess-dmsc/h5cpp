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
// Created on: Oct 23, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/datatype/array.hpp>
#include <h5cpp/datatype/factory.hpp>

using namespace hdf5;

TEST(Array,DefaultConstruction)
{
  datatype::Array type;
  EXPECT_FALSE(type.is_valid());
  EXPECT_EQ(type.get_class(),datatype::Class::NONE);
}

TEST(Array,TensorConstruction)
{
  auto base_type = datatype::create<int>();
  datatype::Array type(base_type,{3,4});
  EXPECT_TRUE(type.is_valid());
  EXPECT_EQ(type.get_class(),datatype::Class::ARRAY);
  EXPECT_EQ(type.size(),12*sizeof(int));
  EXPECT_EQ(type.rank(),2ul);

  Dimensions dims = type.dimensions();
  EXPECT_EQ(dims[0],3ul);
  EXPECT_EQ(dims[1],4ul);
}

TEST(Array,VectorConstruction)
{
  auto base_type = datatype::create<double>();
  datatype::Array type(base_type,{4});
  EXPECT_TRUE(type.is_valid());
  EXPECT_EQ(type.get_class(),datatype::Class::ARRAY);
  EXPECT_EQ(type.size(),4*sizeof(double));
}
