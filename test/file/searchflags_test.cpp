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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Sep 8, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/file/types.hpp>

using namespace hdf5;

TEST(SearchFlags, test_output_stream)
{
  std::stringstream stream;

  stream.str(std::string());
  stream<<file::SearchFlags::ALL;
  EXPECT_EQ(stream.str(), "ALL");

  stream.str(std::string());
  stream<<file::SearchFlags::ATTRIBUTE;
  EXPECT_EQ(stream.str(), "ATTRIBUTE");

  stream.str(std::string());
  stream<<file::SearchFlags::DATASET;
  EXPECT_EQ(stream.str(), "DATASET");

  stream.str(std::string());
  stream<<file::SearchFlags::DATATYPE;
  EXPECT_EQ(stream.str(), "DATATYPE");

  stream.str(std::string());
  stream<<file::SearchFlags::FILE;
  EXPECT_EQ(stream.str(), "FILE");

  stream.str(std::string());
  stream<<file::SearchFlags::GROUP;
  EXPECT_EQ(stream.str(), "GROUP");

  stream.str(std::string());
  stream<<file::SearchFlags::LOCAL;
  EXPECT_EQ(stream.str(), "LOCAL");
}

TEST(SearchFlags, test_or_all_flags)
{
  EXPECT_EQ(file::SearchFlags::ATTRIBUTE | file::SearchFlags::DATASET,
            H5F_OBJ_ATTR | H5F_OBJ_DATASET);

  EXPECT_EQ(file::SearchFlags::DATASET | file::SearchFlags::GROUP,
            H5F_OBJ_DATASET | H5F_OBJ_GROUP);
}

TEST(SearchFlags, test_or_left_three)
{
  EXPECT_EQ(file::SearchFlags::ATTRIBUTE | file::SearchFlags::DATASET |
            file::SearchFlags::DATATYPE,
            H5F_OBJ_ATTR | H5F_OBJ_DATASET | H5F_OBJ_DATATYPE);
}

TEST(SearchFlags, test_and_or_comb)
{
  EXPECT_EQ((file::SearchFlags::DATATYPE | file::SearchFlags::DATASET) &
            file::SearchFlags::DATATYPE,
            H5F_OBJ_DATATYPE);
  EXPECT_EQ(file::SearchFlags::ATTRIBUTE &
	    (file::SearchFlags::ATTRIBUTE | file::SearchFlags::DATASET),
            H5F_OBJ_ATTR);
  EXPECT_EQ((file::SearchFlags::DATATYPE | file::SearchFlags::DATASET) &
	    (file::SearchFlags::ATTRIBUTE | file::SearchFlags::DATASET),
            H5F_OBJ_DATASET);
}

TEST(SearchFlags, test_values)
{
  EXPECT_EQ(static_cast<file::SearchFlagsBase>(file::SearchFlags::ALL),
            H5F_OBJ_ALL);
  EXPECT_EQ(static_cast<file::SearchFlagsBase>(file::SearchFlags::ATTRIBUTE),
            H5F_OBJ_ATTR);
  EXPECT_EQ(static_cast<file::SearchFlagsBase>(file::SearchFlags::DATASET),
            H5F_OBJ_DATASET);
  EXPECT_EQ(static_cast<file::SearchFlagsBase>(file::SearchFlags::DATATYPE),
            H5F_OBJ_DATATYPE);
  EXPECT_EQ(static_cast<file::SearchFlagsBase>(file::SearchFlags::FILE),
            H5F_OBJ_FILE);
  EXPECT_EQ(static_cast<file::SearchFlagsBase>(file::SearchFlags::GROUP),
            H5F_OBJ_GROUP);
  EXPECT_EQ(static_cast<file::SearchFlagsBase>(file::SearchFlags::LOCAL),
            H5F_OBJ_LOCAL);
}


