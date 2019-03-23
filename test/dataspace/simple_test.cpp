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
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 25, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/dataspace/simple.hpp>

using namespace hdf5;

TEST(Simple, test_default_construction) {
  dataspace::Simple space;
  EXPECT_EQ(space.size(), 0);
  EXPECT_EQ(space.rank(), 0u);
  EXPECT_EQ(space.type(), dataspace::Type::SIMPLE);
  EXPECT_TRUE(space.current_dimensions().empty());
  EXPECT_TRUE(space.maximum_dimensions().empty());

  dataspace::Simple space2(ObjectHandle(H5Screate(H5S_SIMPLE)));
  EXPECT_EQ(space2.type(), dataspace::Type::SIMPLE);
}

TEST(Simple, test_exceptions) {
  dataspace::Dataspace s(ObjectHandle(H5Screate(H5S_SCALAR)));
  EXPECT_THROW((dataspace::Simple(s)), std::runtime_error);

  dataspace::Simple s2;
  ObjectHandle(static_cast<hid_t>(s2)).close();
  EXPECT_THROW(s2.rank(), std::runtime_error);
  EXPECT_THROW(s2.current_dimensions(), std::runtime_error);
  EXPECT_THROW(s2.maximum_dimensions(), std::runtime_error);
  EXPECT_THROW(s2.dimensions({1}, {1}), std::runtime_error);
}

TEST(Simple, test_construction_only_current) {
  Dimensions s = {10, 20, 30};
  dataspace::Simple space(s);
  EXPECT_EQ(space.size(), 10 * 20 * 30);
  EXPECT_EQ(space.rank(), 3u);

  Dimensions c = space.current_dimensions();
  Dimensions m = space.maximum_dimensions();
  EXPECT_EQ(c, s);
  EXPECT_EQ(c, m);
}

TEST(Simple, test_construction_current_and_max) {
  Dimensions s = {30, 20, 10}, m = {100, 200, dataspace::Simple::UNLIMITED};
  dataspace::Simple space(s, m);
  EXPECT_EQ(space.rank(), 3u);
  EXPECT_EQ(space.size(), 10 * 20 * 30);

  Dimensions c = space.current_dimensions();
  Dimensions max = space.maximum_dimensions();

  EXPECT_EQ(s, c);
  EXPECT_EQ(m, max);
}

//TODO: better name for test case
// test_setting_dimensions_changes_rank_correctly
// test_given_a_dataspace_of_rank_one_when_setting....
TEST(Simple, test_change_rank) {
  dataspace::Simple space(Dimensions{100});
  EXPECT_EQ(space.rank(), 1u);
  space.dimensions(Dimensions{2, 3}, Dimensions{2, 3});
  EXPECT_EQ(space.rank(), 2u);
}
