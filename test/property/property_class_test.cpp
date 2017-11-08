
//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// h5cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// h5cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with h5cpp.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Eugen Wintersberger <eugen.wintersberger@desy.de>
// Created on: Aug 16, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/property/property_class.hpp>
#include <h5cpp/object_handle.hpp>

namespace pl = hdf5::property;

TEST(PropertyList, test_construction)
{
  pl::Class c(hdf5::ObjectHandle(H5P_ATTRIBUTE_ACCESS));
}

TEST(PropertyList, test_predefined_classes)
{
  EXPECT_EQ(pl::kAttributeCreate.name(),"attribute create");
  EXPECT_EQ(pl::kDatasetAccess.name(),"dataset access");
  EXPECT_EQ(pl::kDatasetCreate.name(),"dataset create");
  EXPECT_EQ(pl::kDatasetXfer.name(),"data transfer");
  EXPECT_EQ(pl::kDatatypeAccess.name(),"datatype access");
  EXPECT_EQ(pl::kDatatypeCreate.name(),"datatype create");
  EXPECT_EQ(pl::kFileAccess.name(),"file access");
  EXPECT_EQ(pl::kFileCreate.name(),"file create");
  EXPECT_EQ(pl::kFileMount.name(),"file mount");
  EXPECT_EQ(pl::kGroupAccess.name(),"group access");
  EXPECT_EQ(pl::kGroupCreate.name(),"group create");
  EXPECT_EQ(pl::kLinkAccess.name(),"link access");
  EXPECT_EQ(pl::kLinkCreate.name(),"link create");
  EXPECT_EQ(pl::kObjectCopy.name(),"object copy");
  EXPECT_EQ(pl::kObjectCreate.name(),"object create");
  EXPECT_EQ(pl::kStringCreate.name(),"string create");
}

TEST(PropertyList, test_equality_operator)
{
  EXPECT_TRUE(pl::kAttributeCreate == pl::kAttributeCreate);
  EXPECT_TRUE(pl::kAttributeCreate != pl::kFileAccess);
}





