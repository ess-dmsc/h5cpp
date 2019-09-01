//
// (c) Copyright 2019 DESY,ESS
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
// Created on: Sep 1, 2019
//

#include <h5cpp/hdf5.hpp>
#include <h5cpp/stl.hpp>
#include <gtest/gtest.h>


using namespace hdf5;

template<typename T>
class VectorMemoryAdapterTest : public ::testing::Test
{
  protected:
    using ValueType = typename T::value_type;
    static const size_t size = 10;
    T data;
    const T cdata;

    VectorMemoryAdapterTest():
      data(size),
      cdata(size)
    {}

};

using test_types = ::testing::Types<
    std::vector<unsigned char>, std::vector<char>,
    std::vector<unsigned short>, std::vector<short>,
    std::vector<unsigned int>, std::vector<int>,
    std::vector<unsigned long>, std::vector<long>,
    std::vector<unsigned long long>, std::vector<long long>>;

TYPED_TEST_CASE(VectorMemoryAdapterTest, test_types);


TYPED_TEST(VectorMemoryAdapterTest, test_non_const_construction)
{
  using ValueType = typename TypeParam::value_type;
  auto adapter = memory::make_adapter(this->data);

  ::testing::StaticAssertTypeEq<memory::MemoryAdapter<TypeParam>,
                                decltype(adapter)>();
  ::testing::StaticAssertTypeEq<void*, decltype(adapter.pointer())>();
  ::testing::StaticAssertTypeEq<dataspace::Simple,
                                typename decltype(adapter)::DataspaceType>();
  ::testing::StaticAssertTypeEq<typename datatype::Trait<ValueType>::TypeClass,
                                typename decltype(adapter)::DatatypeType>();
  ASSERT_EQ(this->data.data(), adapter.pointer());
}

TYPED_TEST(VectorMemoryAdapterTest, test_const_construction)
{
  const auto adapter = memory::make_adapter(this->cdata);

  ::testing::StaticAssertTypeEq<const memory::MemoryAdapter<TypeParam>,
                                decltype(adapter)>();
  ::testing::StaticAssertTypeEq<const void*, decltype(adapter.pointer())>();

  ASSERT_EQ(this->cdata.data(), adapter.pointer());
}

TYPED_TEST(VectorMemoryAdapterTest, test_dataspace_construction)
{
  auto adapter = memory::make_adapter(this->data);

  auto space = adapter.dataspace();
  ::testing::StaticAssertTypeEq<dataspace::Simple, decltype(space)>();
  ASSERT_EQ(10, space.size());
}

TYPED_TEST(VectorMemoryAdapterTest, test_datatype_construction)
{
  using ValueType = typename TypeParam::value_type;
  auto adapter = memory::make_adapter(this->data);
  auto type = adapter.datatype();
  ASSERT_EQ(sizeof(ValueType), type.size());
  ASSERT_EQ(std::is_signed<ValueType>::value, type.is_signed());
}
