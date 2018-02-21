
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
// Created on: Aug 17, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/property/creation_order.hpp>

namespace pl = hdf5::property;

TEST(LinkCreationOrder, test_default_construction) {
  pl::CreationOrder order;
  EXPECT_EQ(order, 0x0000ul);
}

TEST(LinkCreationOrder, test_conversion_construction) {
  pl::CreationOrder o1(H5P_CRT_ORDER_TRACKED);
  EXPECT_TRUE(o1.tracked());
  EXPECT_FALSE(o1.indexed());

  o1 = pl::CreationOrder(H5P_CRT_ORDER_TRACKED | H5P_CRT_ORDER_INDEXED);
  EXPECT_TRUE(o1.tracked());
  EXPECT_TRUE(o1.indexed());
}

TEST(LinkCreationOrder, test_set_tracked) {
  pl::CreationOrder o;
  o.enable_tracked();
  EXPECT_TRUE(o.tracked());
  EXPECT_FALSE(o.indexed());

  o.disable_tracked();
  EXPECT_FALSE(o.tracked());
  EXPECT_FALSE(o.indexed());
}

TEST(LinkCreationOrder, test_set_indexed) {
  pl::CreationOrder o;
  o.enable_indexed();
  EXPECT_TRUE(o.tracked());
  EXPECT_TRUE(o.indexed());

  o.disable_indexed();
  EXPECT_TRUE(o.tracked());
  EXPECT_FALSE(o.indexed());
}
