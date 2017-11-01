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
// Created on: Sep 7, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/dataspace/type_trait.hpp>

using namespace hdf5;

TEST(TypeTrait, test_vector)
{
  std::vector<double> data(20);
  auto space = dataspace::create(data);
  EXPECT_EQ(space.type(),dataspace::Type::SIMPLE);
  Dimensions current_dims = space.current_dimensions(),
             max_dims = space.maximum_dimensions();
  EXPECT_EQ(current_dims.size(),1ul);
  EXPECT_EQ(current_dims[0],20ul);
  EXPECT_EQ(max_dims.size(),1ul);
  EXPECT_EQ(max_dims[0],20ul);
}

TEST(TypeTrait, test_scalar)
{
  int data=10;
  auto space = dataspace::create(data);
  EXPECT_EQ(space.type(),dataspace::Type::SCALAR);
  EXPECT_EQ(space.size(),1l);
}


