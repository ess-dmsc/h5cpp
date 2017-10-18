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
// Created on: Oct 5, 2017
//
#include <cstdint>
#include <vector>
#include "../fixture.hpp"

using namespace hdf5;

class AttributeScalarIO : public BasicFixture
{};

TEST_F(AttributeScalarIO, test_uint8)
{
  attribute::Attribute a = root_.attributes.create<std::uint8_t>("data");
  std::uint8_t write_value = 12;
  std::uint8_t read_value = 0;
  a.write(write_value);
  a.read(read_value);
  EXPECT_EQ(write_value,read_value);
}

TEST_F(AttributeScalarIO, test_float32)
{
  attribute::Attribute a = root_.attributes.create<float>("data");
  float write_value = 3.213e-2;
  float read_value = 0.0;
  a.write(write_value);
  a.read(read_value);
  EXPECT_NEAR(write_value,read_value,0.001);
}

TEST_F(AttributeScalarIO, test_vector_io)
{
  //this should work as the size of the vector is one
  attribute::Attribute a = root_.attributes.create<std::uint8_t>("data");
  std::vector<std::uint8_t> write_data{42};
  std::vector<std::uint8_t> read_data(1);
  EXPECT_NO_THROW(a.write(write_data));
  EXPECT_NO_THROW(a.read(read_data));
  EXPECT_EQ(write_data, read_data);

}

TEST_F(AttributeScalarIO, test_shape_mismatch)
{
  //this should work too - however, only the first element of the vector
  //is written and read.
  attribute::Attribute a = root_.attributes.create<float>("data");
  std::vector<float> write_data{1.2f,3.4f};
  std::vector<float> read_data(3);
  EXPECT_NO_THROW(a.write(write_data));
  EXPECT_NO_THROW(a.read(read_data));
  EXPECT_NEAR(write_data[0],read_data[0],0.0002);
}






