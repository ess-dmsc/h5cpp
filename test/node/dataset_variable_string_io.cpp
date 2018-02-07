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
// Created on: Oct 25, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>

struct DatasetVariableStringIO : public testing::Test
{
  hdf5::file::File file;
  hdf5::node::Group root_group;
  hdf5::datatype::String string_type;
  hdf5::dataspace::Scalar scalar_space;
  hdf5::dataspace::Simple simple_space;
  hdf5::property::DatasetTransferList dtpl;
  hdf5::node::Dataset scalar_dataset;
  hdf5::node::Dataset vector_dataset;

  DatasetVariableStringIO():
    file(hdf5::file::create("DatasetVariableStringIO.h5",hdf5::file::AccessFlags::TRUNCATE)),
    root_group(file.root()),
    string_type(hdf5::datatype::create<std::string>()),
    scalar_space(),
    simple_space({7}),
    dtpl(hdf5::property::DatasetTransferList()),
    scalar_dataset(root_group,hdf5::Path("scalar"),string_type,scalar_space),
    vector_dataset(root_group,hdf5::Path("vector"),string_type,simple_space)
  {
  }
};

using namespace hdf5;

TEST_F(DatasetVariableStringIO,scalar_io)
{
  std::string write_value = "hello";
  EXPECT_NO_THROW(scalar_dataset.write(write_value));
  std::string read_value;
  EXPECT_NO_THROW(scalar_dataset.read(read_value));

  EXPECT_EQ(write_value,read_value);
}

TEST_F(DatasetVariableStringIO,scalar_const_char_ptr_io)
{
  EXPECT_NO_THROW(scalar_dataset.write("this is a test"));
  std::string read_value;
  EXPECT_NO_THROW(scalar_dataset.read(read_value));

  EXPECT_EQ("this is a test",read_value);
}

TEST_F(DatasetVariableStringIO,vector_io)
{
  using str_vector = std::vector<std::string>;
  str_vector write{"hello","world","this","is","an","arbitrary","text"};
  str_vector read(write.size());

  EXPECT_NO_THROW(vector_dataset.write(write));
  EXPECT_NO_THROW(vector_dataset.read(read));

  EXPECT_EQ(write,read);
}

TEST_F(DatasetVariableStringIO,read_single_values_from_vector)
{
  using str_vector = std::vector<std::string>;
  str_vector write{"hello","world","this","is","an","arbitrary","text"};
  EXPECT_NO_THROW(vector_dataset.write(write));

  std::string buffer;
  vector_dataset.read(buffer,dataspace::Hyperslab{{0},{1}});
  EXPECT_EQ(buffer,"hello");
  vector_dataset.read(buffer,dataspace::Hyperslab{{1},{1}});
  EXPECT_EQ(buffer,"world");
  vector_dataset.read(buffer,dataspace::Hyperslab{{6},{1}});
  EXPECT_EQ(buffer,"text");
}



