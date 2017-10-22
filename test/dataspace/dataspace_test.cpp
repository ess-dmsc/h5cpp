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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 22, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/dataspace/dataspace.hpp>

using namespace hdf5;
using namespace hdf5::dataspace;

TEST(Dataspace, default_construction)
{
  Dataspace s;
  EXPECT_THROW(s.size(), std::runtime_error);
  EXPECT_THROW(s.type(), std::runtime_error);
  EXPECT_FALSE(s.is_valid());
}

TEST(Dataspace, from_hid)
{
  Dataspace s(ObjectHandle(H5Screate(H5S_SCALAR)));
  EXPECT_EQ(s.size(), 1);
  EXPECT_EQ(s.type(), Type::SCALAR);
  EXPECT_TRUE(s.is_valid());
}

TEST(Dataspace, copy_construction)
{
  Dataspace s;
  const Dataspace& ss = s;
  EXPECT_THROW(Dataspace(ss).is_valid(), std::runtime_error);

  s = Dataspace(ObjectHandle(H5Screate(H5S_SCALAR)));
  Dataspace s2(s);
  EXPECT_EQ(s.type(), s2.type());
  EXPECT_NE(static_cast<hid_t>(s), static_cast<hid_t>(s2));
}

TEST(Dataspace, copy_assignment)
{
  Dataspace s, s2;
  EXPECT_THROW((s2 = s), std::runtime_error);

  s = Dataspace(ObjectHandle(H5Screate(H5S_SCALAR)));
  s2 = s;
  EXPECT_EQ(s.type(), s2.type());
  EXPECT_NE(static_cast<hid_t>(s), static_cast<hid_t>(s2));

  Dataspace s3 = s2 = s;
  EXPECT_EQ(s.type(), s3.type());
  EXPECT_NE(static_cast<hid_t>(s), static_cast<hid_t>(s3));
}


