//
// (c) Copyright 2019 Eugen Wintersberger <eugen.wintersberger@gmail.com>
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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Sep 1, 2019
//

#include <h5cpp/hdf5.hpp>
#include <gtest/gtest.h>

using namespace hdf5;

template<typename T>
class IntegerMemoryAdapterTest : public ::testing::Test { };

using test_types = ::testing::Types<
    unsigned char, char,
    unsigned short, short,
    unsigned int, int,
    unsigned long, long,
    unsigned long long, long long>;

TYPED_TEST_CASE(IntegerMemoryAdapterTest, test_types);

TYPED_TEST(IntegerMemoryAdapterTest, test_construction_from_none_const)
{
  TypeParam value = TypeParam();
  auto adapter = memory::make_adapter(value);
  ::testing::StaticAssertTypeEq<memory::MemoryAdapter<TypeParam>,
                                decltype(adapter)>();
  ::testing::StaticAssertTypeEq<dataspace::Scalar,
                                typename decltype(adapter)::DataspaceType>();
  ::testing::StaticAssertTypeEq<datatype::Integer,
                                typename decltype(adapter)::DatatypeType>();

  ::testing::StaticAssertTypeEq<void*, decltype(adapter.pointer())>();
  ASSERT_EQ(&value, adapter.pointer());
  ASSERT_EQ(value, decltype(adapter)::create());

  auto space = adapter.dataspace();
  auto type = adapter.datatype();
  ASSERT_EQ(sizeof(TypeParam), type.size());
  ::testing::StaticAssertTypeEq<datatype::Integer, decltype(type)>();
  ::testing::StaticAssertTypeEq<dataspace::Scalar, decltype(space)>();
}

TYPED_TEST(IntegerMemoryAdapterTest, test_construction_from_const)
{
  const TypeParam value = TypeParam();
  auto adapter = memory::make_adapter(value);
  ::testing::StaticAssertTypeEq<memory::MemoryAdapter<const TypeParam>,
                                decltype(adapter)>();
  ::testing::StaticAssertTypeEq<dataspace::Scalar,
                                typename decltype(adapter)::DataspaceType>();
  ::testing::StaticAssertTypeEq<datatype::Integer,
                                typename decltype(adapter)::DatatypeType>();
  ::testing::StaticAssertTypeEq<const void*, decltype(adapter.pointer())>();

  ASSERT_EQ(&value, adapter.pointer());
  ASSERT_EQ(value, decltype(adapter)::create());

  auto space = adapter.dataspace();
  auto type = adapter.datatype();
  ASSERT_EQ(sizeof(TypeParam), type.size());
}
