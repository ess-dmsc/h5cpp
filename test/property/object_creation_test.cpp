
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
// Created on: Aug 17, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/property/object_creation.hpp>
#include <h5cpp/property/property_class.hpp>

namespace pl = hdf5::property;

TEST(ObjectCreationList, default_construction)
{
  pl::ObjectCreationList ocpl;
  EXPECT_TRUE(ocpl.get_class()==pl::kObjectCreate);
}

TEST(ObjectCreationList, test_time_tracking)
{
  pl::ObjectCreationList ocpl;
  EXPECT_NO_THROW(ocpl.enable_time_tracking());
  EXPECT_TRUE(ocpl.time_tracking());

  EXPECT_NO_THROW(ocpl.disable_time_tracking());
  EXPECT_FALSE(ocpl.time_tracking());
}

TEST(ObjectCreationList, test_attribute_creation_order)
{
  pl::ObjectCreationList ocpl;

  EXPECT_NO_THROW(ocpl.attribute_creation_order(pl::CreationOrder().enable_tracked()));
  EXPECT_TRUE(ocpl.attribute_creation_order().tracked());
  EXPECT_FALSE(ocpl.attribute_creation_order().indexed());

  EXPECT_NO_THROW(ocpl.attribute_creation_order(pl::CreationOrder().enable_indexed()));
  EXPECT_TRUE(ocpl.attribute_creation_order().tracked());
  EXPECT_TRUE(ocpl.attribute_creation_order().indexed());
}

TEST(ObjectCreationList, test_attribute_storage_threshold)
{
  pl::ObjectCreationList ocpl;
  EXPECT_NO_THROW(ocpl.attribute_storage_thresholds(100,50));
  EXPECT_EQ(ocpl.attribute_storage_maximum_compact(),100ul);
  EXPECT_EQ(ocpl.attribute_storage_minimum_dense(),50ul);

  EXPECT_THROW(ocpl.attribute_storage_thresholds(50,100),
               std::runtime_error);
}



