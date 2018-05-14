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
//   Martin Shetty <martin.shetty@esss.se>
// Created on: May 14, 2018
//
#include <gtest/gtest.h>
#include <h5cpp/datatype/enum.hpp>
#include <h5cpp/datatype/factory.hpp>

using namespace hdf5;

TEST(Enum, DefaultConstruction) {
  datatype::Enum type;
  EXPECT_FALSE(type.is_valid());
  EXPECT_EQ(type.get_class(), datatype::Class::NONE);
}

TEST(Enum, Exceptions) {
  auto ft = datatype::create<double>();
  EXPECT_THROW((datatype::Enum(ft)), std::runtime_error);
  EXPECT_THROW((datatype::Enum::create(datatype::Datatype())), std::runtime_error);
}

TEST(Enum, IntConstruction) {
  auto base_type = datatype::create<int>();
  auto type = datatype::Enum::create(base_type);
  EXPECT_TRUE(type.is_valid());
  EXPECT_EQ(type.get_class(), datatype::Class::ENUM);
  EXPECT_EQ(type.number_of_values(), 0);

  ObjectHandle(static_cast<hid_t>(type)).close();
  EXPECT_THROW((type.number_of_values()), std::runtime_error);
}

TEST(Enum, IntInsert) {
  auto type = datatype::Enum::create(datatype::create<int>());

  int val1 = 1;
  type.insert("val1", val1);
  EXPECT_EQ(type.number_of_values(), 1);

  // duplicate value
  EXPECT_THROW((type.insert("val2", val1)), std::runtime_error);
}

TEST(Enum, InsertTypeMismatch) {
  auto type = datatype::Enum::create(datatype::create<int>());

  double val1 = 1;
  EXPECT_THROW((type.insert("val1", val1)), std::runtime_error);
}

TEST(Enum, GetName) {
  auto type = datatype::Enum::create(datatype::create<int>());
  int val1 = 1;
  type.insert("val1", val1);
  EXPECT_EQ(type.name(0), "val1");

  EXPECT_THROW((type.name(1)), std::runtime_error);

  ObjectHandle(static_cast<hid_t>(type)).close();
  EXPECT_THROW((type.name(0)), std::runtime_error);
}

TEST(Enum, GetValue) {
  auto type = datatype::Enum::create(datatype::create<int>());
  int val1 = 1;
  type.insert("val1", val1);

  int val2;
  type.value(0, val2);
  EXPECT_EQ(val2, val1);
  EXPECT_EQ(type.value<int>(0), val1);

  EXPECT_THROW((type.value<double>(0)), std::runtime_error);
  EXPECT_THROW((type.value<int>(1)), std::runtime_error);
}

TEST(Enum, GetValueByName) {
  auto type = datatype::Enum::create(datatype::create<int>());
  int val1 = 1;
  type.insert("val1", val1);

  int val2;
  type.value("val1", val2);
  EXPECT_EQ(val2, val1);
  EXPECT_EQ(type.value<int>("val1"), val1);

  EXPECT_THROW((type.value<double>("val1")), std::runtime_error);
  EXPECT_THROW((type.value<int>("val2")), std::runtime_error);
}

