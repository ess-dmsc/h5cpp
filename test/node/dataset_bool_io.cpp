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

struct DatasetBoolIO : public testing::Test
{
  hdf5::file::File file;
  hdf5::node::Group root_group;
  hdf5::dataspace::Scalar space;


  DatasetBoolIO():
    file(hdf5::file::create("DatasetBoolIO.h5",hdf5::file::AccessFlags::TRUNCATE)),
    root_group(file.root()),
    space()
  {
  }
};

using namespace hdf5;

TEST_F(DatasetBoolIO,scalar_io)
{
  auto type = hdf5::datatype::create<bool>();
  node::Dataset dset(root_group,Path("data"),type,space);

  bool write = true,
       read  = false;
  EXPECT_NO_THROW(dset.write(write));
  EXPECT_NO_THROW(dset.read(read));

  EXPECT_EQ(write,read);

}



