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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Oct 25, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>
#include "../fixture.hpp"
#include <string>
#include <vector>

using namespace hdf5;

class AttributeVariableStringIO : public testing::Test
{
  public:
    file::File file;
    node::Group root_group;
    dataspace::Scalar scalar_space;
    dataspace::Simple simple_space;
    datatype::String string_type;
    attribute::Attribute scalar_attr;
    attribute::Attribute vector_attr;

    void SetUp()
    {
      file = file::create("AttributeFixedStringIO.h5",file::AccessFlags::TRUNCATE);
      root_group = file.root();
      simple_space = dataspace::Simple{{6}};
      scalar_space = dataspace::Scalar();
      string_type = datatype::create<std::string>();

      scalar_attr = root_group.attributes.create("scalar",string_type,scalar_space);
      vector_attr = root_group.attributes.create("vector",string_type,simple_space);
    }
};

TEST_F(AttributeVariableStringIO,scalar_io)
{
  std::string write = "hello";
  std::string read;

  scalar_attr.write(write);
  scalar_attr.read(read);
  EXPECT_EQ(write,read);
}

TEST_F(AttributeVariableStringIO,scalar_io_const_char)
{
  std::string read;

  scalar_attr.write("A short notice");
  scalar_attr.read(read);
  EXPECT_EQ("A short notice",read);
}

TEST_F(AttributeVariableStringIO,vector_io)
{
  std::vector<std::string> write{"AAAAA","BBBBB","CCCCC","DDDDD",
                                 "EEEEE","FFFFF"};
  std::vector<std::string> read(write.size());


  vector_attr.write(write);
  vector_attr.read(read);
  EXPECT_EQ(write,read);

}

TEST_F(AttributeVariableStringIO, simple_read)
{

  auto a = root_group.attributes.create(
					"simple5",
					string_type, dataspace::Simple({1}));
  std::string write = "hell";
  std::string read;
  a.write(write, string_type);
  EXPECT_NO_THROW(a.read(read, a.datatype()));
  EXPECT_EQ(write, read);
  EXPECT_NO_THROW(a.read(read));
  EXPECT_EQ(write, read);
}

TEST_F(AttributeVariableStringIO, scalar_read)
{

  auto a = root_group.attributes.create("scalar5", string_type, scalar_space);
  std::string write = "hell";
  std::string read;
  a.write(write, string_type);
  EXPECT_NO_THROW(a.read(read, a.datatype()));
  EXPECT_EQ(write, read);
  EXPECT_NO_THROW(a.read(read));
  EXPECT_EQ(write, read);
}

TEST_F(AttributeVariableStringIO, simple_vector_read)
{

  auto a = root_group.attributes.create("simple20x",
      string_type, hdf5::dataspace::Simple({4}));
  std::vector<std::string> write = {"hllo", "ho1", "h", "ho33"};
  std::vector<std::string> read(4);
  a.write(write, string_type);
  EXPECT_NO_THROW(a.read(read, a.datatype()));
  EXPECT_EQ(write, read);
  EXPECT_NO_THROW(a.read(read));
  EXPECT_EQ(write, read);
}
