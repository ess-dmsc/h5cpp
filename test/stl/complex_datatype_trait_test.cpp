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
#include <h5cpp/stl.hpp>
#include <gtest/gtest.h>

using namespace hdf5;
using test_types = ::testing::Types<float, double, long double>;

template<typename T>
class ComplexDatatypeTraitTest : public ::testing::Test { };


TYPED_TEST_CASE(ComplexDatatypeTraitTest, test_types);

TYPED_TEST(ComplexDatatypeTraitTest, test)
{
  auto datatype = datatype::Trait<std::complex<TypeParam>>::create();
  EXPECT_EQ(sizeof(std::complex<TypeParam>), datatype.size());
  EXPECT_EQ(2, datatype.number_of_fields());
  EXPECT_EQ("real", datatype.field_name(0));
  EXPECT_EQ("imag", datatype.field_name(1));
}
