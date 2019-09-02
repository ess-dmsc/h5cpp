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
// Created on: Sep 2, 2019
//

#include <h5cpp/hdf5.hpp>
#include <h5cpp/stl.hpp>
#include <gtest/gtest.h>

using namespace hdf5;


template<typename T>
class BaseStringTest : public ::testing::Test
{
  protected:
    std::string original_string;
    std::string temp_string;

    BaseStringTest():
      original_string("hello world"),
      temp_string("hello world")
    {}
};


using test_types = ::testing::Types<type::FixedUTF8String,
                                    type::FixedASCIIString,
                                    type::VariableASCIIString,
                                    type::VariableUTF8String>;

TYPED_TEST_CASE(BaseStringTest, test_types);


TYPED_TEST(BaseStringTest, test_literal_construction)
{
  TypeParam new_string = "hello world";
  EXPECT_EQ(this->original_string, new_string);
}


TYPED_TEST(BaseStringTest, test_copy_construction)
{
  TypeParam new_string = this->original_string;
  EXPECT_EQ(this->original_string, new_string);
}

TYPED_TEST(BaseStringTest, test_move_construction)
{
  TypeParam new_string = std::move(this->temp_string);
  EXPECT_EQ(this->original_string, new_string);

}

TYPED_TEST(BaseStringTest, test_literal_assignment)
{
  TypeParam new_string;
  new_string = "hello world";
  EXPECT_EQ(this->original_string, new_string);
}

TYPED_TEST(BaseStringTest, test_copy_assignment)
{
  TypeParam new_string;
  new_string = this->original_string;
}

TYPED_TEST(BaseStringTest, test_move_assignment)
{
  TypeParam new_string;
  new_string = std::move(this->original_string);
}

