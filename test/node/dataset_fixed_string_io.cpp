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
    string_type(hdf5::datatype::String::fixed(20)),
    scalar_space(),
    simple_space({2,3}),
    dtpl(hdf5::property::DatasetTransferList())
  {
    string_type.set_encoding(hdf5::datatype::CharacterEncoding::UTF8);
    string_type.set_padding(hdf5::datatype::StringPad::NULLTERM);
  }
};

using namespace hdf5;

TEST_F(DatasetFixedStringIO,scalar_auto_config)
{
  node::Dataset dset = root_group.create_dataset("data",string_type,scalar_space);

  std::string write_value = "hello";
  EXPECT_NO_THROW(dset.write(write_value,string_type,scalar_space,scalar_space,dtpl));

}

TEST_F(DatasetFixedStringIO,vector_no_auto_config)
{
  node::Dataset dset = root_group.create_dataset("data",string_type,simple_space);

  std::vector<std::string> write_values{"hello","world","this","is","some","stupid"};
  EXPECT_NO_THROW(dset.write(write_values,string_type,simple_space,simple_space,dtpl));
}


