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
// Created on: Oct 23, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/property/property_class.hpp>
#include <h5cpp/property/property_list.hpp>
#include <h5cpp/object_handle.hpp>

using namespace hdf5;
using namespace hdf5::property;

namespace pl = hdf5::property;

TEST(List, default_construction_impossible)
{
  pl::Class c;
  EXPECT_THROW(List(c).get_class(), std::runtime_error);
}

TEST(List, from_class)
{
  pl::Class c = kDatasetAccess;
  EXPECT_EQ(List(c).get_class().name(), c.name());
}


TEST(List, copy_construction)
{
//  pl::Class c;
//  List s(c);
//  const List& ss = s;
//  EXPECT_THROW(List(ss).get_class(), std::runtime_error);

  List s = List(kDatasetAccess);
  List s2(s);
  EXPECT_EQ(s.get_class().name(), s2.get_class().name());
  EXPECT_NE(static_cast<hid_t>(s), static_cast<hid_t>(s2));
}

TEST(List, copy_assignment)
{
//  List s, s2;
//  EXPECT_THROW((s2 = s), std::runtime_error);

  List s = List(kDatasetAccess);
  List s2 = s;
  EXPECT_EQ(s.get_class().name(), s2.get_class().name());
  EXPECT_NE(static_cast<hid_t>(s), static_cast<hid_t>(s2));

  List s3 = s2 = s;
  EXPECT_EQ(s.get_class().name(), s3.get_class().name());
  EXPECT_NE(static_cast<hid_t>(s), static_cast<hid_t>(s3));
}
