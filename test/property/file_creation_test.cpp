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
// Created on: Aug 21, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/property/file_creation.hpp>

namespace pl = hdf5::property;

TEST(FileCreationList, test_default_construction)
{
  pl::FileCreationList fcpl;
  EXPECT_TRUE(fcpl.get_class() == pl::kFileCreate);
}

TEST(FileCreationList, test_user_block)
{
  pl::FileCreationList fcpl;

  EXPECT_NO_THROW(fcpl.user_block(1024));
  EXPECT_EQ(fcpl.user_block(),1024ul);

  //too small
  EXPECT_THROW(fcpl.user_block(256),std::runtime_error);
  //not a power of two
  EXPECT_THROW(fcpl.user_block(513),std::runtime_error);
}

TEST(FileCreationList, test_object_offset_size)
{
  pl::FileCreationList fcpl;
  EXPECT_EQ(fcpl.object_offset_size(),sizeof(hsize_t));

  EXPECT_NO_THROW(fcpl.object_length_size(2));
  EXPECT_EQ(fcpl.object_length_size(),2ul);

  EXPECT_NO_THROW(fcpl.object_offset_size(2));
  EXPECT_EQ(fcpl.object_offset_size(),2ul);
  EXPECT_EQ(fcpl.object_length_size(),2ul);

  EXPECT_NO_THROW(fcpl.object_offset_size(4));
  EXPECT_EQ(fcpl.object_offset_size(),4ul);
  EXPECT_EQ(fcpl.object_length_size(),2ul);

  EXPECT_NO_THROW(fcpl.object_offset_size(8));
  EXPECT_EQ(fcpl.object_offset_size(),8ul);
  EXPECT_EQ(fcpl.object_length_size(),2ul);

  EXPECT_NO_THROW(fcpl.object_offset_size(16));
  EXPECT_EQ(fcpl.object_offset_size(),16ul);
  EXPECT_EQ(fcpl.object_length_size(),2ul);

  EXPECT_THROW(fcpl.object_offset_size(15),std::runtime_error);
  EXPECT_THROW(fcpl.object_offset_size(25),std::runtime_error);

}

TEST(FileCreationList, test_object_length_size)
{
  pl::FileCreationList fcpl;
  EXPECT_EQ(fcpl.object_length_size(),sizeof(hsize_t));

  EXPECT_NO_THROW(fcpl.object_offset_size(2));
  EXPECT_EQ(fcpl.object_offset_size(),2ul);

  EXPECT_NO_THROW(fcpl.object_length_size(2));
  EXPECT_EQ(fcpl.object_length_size(),2ul);
  EXPECT_EQ(fcpl.object_offset_size(),2ul);

  EXPECT_NO_THROW(fcpl.object_length_size(4));
  EXPECT_EQ(fcpl.object_length_size(),4ul);
  EXPECT_EQ(fcpl.object_offset_size(),2ul);

  EXPECT_NO_THROW(fcpl.object_length_size(8));
  EXPECT_EQ(fcpl.object_length_size(),8ul);
  EXPECT_EQ(fcpl.object_offset_size(),2ul);

  EXPECT_NO_THROW(fcpl.object_length_size(16));
  EXPECT_EQ(fcpl.object_length_size(),16ul);
  EXPECT_EQ(fcpl.object_offset_size(),2ul);

  EXPECT_THROW(fcpl.object_length_size(15),std::runtime_error);
  EXPECT_THROW(fcpl.object_length_size(25),std::runtime_error);
}



