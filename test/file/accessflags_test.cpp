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
// Created on: Sep 8, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/file/types.hpp>

using namespace hdf5;

TEST(AccessFlags, test_output_stream)
{
  std::stringstream stream;

  stream.str(std::string());
  stream<<file::AccessFlags::EXCLUSIVE;
  EXPECT_EQ(stream.str(), "EXCLUSIVE");

  stream.str(std::string());
  stream<<file::AccessFlags::READONLY;
  EXPECT_EQ(stream.str(), "READONLY");

  stream.str(std::string());
  stream<<file::AccessFlags::READWRITE;
  EXPECT_EQ(stream.str(), "READWRITE");

  stream.str(std::string());
  stream<<file::AccessFlags::TRUNCATE;
  EXPECT_EQ(stream.str(), "TRUNCATE");
#if H5_VERSION_GE(1,10,0)
  stream.str(std::string());
  stream<<file::AccessFlags::SWMR_WRITE;
  EXPECT_EQ(stream.str(), "SWMR WRITE");

  stream.str(std::string());
  stream<<file::AccessFlags::SWMR_READ;
  EXPECT_EQ(stream.str(), "SWMR READ");
#endif
}

TEST(AccessFlags, test_values)
{
  EXPECT_EQ(static_cast<file::AccessFlagsBase>(file::AccessFlags::EXCLUSIVE),
                    H5F_ACC_EXCL);
  EXPECT_EQ(static_cast<file::AccessFlagsBase>(file::AccessFlags::READONLY),
                    H5F_ACC_RDONLY);
  EXPECT_EQ(static_cast<file::AccessFlagsBase>(file::AccessFlags::READWRITE),
                    H5F_ACC_RDWR);
  EXPECT_EQ(static_cast<file::AccessFlagsBase>(file::AccessFlags::TRUNCATE),
                    H5F_ACC_TRUNC);
#if H5_VERSION_GE(1,10,0)
  EXPECT_EQ(static_cast<file::AccessFlagsBase>(file::AccessFlags::SWMR_WRITE),
                    H5F_ACC_SWMR_WRITE);
  EXPECT_EQ(static_cast<file::AccessFlagsBase>(file::AccessFlags::SWMR_READ),
                    H5F_ACC_SWMR_READ);

#endif
}


