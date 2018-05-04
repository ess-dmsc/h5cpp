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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: May 4, 2018
//

#include <gtest/gtest.h>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>

using namespace hdf5;
namespace fs = boost::filesystem;

class File : public testing::Test
{
 protected:
  virtual void SetUp()
  {
#if H5_VERSION_GE(1, 10, 0)
    property::FileCreationList fcpl;
    property::FileAccessList fapl;
    fapl.library_version_bounds(property::LibVersion::LATEST,
                                property::LibVersion::LATEST);
    file::create("file_open.h5", file::AccessFlags::TRUNCATE, fcpl, fapl);
#else
    file::create("file_open.h5", file::AccessFlags::TRUNCATE);
#endif
  }
};

TEST_F(File, is_valid)
{
  file::File f = file::open("file_open.h5", file::AccessFlags::READWRITE);
  EXPECT_TRUE(f.is_valid());
}

TEST_F(File, close)
{
  file::File f = file::open("file_open.h5", file::AccessFlags::READWRITE);
  f.close();
  EXPECT_FALSE(f.is_valid());
}

TEST_F(File, intent)
{
  file::File f = file::open("file_open.h5", file::AccessFlags::READWRITE);
  EXPECT_EQ(f.intent(), file::AccessFlags::READWRITE);

  f.close();
  EXPECT_THROW(f.intent(), std::runtime_error);
}

TEST_F(File, size)
{
  file::File f = file::open("file_open.h5", file::AccessFlags::READWRITE);
  EXPECT_GE(f.size(), 0);

  f.close();
  EXPECT_THROW(f.size(), std::runtime_error);
}

TEST_F(File, id)
{
  file::File f = file::open("file_open.h5", file::AccessFlags::READWRITE);
  EXPECT_EQ(f.id().file_name(), "file_open.h5");

  f.close();
  EXPECT_THROW(f.id(), std::runtime_error);
}

TEST_F(File, path)
{
  file::File f = file::open("file_open.h5", file::AccessFlags::READWRITE);
  EXPECT_EQ(f.path().string(), "file_open.h5");

  f.close();
  EXPECT_THROW(f.path(), std::runtime_error);
}

TEST_F(File, root)
{
  file::File f = file::open("file_open.h5", file::AccessFlags::READWRITE);
  EXPECT_EQ(f.root().link().path(), "/");

  f.close();
  EXPECT_THROW(f.root(), std::runtime_error);
}

TEST_F(File, count_open_objects)
{
  file::File f = file::open("file_open.h5", file::AccessFlags::READWRITE);
  auto r = f.root();
  EXPECT_EQ(f.count_open_objects(file::SearchFlags::GROUP), 1);

  f.close();
  EXPECT_THROW(f.count_open_objects(file::SearchFlags::ALL), std::runtime_error);
}

TEST_F(File, flush)
{
  file::File f = file::open("file_open.h5", file::AccessFlags::READWRITE);
  EXPECT_NO_THROW(f.flush(file::Scope::GLOBAL));

  f.close();
  EXPECT_THROW(f.flush(file::Scope::GLOBAL), std::runtime_error);
}
