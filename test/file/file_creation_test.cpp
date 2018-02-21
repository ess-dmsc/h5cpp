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
// Created on: Sep 10, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <boost/filesystem.hpp>

using namespace hdf5;
namespace fs = boost::filesystem;

class FileCreation : public testing::Test
{
  protected:
    FileCreation() {}
    virtual ~FileCreation() {}

    virtual void SetUp()
    {
      for(auto filename : files_)
        fs::remove(filename);
    }

    virtual void TearDown() {}

    static const std::vector<std::string> files_;
};

const std::vector<std::string> FileCreation::files_ = {
    "./test1.h5",
    "./test2.h5"
};


TEST_F(FileCreation, test_default)
{
  file::File f;
  EXPECT_THROW(f.intent(),std::runtime_error);
  EXPECT_THROW(f.size(),std::runtime_error);
  EXPECT_THROW(f.flush(file::Scope::GLOBAL),std::runtime_error);
  EXPECT_THROW(f.flush(file::Scope::LOCAL),std::runtime_error);
  EXPECT_THROW(f.count_open_objects(file::SearchFlags::ALL),std::runtime_error);
  EXPECT_THROW(f.root(), std::runtime_error);
  EXPECT_NO_THROW(f.close());
}

TEST_F(FileCreation, test_no_truncate)
{
  file::File f = file::create(fs::path("./test1.h5"));
  EXPECT_EQ(f.intent(),file::AccessFlags::READWRITE);
  f.close();

  //cannot create another file
  EXPECT_THROW(file::create("./test1.h5"),std::runtime_error);
}

TEST_F(FileCreation, test_truncation)
{
  file::File f = file::create("./test2.h5");
  EXPECT_EQ(f.intent(),file::AccessFlags::READWRITE);
  f.close();

  //should work
  EXPECT_NO_THROW(file::create("./test2.h5",file::AccessFlags::TRUNCATE));
}

//testing a situation where we have two individual files open
//
TEST_F(FileCreation, test_same_file_ro)
{
  file::create("test1.h5",file::AccessFlags::TRUNCATE);
  file::File f1 = file::open("test1.h5",file::AccessFlags::READONLY);
  file::File f2 = file::open("test1.h5",file::AccessFlags::READONLY);

  EXPECT_TRUE(f1.id()==f2.id());
}

#ifndef _MSC_VER
TEST_F(FileCreation, test_same_file_with_symbolic_link)
{
  file::create("test1.h5",file::AccessFlags::TRUNCATE);

  boost::filesystem::create_symlink("test1.h5", "test1_link.h5");
  file::File f1 = file::open("test1.h5",file::AccessFlags::READONLY);
  file::File f2 = file::open("test1_link.h5",file::AccessFlags::READONLY);

  EXPECT_TRUE(f1.id()==f2.id());
  boost::filesystem::remove("test1_link.h5");
}
#endif







