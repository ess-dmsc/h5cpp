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
// Authors:
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Jul 06, 2018
//

#include <gtest/gtest.h>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/core/filesystem.hpp>
#include <h5cpp/hdf5.hpp>

using namespace hdf5;

class FileClose : public testing::Test
{
  protected:
    FileClose() {}
    virtual ~FileClose() {}

    virtual void SetUp()
    {
      for(auto filename : files_)
        fs::remove(filename);
      hdf5::property::FileAccessList fapl;
      hdf5::property::FileCreationList fcpl;
      auto nexus_file = file::create("testclose.h5",
				     file::AccessFlags::TRUNCATE, fcpl, fapl);
      std::string hdf5_version =  "1.0.0";
      auto type = datatype::create<std::string>();
      dataspace::Scalar space;

      auto r1 = nexus_file.root();
      r1.attributes.create("HDF5_version", type, space).write(hdf5_version);

      r1.close();
      nexus_file.close();
    }

    virtual void TearDown() {}

    static const std::vector<std::string> files_;
};

const std::vector<std::string> FileClose::files_ = {
    "./testclose.h5"
};

TEST_F(FileClose, test_strong_withopen_root_attr)
{

  hdf5::property::FileAccessList fapl2;
  fapl2.close_degree(hdf5::property::CloseDegree::STRONG);
  EXPECT_EQ(fapl2.close_degree(), hdf5::property::CloseDegree::STRONG);
  auto file = hdf5::file::open("testclose.h5",
				hdf5::file::AccessFlags::READONLY, fapl2);
  auto root_group = file.root();

  auto attr = root_group.attributes[0];
  EXPECT_EQ(file.count_open_objects(file::SearchFlags::ALL), 3u);

  // with CloseDegree::STRONG it closes also root_group and attr
  EXPECT_NO_THROW(file.close());


  // everything is close so file can be reopen in a different mode, i.e. READWRITE
  EXPECT_NO_THROW(hdf5::file::open("testclose.h5",
				   hdf5::file::AccessFlags::READWRITE));
}

TEST_F(FileClose, test_strong_withopen_attr)
{

  hdf5::property::FileAccessList fapl2;
  fapl2.close_degree(hdf5::property::CloseDegree::STRONG);
  EXPECT_EQ(fapl2.close_degree(), hdf5::property::CloseDegree::STRONG);
  auto file = hdf5::file::open("testclose.h5",
				hdf5::file::AccessFlags::READONLY, fapl2);
  auto root_group = file.root();

  auto attr = root_group.attributes[0];
  root_group.close();

  // with CloseDegree::STRONG it closes also attr
  EXPECT_NO_THROW(file.close());


  // everything is close so file can be reopen in a different mode, i.e. READWRITE
  EXPECT_NO_THROW(hdf5::file::open("testclose.h5",
				   hdf5::file::AccessFlags::READWRITE));
}

TEST_F(FileClose, test_strong_withopen_root)
{

  hdf5::property::FileAccessList fapl2;
  fapl2.close_degree(hdf5::property::CloseDegree::STRONG);
  EXPECT_EQ(fapl2.close_degree(), hdf5::property::CloseDegree::STRONG);
  auto file = hdf5::file::open("testclose.h5",
				hdf5::file::AccessFlags::READONLY, fapl2);
  auto root_group = file.root();

  // with CloseDegree::STRONG it closes also attr
  file.close();

  // everything is close so file can be reopen in a different mode, i.e. READWRITE
  EXPECT_NO_THROW(hdf5::file::open("testclose.h5",
				   hdf5::file::AccessFlags::READWRITE));
}

TEST_F(FileClose, test_withopen_attr_root)
{

  hdf5::property::FileAccessList fapl2;
  EXPECT_EQ(fapl2.close_degree(), hdf5::property::CloseDegree::DEFAULT);
  auto file = hdf5::file::open("testclose.h5",
				hdf5::file::AccessFlags::READONLY, fapl2);
  auto root_group = file.root();

  auto attr = root_group.attributes[0];
  EXPECT_EQ(file.count_open_objects(file::SearchFlags::ALL), 3ul);

  // without CloseDegree::STRONG root_group and attr are still open
  EXPECT_NO_THROW(file.close());


  // file cannot be reopen in a different mode, i.e. READWRITE
  EXPECT_THROW(hdf5::file::open("testclose.h5",
				hdf5::file::AccessFlags::READWRITE),
	       std::runtime_error);
}

TEST_F(FileClose, test_withopen_attr)
{

  hdf5::property::FileAccessList fapl2;
  EXPECT_EQ(fapl2.close_degree(), hdf5::property::CloseDegree::DEFAULT);
  auto file = hdf5::file::open("testclose.h5",
				hdf5::file::AccessFlags::READONLY, fapl2);
  auto root_group = file.root();

  auto attr = root_group.attributes[0];
  root_group.close();

  EXPECT_EQ(file.count_open_objects(file::SearchFlags::ALL), 2ul);

  // without CloseDegree::STRONG root_group and attr are still open
  EXPECT_NO_THROW(file.close());


  // file cannot be reopen in a different mode, i.e. READWRITE
  EXPECT_THROW(hdf5::file::open("testclose.h5",
				hdf5::file::AccessFlags::READWRITE),
	       std::runtime_error);
}

TEST_F(FileClose, test_withopen_root)
{

  hdf5::property::FileAccessList fapl2;
  EXPECT_EQ(fapl2.close_degree(), hdf5::property::CloseDegree::DEFAULT);
  auto file = hdf5::file::open("testclose.h5",
				hdf5::file::AccessFlags::READONLY, fapl2);
  auto root_group = file.root();

  // without CloseDegree::STRONG root_group is still open
  EXPECT_NO_THROW(file.close());


  // file cannot be reopen in a different mode, i.e. READWRITE
  EXPECT_THROW(hdf5::file::open("testclose.h5",
				hdf5::file::AccessFlags::READWRITE),
	       std::runtime_error);
}







