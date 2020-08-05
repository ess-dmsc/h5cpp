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
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Sep 8, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/core/filesystem.hpp>
#include <fstream>

using namespace hdf5;

class IsHDF5 : public testing::Test
{
 protected:
  IsHDF5() {}
  virtual void SetUp()
  {
    std::ofstream ofile("test.txt");
    ofile << "hello world" << std::endl;
    ofile.close();

    file::create("test.h5", file::AccessFlags::TRUNCATE);
  }

  virtual void TearDown()
  {
    fs::remove("test.txt");
    fs::remove("test.h5");
  }
  virtual ~IsHDF5() {}
};

TEST_F(IsHDF5, test_hdf5_file)
{
  EXPECT_TRUE(file::is_hdf5_file("test.h5"));
}

TEST_F(IsHDF5, test_no_hdf5_file)
{
  EXPECT_FALSE(file::is_hdf5_file("test.txt"));
}

TEST_F(IsHDF5, test_failure)
{
  EXPECT_THROW(file::is_hdf5_file("nonexistent.qqq"), std::runtime_error);
}






