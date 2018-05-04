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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Feb 5, 2018
//
#include <gtest/gtest.h>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

class H5pyStringCompatTest : public testing::Test
{
  protected:
    file::File h5py_file;
    node::Group root_group;

    virtual void SetUp()
    {
      h5py_file = file::open("./h5py_test_data.h5",file::AccessFlags::READONLY);
      root_group = h5py_file.root();
    }

};

#ifndef _MSC_VER
TEST_F(H5pyStringCompatTest, test_read_scalar_string)
{
  node::Dataset dataset = root_group.nodes["fix_string_scalar"];
  std::string buffer;
  datatype::String memory_type = datatype::String::fixed(20);
  memory_type.padding(datatype::StringPad::SPACEPAD);
  dataspace::Scalar memory_space;
  dataset.read(buffer,memory_type,memory_space,dataset.dataspace());
  EXPECT_EQ(buffer,"hello from h5py     ");
}

TEST_F(H5pyStringCompatTest, test_read_vector_string)
{
  std::vector<std::string> buffer(6);
  std::vector<std::string> ref_data{"hello               ",
                                    "world               ",
                                    "this                ",
                                    "is                  ",
                                    "a                   ",
                                    "test                "
  };
  node::Dataset dataset = root_group.nodes["fix_string_array"];


  datatype::String memory_type = datatype::String::fixed(20);
  memory_type.padding(datatype::StringPad::SPACEPAD);
  dataspace::Simple memory_space{{2,3}};
  dataset.read(buffer,memory_type,memory_space,dataset.dataspace());
  EXPECT_EQ(buffer,ref_data);
}
#endif
