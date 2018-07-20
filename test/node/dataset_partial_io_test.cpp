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
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Jan Kotanski <jan.kotanski@desy.de>
//
// Created on: Oct 11, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>
#include <h5cpp/dataspace/points.hpp>
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

TEST_F(PartialIO, test_read_write_hyperslab)
{
  dataspace::Simple space {{0}, {dataspace::Simple::UNLIMITED}};
  auto type = datatype::create<int>();
  int write_value = 0,
      read_value = 0;
  dcpl.chunk({1024});

  node::Dataset dset(root_, Path("data"), type, space, lcpl, dcpl);

  dataspace::Hyperslab slab {{0},
                             {1},
                             {1},
                             {1}};

  for (size_t index = 0; index < 100; index++)
  {
    dset.extent(0, 1);
    slab.offset(0, index);
    dset.write(write_value, slab);
    dset.read(read_value, slab);
    EXPECT_EQ(write_value, read_value);
  }
}

TEST_F(PartialIO, test_read_write_points)
{
  dataspace::Simple space {{10}};
  auto type = datatype::create<int>();

  node::Dataset dset(root_, Path("data"), type, space);

  std::vector<int> write {6, 7, 8, 9, 10};
  dset.write(write,
             dataspace::Points({{1},
                                {2},
                                {3},
                                {4},
                                {5}}));

  std::vector<int> read(3);
  dset.read(read,
            dataspace::Points({{1},
                               {3},
                               {5}}));

  EXPECT_EQ(read, std::vector<int>({6, 8, 10}));
}

TEST_F(PartialIO, test_read_write_empty_int)
{
  dataspace::Simple space {{0}, {dataspace::Simple::UNLIMITED}};
  auto type = datatype::create<int>();
  std::vector<int> read_value;
  std::vector<int> write_value;
  dcpl.chunk({1});

  node::Dataset dset(root_, Path("data"), type, space, lcpl, dcpl);

  EXPECT_NO_THROW(dset.read(read_value));
  EXPECT_EQ(write_value, read_value);
}

TEST_F(PartialIO, test_read_write_empty_var_string)
{
  dataspace::Simple space {{0}, {dataspace::Simple::UNLIMITED}};
  auto type = datatype::create<std::string>();
  std::vector<std::string> read_value;
  std::vector<std::string> write_value;
  dcpl.chunk({1});

  node::Dataset dset(root_, Path("data"), type, space, lcpl, dcpl);

  EXPECT_NO_THROW(dset.read(read_value));
  EXPECT_EQ(write_value, read_value);
}

TEST_F(PartialIO, test_read_write_empty_fix_string)
{
  dataspace::Simple space {{0}, {dataspace::Simple::UNLIMITED}};
  auto type = hdf5::datatype::String::fixed(5);
  std::vector<std::string> read_value;
  std::vector<std::string> write_value;
  dcpl.chunk({1});

  node::Dataset dset(root_, Path("data"), type, space, lcpl, dcpl);

  EXPECT_NO_THROW(dset.read(read_value));
  EXPECT_EQ(write_value, read_value);
}

TEST_F(PartialIO, test_read_write_empty_double)
{
  dataspace::Simple space {{0}, {dataspace::Simple::UNLIMITED}};
  auto type = datatype::create<double>();
  std::vector<double> read_value;
  std::vector<double> write_value;
  dcpl.chunk({1});

  node::Dataset dset(root_, Path("data"), type, space, lcpl, dcpl);

  EXPECT_NO_THROW(dset.read(read_value));
  EXPECT_EQ(write_value, read_value);
}
