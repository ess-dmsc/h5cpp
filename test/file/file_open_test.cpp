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

using namespace hdf5;
namespace fs = boost::filesystem;

class FileOpen : public testing::Test
{
  protected:
    virtual void SetUp()
    {
#if H5_VERSION_GE(1,10,0)
      property::FileCreationList fcpl;
      property::FileAccessList fapl;
      fapl.library_version_bounds(property::LibVersion::LATEST,
                                  property::LibVersion::LATEST);
      file::create("file_open.h5", file::AccessFlags::TRUNCATE,fcpl,fapl);
#else
      file::create("file_open.h5", file::AccessFlags::TRUNCATE);
#endif
    }
};


TEST_F(FileOpen, test_open_default)
{
  file::File f = file::open("file_open.h5");
  EXPECT_EQ(f.intent(),file::AccessFlags::READONLY);
}

TEST_F(FileOpen, test_open_readwrite)
{
  file::File f = file::open("file_open.h5",file::AccessFlags::READWRITE);
  EXPECT_EQ(f.intent(),file::AccessFlags::READWRITE);
}

#if H5_VERSION_GE(1,10,0)

TEST_F(FileOpen, test_open_swmr_read)
{
  file::File f = file::open("file_open.h5",file::AccessFlags::SWMR_READ);
  EXPECT_EQ(f.intent(),file::AccessFlags::SWMR_READ);
}

TEST_F(FileOpen, test_open_swmr_write)
{
  file::File f = file::open("file_open.h5",
                             file::AccessFlags::READWRITE | file::AccessFlags::SWMR_WRITE);


  EXPECT_EQ(static_cast<file::AccessFlagsBase>(f.intent()),
                    file::AccessFlags::SWMR_WRITE|file::AccessFlags::READWRITE  );

}

#endif







