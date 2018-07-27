//
// (c) Copyright 2018 DESY,ESS
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
// Author: Jan Kotanski <jan,kotanski@desy.de>
// Created on: Jul 2, 2018
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

class DatasetPNIIOBoolTest : public testing::Test
{
  protected:
    file::File pniio_file;
    node::Group root_group;

    virtual void SetUp()
    {
      pniio_file = file::open("./pniio_test_boolattr.h5",file::AccessFlags::READONLY);
      root_group = pniio_file.root();
    }

};

#ifndef _MSC_VER
TEST_F(DatasetPNIIOBoolTest, test_read_simple_bool)
{
  auto dstrue = node::get_dataset(root_group,"ds_bool_scalar_true");
  bool buffer;
  dstrue.read(buffer);
  EXPECT_EQ(buffer, true);
  bool buffer2;
  auto dsfalse = node::get_dataset(root_group,"ds_bool_scalar_false");
  dsfalse.read(buffer2);
  EXPECT_EQ(buffer2, false);
}

TEST_F(DatasetPNIIOBoolTest, test_read_vector_bool)
{
  auto ds = node::get_dataset(root_group,"ds_bool_array");
  std::vector<bool> buffer(4);
  std::vector<unsigned char> buffer2(4);
  std::vector<bool> ref  = {false, true, true, false};
  std::vector<unsigned char> ref2  = {0, 1, 1, 0};
  EXPECT_EQ(ds.datatype().get_class(), datatype::Class::INTEGER);
  EXPECT_EQ(ds.datatype().size(), 1);
  // ds.read(buffer);
  //  EXPECT_EQ(buffer, ref);
  ds.read(buffer2);
  EXPECT_EQ(buffer2, ref2);
}
#endif
