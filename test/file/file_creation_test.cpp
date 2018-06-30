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
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
//   Jan Kotanski <jan.kotanski@desy.de>
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
    "./test1_with_a_much_longer_file_name.h5",
    "./test1.h5",
    "./test2.h5",
    "./testclose.h5"
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
  EXPECT_THROW(f.close(), std::runtime_error);
}

TEST_F(FileCreation, test_no_truncate)
{
  file::File f = file::create(fs::path("./test1_with_a_much_longer_file_name.h5"));
  EXPECT_EQ(f.intent(),file::AccessFlags::READWRITE);
  EXPECT_EQ(f.path().string(),"./test1_with_a_much_longer_file_name.h5");
  f.close();

  //cannot create another file
  EXPECT_THROW(file::create("./test1_with_a_much_longer_file_name.h5"),std::runtime_error);
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

TEST_F(FileCreation, test_closeattr_close)
{
  auto nexus_file = file::create("testclose.h5",
				 file::AccessFlags::TRUNCATE);
  std::string hdf5_version =  "1.0.0";
  auto type = datatype::create<std::string>();
  dataspace::Scalar space;

  auto r1 = nexus_file.root();
  r1.attributes.create("HDF5_version", type, space).write(hdf5_version);

  // without this line works
  r1.close();

  nexus_file.close();

  auto file2 = hdf5::file::open("testclose.h5",
				hdf5::file::AccessFlags::READONLY);
  auto r2 = file2.root();

  auto attr = r2.attributes[0];
  attr.close();

  r2.close();
  file2.close();

  EXPECT_NO_THROW(hdf5::file::open("testclose.h5",
				   hdf5::file::AccessFlags::READWRITE));
}

TEST_F(FileCreation, test_closeattr_withoutclose_strong)
{
  hdf5::property::FileAccessList fapl;
  fapl.close_degree(hdf5::property::CloseDegree::STRONG);
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

  hdf5::property::FileAccessList fapl2;
  fapl2.close_degree(hdf5::property::CloseDegree::STRONG);
  auto file2 = hdf5::file::open("testclose.h5",
				hdf5::file::AccessFlags::READONLY, fapl2);
  auto r2 = file2.root();

  auto attr = r2.attributes[0];

  r2.close();
  file2.close();


  EXPECT_NO_THROW(hdf5::file::open("testclose.h5",
				   hdf5::file::AccessFlags::READWRITE));
}

TEST_F(FileCreation, test_closeattr_bracket)
{
  auto nexus_file = file::create("testclose.h5",
				       file::AccessFlags::TRUNCATE);
  std::string hdf5_version =  "1.0.0";
  auto type = datatype::create<std::string>();
  dataspace::Scalar space;

  auto r1 = nexus_file.root();
  r1.attributes.create("HDF5_version", type, space).write(hdf5_version);
  r1.close();
  nexus_file.close();

  auto file2 = hdf5::file::open("testclose.h5",
				hdf5::file::AccessFlags::READONLY);
  auto r2 = file2.root();

  {
    auto attr = r2.attributes[0];
  }

  r2.close();
  file2.close();

  EXPECT_NO_THROW(hdf5::file::open("testclose.h5",
				   hdf5::file::AccessFlags::READWRITE));
}


TEST_F(FileCreation, test_closeattr_bracketclose)
{
  {
    auto nexus_file = file::create("testclose.h5",
				   file::AccessFlags::TRUNCATE);
    std::string hdf5_version =  "1.0.0";
    auto type = datatype::create<std::string>();
    dataspace::Scalar space;


    auto r1 = nexus_file.root();
    r1.attributes.create("HDF5_version", type, space).write(hdf5_version);

    nexus_file.close();
  }


  auto file2 = hdf5::file::open("testclose.h5",
				hdf5::file::AccessFlags::READONLY);
  auto r2 = file2.root();

  auto attr = r2.attributes[0];
  attr.close();

  r2.close();
  file2.close();

  EXPECT_NO_THROW(hdf5::file::open("testclose.h5",
				   hdf5::file::AccessFlags::READWRITE));

}






