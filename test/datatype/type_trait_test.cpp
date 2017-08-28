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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing default type traits
#include <boost/test/unit_test.hpp>
#include <h5cpp/datatype/type_trait.hpp>
#include <h5cpp/datatype/datatype.hpp>

namespace ds = hdf5::datatype;

BOOST_AUTO_TEST_SUITE(TypeTrait_test)

BOOST_AUTO_TEST_CASE(test_char)
{
  auto type = ds::TypeTrait<char>::create();
  BOOST_CHECK(type.get_class()==ds::Class::INTEGER);
  BOOST_CHECK(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_CHAR));
}

BOOST_AUTO_TEST_CASE(test_unsigned_char)
{
  auto type = ds::TypeTrait<unsigned char>::create();
  BOOST_CHECK(type.get_class()==ds::Class::INTEGER);
  BOOST_CHECK(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_UCHAR));

}

BOOST_AUTO_TEST_CASE(test_signed_char)
{
  auto type = ds::TypeTrait<signed char>::create();
  BOOST_CHECK(type.get_class()==ds::Class::INTEGER);
  BOOST_CHECK(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_SCHAR));
}

BOOST_AUTO_TEST_CASE(test_short)
{
  auto type = ds::TypeTrait<short>::create();
  BOOST_CHECK(type.get_class()==ds::Class::INTEGER);
  BOOST_CHECK(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_SHORT));
}

BOOST_AUTO_TEST_CASE(test_unsigned_short)
{
  auto type = ds::TypeTrait<unsigned short>::create();
  BOOST_CHECK(type.get_class()==ds::Class::INTEGER);
  BOOST_CHECK(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_USHORT));
}

BOOST_AUTO_TEST_CASE(test_int)
{
  auto type = ds::TypeTrait<int>::create();
  BOOST_CHECK(type.get_class()==ds::Class::INTEGER);
  BOOST_CHECK(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_INT));
}

BOOST_AUTO_TEST_CASE(test_unsigned_int)
{
  auto type = ds::TypeTrait<unsigned int>::create();
  BOOST_CHECK(type.get_class()==ds::Class::INTEGER);
  BOOST_CHECK(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_UINT));
}

BOOST_AUTO_TEST_CASE(test_long)
{
  auto type = ds::TypeTrait<long>::create();
  BOOST_CHECK(type.get_class()==ds::Class::INTEGER);
  BOOST_CHECK(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_LONG));
}

BOOST_AUTO_TEST_CASE(test_unsigned_long)
{
  auto type = ds::TypeTrait<unsigned long>::create();
  BOOST_CHECK(type.get_class()==ds::Class::INTEGER);
  BOOST_CHECK(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_ULONG));
}

BOOST_AUTO_TEST_CASE(test_long_long)
{
  auto type = ds::TypeTrait<long long>::create();
  BOOST_CHECK(type.get_class()==ds::Class::INTEGER);
  BOOST_CHECK(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_LLONG));
}

BOOST_AUTO_TEST_CASE(test_unsigned_long_long)
{
  auto type = ds::TypeTrait<unsigned long>::create();
  BOOST_CHECK(type.get_class()==ds::Class::INTEGER);
  BOOST_CHECK(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_ULLONG));
}

BOOST_AUTO_TEST_CASE(test_float)
{
  auto type = ds::TypeTrait<float>::create();
  BOOST_CHECK(type.get_class()==ds::Class::FLOAT);
  BOOST_CHECK(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_FLOAT));
}

BOOST_AUTO_TEST_CASE(test_double)
{
  auto type = ds::TypeTrait<double>::create();
  BOOST_CHECK(type.get_class()==ds::Class::FLOAT);
  BOOST_CHECK(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_DOUBLE));
}

BOOST_AUTO_TEST_CASE(test_long_double)
{
  auto type = ds::TypeTrait<long double>::create();
  BOOST_CHECK(type.get_class()==ds::Class::FLOAT);
  BOOST_CHECK(H5Tequal(static_cast<hid_t>(type),H5T_NATIVE_LDOUBLE));
}

BOOST_AUTO_TEST_SUITE_END()
