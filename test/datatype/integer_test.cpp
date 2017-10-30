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
// Created on: Aug 23, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/datatype/integer.hpp>

namespace type_ns = hdf5::datatype;

template <class T>
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
char,unsigned char,signed char,
short,unsigned short,
int, unsigned int,
long, unsigned long,
long long, unsigned long long>
test_types;

TYPED_TEST_CASE(Integer, test_types);

TYPED_TEST(Integer, General)
{
  auto t = type_ns::create<decltype(this->value_)>();
  EXPECT_TRUE((std::is_same<decltype(t),type_ns::Integer>::value));
  EXPECT_TRUE(t.get_class()==type_ns::Class::INTEGER);
  EXPECT_EQ(t.size(),sizeof(this->value_));

  type_ns::Datatype &generic = t;
  type_ns::Integer new_type(generic);
  EXPECT_EQ(new_type.get_class(),type_ns::Class::INTEGER);
  auto invalidDT = type_ns::Datatype();
  EXPECT_THROW(type_ns::Integer(invalidDT),std::runtime_error);
}

