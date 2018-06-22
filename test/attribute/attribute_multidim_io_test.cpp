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
// Authors:
//       Eugen Wintersberger <eugen.wintersberger@desy.de>
//       Jan Kotanski <jan.kotanski@desy.de>
// Created on: Oct 5, 2017
//
#include "../fixture.hpp"
#include <cstdint>
#include <vector>
#include <array>

using namespace hdf5;

class AttributeMultidimIO : public BasicFixture
{};

TEST_F(AttributeMultidimIO, test_uint8_vector)
{
  std::vector<std::uint8_t> write_data{1,2,3};
  std::vector<std::uint8_t> read_data(write_data.size());

  attribute::Attribute a = root_.attributes.create<std::uint8_t>("data",{3});
  a.write(write_data);
  a.read(read_data);
  EXPECT_EQ(write_data, read_data);
}

TEST_F(AttributeMultidimIO, test_uint8_array)
{
  std::array<std::uint8_t,3> write_data{1,2,3};
  std::array<std::uint8_t,3> read_data;

  attribute::Attribute a = root_.attributes.create<std::uint8_t>("data",{3});
  a.write(write_data);
  a.read(read_data);
  EXPECT_EQ(write_data, read_data);
}

TEST_F(AttributeMultidimIO,test_init_list)
{
  attribute::Attribute a = root_.attributes.create<int>("data",{4});
  a.write({1,2,3,4});
  std::vector<int> read(4);
  a.read(read);
  EXPECT_EQ((std::vector<int>{1,2,3,4}),read);
}

TEST_F(AttributeMultidimIO, test_read_float)
{
  std::vector<float> fvec_data = {1.2, -0.23, 34.4, 5.5};
  std::vector<float> fbuffer(4);
  auto floattype = hdf5::datatype::create<float>();
  auto a = root_.attributes.create("float",
				   floattype,
				   hdf5::dataspace::Simple({4}));
  a.write(fvec_data, floattype);
  a.read(fbuffer);
  EXPECT_EQ(fbuffer, fvec_data);
  a.read(fbuffer, a.datatype());
  EXPECT_EQ(fbuffer, fvec_data);
}

