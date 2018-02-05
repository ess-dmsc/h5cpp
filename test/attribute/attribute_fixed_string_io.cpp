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
#include "../fixture.hpp"
#include <string>
#include <vector>

using namespace hdf5;

class AttributeFixedStringIO : public testing::Test
{
  public:
    file::File file;
    node::Group root_group;
    dataspace::Scalar scalar_space;
    dataspace::Simple simple_space;
    datatype::String string_type;

    void SetUp()
    {
      file = file::create("AttributeFixedStringIO.h5",file::AccessFlags::TRUNCATE);
      root_group = file.root();
      simple_space = dataspace::Simple{{2,3}};
      scalar_space = dataspace::Scalar();
      string_type = datatype::String::fixed(5);
      string_type.encoding(datatype::CharacterEncoding::UTF8);
      string_type.padding(datatype::StringPad::NULLTERM);
    }
};

TEST_F(AttributeFixedStringIO,scalar_io)
{
  std::string write = "hello";
  std::string read;

  EXPECT_TRUE(root_group.is_valid());
  attribute::Attribute a = root_group.attributes.create("strattr",string_type,scalar_space);
  a.write(write,string_type);
  a.read(read,string_type);
  EXPECT_EQ(write,read);
}

TEST_F(AttributeFixedStringIO,vector_io)
{
  std::vector<std::string> write{"AAAAA","BBBBB","CCCCC","DDDDD",
                                 "EEEEE","FFFFF"};
  std::vector<std::string> read(write.size());

  attribute::Attribute a = root_group.attributes.create("strattr",string_type,simple_space);
  a.write(write,string_type);
  a.read(read,string_type);
  EXPECT_EQ(write,read);

}
