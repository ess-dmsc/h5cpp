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
// Created on: Aug 28, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/datatype/type_trait.hpp>
#include <h5cpp/datatype/datatype.hpp>

namespace ds = hdf5::datatype;

TEST(TypeTrait, test_char)
{
  auto type = ds::TypeTrait<char>::create();
  EXPECT_TRUE(type.get_class()==ds::Class::INTEGER);
  EXPECT_TRUE(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_CHAR));
}

TEST(TypeTrait, test_unsigned_char)
{
  auto type = ds::TypeTrait<unsigned char>::create();
  EXPECT_TRUE(type.get_class()==ds::Class::INTEGER);
  EXPECT_TRUE(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_UCHAR));

}

TEST(TypeTrait, test_signed_char)
{
  auto type = ds::TypeTrait<signed char>::create();
  EXPECT_TRUE(type.get_class()==ds::Class::INTEGER);
  EXPECT_TRUE(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_SCHAR));
}

TEST(TypeTrait, test_short)
{
  auto type = ds::TypeTrait<short>::create();
  EXPECT_TRUE(type.get_class()==ds::Class::INTEGER);
  EXPECT_TRUE(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_SHORT));
}

TEST(TypeTrait, test_unsigned_short)
{
  auto type = ds::TypeTrait<unsigned short>::create();
  EXPECT_TRUE(type.get_class()==ds::Class::INTEGER);
  EXPECT_TRUE(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_USHORT));
}

TEST(TypeTrait, test_int)
{
  auto type = ds::TypeTrait<int>::create();
  EXPECT_TRUE(type.get_class()==ds::Class::INTEGER);
  EXPECT_TRUE(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_INT));
}

TEST(TypeTrait, test_unsigned_int)
{
  auto type = ds::TypeTrait<unsigned int>::create();
  EXPECT_TRUE(type.get_class()==ds::Class::INTEGER);
  EXPECT_TRUE(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_UINT));
}

TEST(TypeTrait, test_long)
{
  auto type = ds::TypeTrait<long>::create();
  EXPECT_TRUE(type.get_class()==ds::Class::INTEGER);
  EXPECT_TRUE(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_LONG));
}

TEST(TypeTrait, test_unsigned_long)
{
  auto type = ds::TypeTrait<unsigned long>::create();
  EXPECT_TRUE(type.get_class()==ds::Class::INTEGER);
  EXPECT_TRUE(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_ULONG));
}

TEST(TypeTrait, test_long_long)
{
  auto type = ds::TypeTrait<long long>::create();
  EXPECT_TRUE(type.get_class()==ds::Class::INTEGER);
  EXPECT_TRUE(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_LLONG));
}

TEST(TypeTrait, test_unsigned_long_long)
{
  auto type = ds::TypeTrait<unsigned long long>::create();
  EXPECT_TRUE(type.get_class()==ds::Class::INTEGER);
  EXPECT_TRUE(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_ULLONG));
}

TEST(TypeTrait, test_float)
{
  auto type = ds::TypeTrait<float>::create();
  EXPECT_TRUE(type.get_class()==ds::Class::FLOAT);
  EXPECT_TRUE(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_FLOAT));
}

TEST(TypeTrait, test_double)
{
  auto type = ds::TypeTrait<double>::create();
  EXPECT_TRUE(type.get_class()==ds::Class::FLOAT);
  EXPECT_TRUE(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_DOUBLE));
}

TEST(TypeTrait, test_long_double)
{
  auto type = ds::TypeTrait<long double>::create();
  EXPECT_TRUE(type.get_class()==ds::Class::FLOAT);
  EXPECT_TRUE(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_LDOUBLE));
}


