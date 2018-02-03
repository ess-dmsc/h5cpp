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
//   Martin Shetty <martin.shetty@esss.es>
// Created on: Aug 23, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/datatype/integer.hpp>

using namespace hdf5;

template<class T>
class Integer : public testing::Test
{
 protected:
  Integer() {}
  virtual ~Integer() {}
  T value_;
};

using testing::Types;

// The list of types we want to test.
typedef
Types<
    char, unsigned char, signed char,
    short, unsigned short,
    int, unsigned int,
    long, unsigned long,
    long long, unsigned long long>
    test_types;

TYPED_TEST_CASE(Integer, test_types);

TYPED_TEST(Integer, Exceptions)
{
  datatype::Datatype dtype;
  EXPECT_THROW((datatype::Integer(dtype)), std::runtime_error);

  auto ft = datatype::create<double>();
  EXPECT_THROW((datatype::Integer(ft)), std::runtime_error);
}

TYPED_TEST(Integer, General)
{
  auto t = datatype::create<decltype(this->value_)>();
  EXPECT_TRUE((std::is_same<decltype(t), datatype::Integer>::value));
  EXPECT_TRUE(t.get_class() == datatype::Class::INTEGER);
  EXPECT_EQ(t.size(), sizeof(this->value_));

  datatype::Datatype &generic = t;
  datatype::Integer new_type(generic);
  EXPECT_EQ(new_type.get_class(), datatype::Class::INTEGER);

  datatype::Datatype default_constructed;
  EXPECT_FALSE(default_constructed.is_valid());
  EXPECT_THROW((datatype::Integer(default_constructed)), std::runtime_error);
}

