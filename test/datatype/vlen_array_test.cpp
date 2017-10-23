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

TEST(VLengthArray,DefaultConstruction)
{
  datatype::VLengthArray type;
  EXPECT_FALSE(type.is_valid());
  EXPECT_EQ(type.get_class(),datatype::Class::NONE);

}

TEST(VLengthArray,Construction)
{
  auto base_type = datatype::create<double>();
  datatype::VLengthArray type(base_type);
  EXPECT_TRUE(type.is_valid());
  EXPECT_EQ(type.get_class(),datatype::Class::VARLENGTH);
  EXPECT_EQ(type.super().get_class(),datatype::Class::FLOAT);
  EXPECT_NE(type.super().get_class(),datatype::Class::INTEGER);
  EXPECT_EQ(type.super(),base_type);
  EXPECT_EQ(type.size(),datatype::kVariable);
}
