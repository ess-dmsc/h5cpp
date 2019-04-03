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
#include <h5cpp/datatype/ebool.hpp>

using namespace hdf5;

class DatasetH5pyBoolTest : public testing::Test
{
  protected:
    file::File h5py_file;
    node::Group root_group;

    virtual void SetUp()
    {
      h5py_file = file::open("./h5py_test_boolattr.h5",file::AccessFlags::READONLY);
      root_group = h5py_file.root();
    }

};

#ifndef _MSC_VER
TEST_F(DatasetH5pyBoolTest, test_read_scalar_bool)
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

TEST_F(DatasetH5pyBoolTest, test_read_simple_bool)
{
  auto dstrue = node::get_dataset(root_group,"ds_bool_simple_true");
  bool buffer;
  dstrue.read(buffer);
  EXPECT_EQ(buffer, true);
  bool buffer2;
  auto dsfalse = node::get_dataset(root_group,"ds_bool_simple_false");
  dsfalse.read(buffer2);
  EXPECT_EQ(buffer2, false);
}

TEST_F(DatasetH5pyBoolTest, test_read_vector_bool)
{
  auto ds = node::get_dataset(root_group,"ds_bool_array");
  // missing implementation for std:vector<bool>
  // std::vector<bool> buffer(4);
  // std::vector<bool> ref  = {false, true, true, false};
  // ds.read(buffer);
  // EXPECT_EQ(buffer, ref);
  std::vector<unsigned char> buffer2(4);
  std::vector<unsigned char> ref2  = {0, 1, 1, 0};
  EXPECT_EQ(ds.datatype().get_class(), datatype::Class::ENUM);
  EXPECT_EQ(ds.datatype().size(), 1ul);
  ds.read(buffer2);
  EXPECT_EQ(buffer2, ref2);
}

TEST_F(DatasetH5pyBoolTest, test_read_scalar_ebool)
{
  auto dstrue = node::get_dataset(root_group,"ds_bool_scalar_true");
  datatype::EBool buffer;
  EXPECT_EQ(dstrue.datatype().get_class(), datatype::Class::ENUM);
  EXPECT_EQ(datatype::is_bool(datatype::Enum(dstrue.datatype())), true);
  dstrue.read(buffer);
  EXPECT_EQ(buffer, true);
  EXPECT_EQ(buffer, 1);
  EXPECT_EQ(buffer, datatype::EBool::TRUE);
  datatype::EBool buffer2;
  auto dsfalse = node::get_dataset(root_group,"ds_bool_scalar_false");
  dsfalse.read(buffer2);
  EXPECT_EQ(dsfalse.datatype().get_class(), datatype::Class::ENUM);
  EXPECT_EQ(datatype::is_bool(datatype::Enum(dsfalse.datatype())), true);
  EXPECT_EQ(buffer2, false);
  EXPECT_EQ(buffer2, 0);
  EXPECT_EQ(buffer2, datatype::EBool::FALSE);
}

TEST_F(DatasetH5pyBoolTest, test_read_simple_ebool)
{
  auto dstrue = node::get_dataset(root_group,"ds_bool_simple_true");
  datatype::EBool buffer;
  EXPECT_EQ(dstrue.datatype().get_class(), datatype::Class::ENUM);
  EXPECT_EQ(datatype::is_bool(datatype::Enum(dstrue.datatype())), true);
  dstrue.read(buffer);
  EXPECT_EQ(buffer, true);
  EXPECT_EQ(buffer, 1);
  EXPECT_EQ(buffer, datatype::EBool::TRUE);
  datatype::EBool buffer2;
  auto dsfalse = node::get_dataset(root_group,"ds_bool_simple_false");
  dsfalse.read(buffer2);
  EXPECT_EQ(dsfalse.datatype().get_class(), datatype::Class::ENUM);
  EXPECT_EQ(datatype::is_bool(datatype::Enum(dsfalse.datatype())), true);
  EXPECT_EQ(buffer2, false);
  EXPECT_EQ(buffer2, 0);
  EXPECT_EQ(buffer2, datatype::EBool::FALSE);
}

TEST_F(DatasetH5pyBoolTest, test_read_vector_ebool)
{
  auto ds = node::get_dataset(root_group,"ds_bool_array");
  EXPECT_EQ(ds.datatype().get_class(), datatype::Class::ENUM);
  EXPECT_EQ(datatype::is_bool(datatype::Enum(ds.datatype())), true);
  std::vector<datatype::EBool> buffer(4);
  std::vector<datatype::EBool> eref  = {datatype::EBool::FALSE,
					datatype::EBool::TRUE,
				        datatype::EBool::TRUE,
				        datatype::EBool::FALSE};
  EXPECT_EQ(ds.datatype().get_class(), datatype::Class::ENUM);
  EXPECT_EQ(ds.datatype().size(), 1ul);
  ds.read(buffer);
  EXPECT_EQ(buffer, eref);
}
#endif
