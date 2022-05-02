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
// Authors:
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 8, 2021
//

#include <gtest/gtest.h>
#include <h5cpp/file/types.hpp>

using namespace hdf5;

TEST(ImageFlags, test_output_stream)
{
  std::stringstream stream;

  stream.str(std::string());
  stream<<file::ImageFlags::ReadOnly;
  EXPECT_EQ(stream.str(), "READONLY");

  stream.str(std::string());
  stream<<file::ImageFlags::DontCopy;
  EXPECT_EQ(stream.str(), "DONT COPY");

  stream.str(std::string());
  stream<<file::ImageFlags::ReadWrite;
  EXPECT_EQ(stream.str(), "READWRITE");

  stream.str(std::string());
  stream<<file::ImageFlags::DontRelease;
  EXPECT_EQ(stream.str(), "DONT RELEASE");
  
  stream.str(std::string());
  stream<<file::ImageFlags::All;
  EXPECT_EQ(stream.str(), "ALL");

}

TEST(ImageFlags, test_or_flags) {
  EXPECT_EQ(file::ImageFlags::DontCopy | file::ImageFlags::DontRelease,
            H5LT_FILE_IMAGE_DONT_COPY | H5LT_FILE_IMAGE_DONT_RELEASE);

  EXPECT_EQ(file::ImageFlags::ReadOnly | file::ImageFlags::ReadWrite,
            H5LT_FILE_IMAGE_OPEN_RW);
  EXPECT_EQ(file::ImageFlags::All | file::ImageFlags::ReadWrite,
	    H5LT_FILE_IMAGE_ALL);
}

TEST(ImageFlags, test_or_left_three)
{
  EXPECT_EQ(file::ImageFlags::DontCopy | file::ImageFlags::DontRelease |
            file::ImageFlags::ReadWrite,
            H5LT_FILE_IMAGE_DONT_COPY | H5LT_FILE_IMAGE_DONT_RELEASE |
            H5LT_FILE_IMAGE_OPEN_RW);
  EXPECT_EQ(file::ImageFlags::DontCopy | file::ImageFlags::DontRelease |
            file::ImageFlags::ReadWrite,
            H5LT_FILE_IMAGE_ALL);
}

TEST(ImageFlags, test_and_or_comb)
{
  EXPECT_EQ((file::ImageFlags::DontCopy | file::ImageFlags::DontRelease) &
            file::ImageFlags::DontCopy,
            H5LT_FILE_IMAGE_DONT_COPY);
  EXPECT_EQ(file::ImageFlags::DontRelease &
	    (file::ImageFlags::DontCopy | file::ImageFlags::DontRelease),
            H5LT_FILE_IMAGE_DONT_RELEASE);
  EXPECT_EQ((file::ImageFlags::DontCopy | file::ImageFlags::DontRelease) &
	    (file::ImageFlags::DontCopy | file::ImageFlags::ReadWrite),
            H5LT_FILE_IMAGE_DONT_COPY);
}

TEST(ImageFlags, test_values)
{
  EXPECT_EQ(static_cast<file::ImageFlagsBase>(file::ImageFlags::ReadOnly),
                    0x0000);
  EXPECT_EQ(static_cast<file::ImageFlagsBase>(file::ImageFlags::ReadWrite),
                    H5LT_FILE_IMAGE_OPEN_RW);
  EXPECT_EQ(static_cast<file::ImageFlagsBase>(file::ImageFlags::DontCopy),
                    H5LT_FILE_IMAGE_DONT_COPY);
  EXPECT_EQ(static_cast<file::ImageFlagsBase>(file::ImageFlags::DontRelease),
                    H5LT_FILE_IMAGE_DONT_RELEASE);
  EXPECT_EQ(static_cast<file::ImageFlagsBase>(file::ImageFlags::All),
                    H5LT_FILE_IMAGE_ALL);
}


