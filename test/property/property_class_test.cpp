
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

namespace pl = hdf5::property;

TEST(PropertyList, test_construction)
{
  pl::Class c(hdf5::ObjectHandle(H5P_ATTRIBUTE_ACCESS));

  EXPECT_THROW((pl::Class(hdf5::ObjectHandle(H5Screate(H5S_SIMPLE)))), std::runtime_error);
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

TEST(PropertyList, test_stream)
{
  std::stringstream stream;

  stream.str(std::string());
  stream << pl::kAttributeCreate;
  EXPECT_EQ(stream.str(), "AttributeClass(attribute create)");
  stream.str(std::string());
  stream << pl::kDatasetAccess;
  EXPECT_EQ(stream.str(), "AttributeClass(dataset access)");
  stream.str(std::string());
  stream << pl::kDatasetCreate;
  EXPECT_EQ(stream.str(), "AttributeClass(dataset create)");
  stream.str(std::string());
  stream << pl::kDatasetXfer;
  EXPECT_EQ(stream.str(), "AttributeClass(data transfer)");
  stream.str(std::string());
  stream << pl::kDatatypeAccess;
  EXPECT_EQ(stream.str(), "AttributeClass(datatype access)");
  stream.str(std::string());
  stream << pl::kDatatypeCreate;
  EXPECT_EQ(stream.str(), "AttributeClass(datatype create)");
  stream.str(std::string());
  stream << pl::kFileAccess;
  EXPECT_EQ(stream.str(), "AttributeClass(file access)");
  stream.str(std::string());
  stream << pl::kFileCreate;
  EXPECT_EQ(stream.str(), "AttributeClass(file create)");
  stream.str(std::string());
  stream << pl::kFileMount;
  EXPECT_EQ(stream.str(), "AttributeClass(file mount)");
  stream.str(std::string());
  stream << pl::kGroupAccess;
  EXPECT_EQ(stream.str(), "AttributeClass(group access)");
  stream.str(std::string());
  stream << pl::kGroupCreate;
  EXPECT_EQ(stream.str(), "AttributeClass(group create)");
  stream.str(std::string());
  stream << pl::kLinkAccess;
  EXPECT_EQ(stream.str(), "AttributeClass(link access)");
  stream.str(std::string());
  stream << pl::kLinkCreate;
  EXPECT_EQ(stream.str(), "AttributeClass(link create)");
  stream.str(std::string());
  stream << pl::kObjectCopy;
  EXPECT_EQ(stream.str(), "AttributeClass(object copy)");
  stream.str(std::string());
  stream << pl::kObjectCreate;
  EXPECT_EQ(stream.str(), "AttributeClass(object create)");
  stream.str(std::string());
  stream << pl::kStringCreate;
  EXPECT_EQ(stream.str(), "AttributeClass(string create)");

  stream.str(std::string());
  pl::Class cl;
  stream << cl;
  EXPECT_EQ(stream.str(), "AttributeClass()");
}

TEST(PropertyList, test_equality_operator)
{
  EXPECT_TRUE(pl::kAttributeCreate == pl::kAttributeCreate);
  EXPECT_FALSE(pl::kAttributeCreate == pl::kFileAccess);
  EXPECT_TRUE(pl::kAttributeCreate != pl::kFileAccess);
  EXPECT_FALSE(pl::kAttributeCreate != pl::kAttributeCreate);

  pl::Class p2;
  EXPECT_THROW((pl::kAttributeCreate == p2), std::runtime_error);
  EXPECT_THROW((pl::kAttributeCreate != p2), std::runtime_error);
}





