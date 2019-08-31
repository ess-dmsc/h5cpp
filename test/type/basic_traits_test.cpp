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
// Author: Eugen Wintersberger <eugen.wintersberger@gmail.com>
// Created on: Sep 01, 2019
//

#include <h5cpp/type/trait.hpp>
#include <h5cpp/hdf5.hpp>
#include <gtest/gtest.h>
#include "../h5cpp_test_helpers.hpp"
#include "../gtest_print.hpp"


using namespace hdf5;

template<typename T>
class BasicTraitsTest : public ::testing::Test { };

using test_types = ::testing::Types<
    unsigned char, char,
    unsigned short, short,
    unsigned int, int,
    unsigned long, long,
    unsigned long long, long long,
    float, double, long double>;

TYPED_TEST_CASE(BasicTraitsTest, test_types);

TYPED_TEST(BasicTraitsTest,test_create)
{
    TypeParam expected = TypeParam();
    TypeParam value = type::Trait<TypeParam>::create();
    EXPECT_EQ(expected, value);
}

TYPED_TEST(BasicTraitsTest,test_pointer)
{
    TypeParam expected = TypeParam();
    EXPECT_EQ(&expected, type::Trait<TypeParam>::pointer(expected));

    using PointerType = decltype(type::Trait<TypeParam>::pointer(expected));
    ::testing::StaticAssertTypeEq<void*, PointerType>();
}

TYPED_TEST(BasicTraitsTest, test_const_pointer)
{
  const TypeParam expected = TypeParam();
  EXPECT_EQ(&expected, type::Trait<TypeParam>::pointer(expected));

  using PointerType = decltype(type::Trait<TypeParam>::pointer(expected));
  ::testing::StaticAssertTypeEq<const void *, PointerType>();
}



