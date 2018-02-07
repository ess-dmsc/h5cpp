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
// Created on: Oct 24, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>

struct DatasetFixedStringIO : public testing::Test
{
  hdf5::file::File file;
  hdf5::node::Group root_group;
  hdf5::datatype::String string_type;
  hdf5::dataspace::Scalar scalar_space;
  hdf5::dataspace::Simple simple_space;
  hdf5::property::DatasetTransferList dtpl;

  DatasetFixedStringIO():
    file(hdf5::file::create("DatasetFixedStringIO.h5",hdf5::file::AccessFlags::TRUNCATE)),
    root_group(file.root()),
    string_type(hdf5::datatype::String::fixed(5)),
    scalar_space(),
    simple_space({2,3}),
    dtpl(hdf5::property::DatasetTransferList())
  {
    string_type.encoding(hdf5::datatype::CharacterEncoding::UTF8);
    string_type.padding(hdf5::datatype::StringPad::NULLTERM);
  }
};

using namespace hdf5;

TEST_F(DatasetFixedStringIO,scalar_auto_config)
{
  node::Dataset dset(root_group,Path("data"),string_type,scalar_space);

  std::string write_value = "hello";
  EXPECT_NO_THROW(dset.write(write_value,string_type,scalar_space,scalar_space,dtpl));
  std::string read_value;
  EXPECT_NO_THROW(dset.read(read_value,string_type,scalar_space,scalar_space,dtpl));

  EXPECT_EQ(write_value,read_value);

}

TEST_F(DatasetFixedStringIO,vector_no_auto_config)
{
  node::Dataset dset(root_group,Path("data"),string_type,simple_space);

  std::vector<std::string> write{"AAAAA","BBBBB","CCCCC","DDDDD","EEEEE","FFFFF"};
  EXPECT_NO_THROW(dset.write(write,string_type,simple_space,simple_space,dtpl));
  std::vector<std::string> read;
  EXPECT_NO_THROW(dset.read(read,string_type,simple_space,simple_space,dtpl));
  EXPECT_EQ(write,read);
}

TEST_F(DatasetFixedStringIO,single_value_read)
{
  node::Dataset dset(root_group,Path("data"),string_type,simple_space);
  std::vector<std::string> write{"AAAAA","BBBBB","CCCCC","DDDDD","EEEEE","FFFFF"};
  EXPECT_NO_THROW(dset.write(write,string_type,simple_space,simple_space,dtpl));

  auto read_type = datatype::String::fixed(10);
  read_type.padding(datatype::StringPad::SPACEPAD);
  read_type.encoding(datatype::CharacterEncoding::UTF8);
  std::string buffer;
  dset.read(buffer,read_type,dataspace::Scalar(),dataspace::Hyperslab{{0,0},{1,1}});
  EXPECT_EQ(buffer,std::string("AAAAA     "));
  dset.read(buffer,read_type,dataspace::Scalar(),dataspace::Hyperslab{{1,2},{1,1}});
  EXPECT_EQ(buffer,"FFFFF     ");

}



