//
// (c) Copyright 2019 Eugen Wintersberger  <eugen.wintersberger@gmail.com>
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
class VectorTypeTraitTest : public ::testing::Test
{
  protected:
    dataspace::Simple space;

    static const constexpr size_t N1 = 10;
    static const constexpr size_t N2 = 20;
    static const constexpr size_t N = N1*N2;

    VectorTypeTraitTest():
      space({N1, N2})
    {}
};

using test_types = ::testing::Types<
    std::vector<unsigned char>, std::vector<char>,
    std::vector<unsigned short>, std::vector<short>,
    std::vector<unsigned int>, std::vector<int>,
    std::vector<unsigned long>, std::vector<long>,
    std::vector<unsigned long long>, std::vector<long long>,
    std::vector<float>, std::vector<double>, std::vector<long double>>;

TYPED_TEST_CASE(VectorTypeTraitTest, test_types);

TYPED_TEST(VectorTypeTraitTest,test_create)
{
    auto expected = TypeParam(this->N);
    auto value = type::Trait<TypeParam>::create(
        datatype::Trait<TypeParam>::create(), this->space);
    EXPECT_EQ(expected.size(), value.size());
}

TYPED_TEST(VectorTypeTraitTest,test_pointer)
{
    auto expected = TypeParam(this->N);
    EXPECT_EQ(expected.data(), type::Trait<TypeParam>::pointer(expected));

    using PointerType = decltype(type::Trait<TypeParam>::pointer(expected));
    ::testing::StaticAssertTypeEq<void*, PointerType>();
}

TYPED_TEST(VectorTypeTraitTest, test_const_pointer)
{
    const auto expected = TypeParam(this->N);
    EXPECT_EQ(expected.data(), type::Trait<TypeParam>::pointer(expected));

    using PointerType = decltype(type::Trait<TypeParam>::pointer(expected));
    ::testing::StaticAssertTypeEq<const void *, PointerType>();
}


