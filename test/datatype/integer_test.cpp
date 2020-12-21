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
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 23, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/datatype/integer.hpp>

using namespace hdf5;

template<class T>
class Integer : public testing::Test {
 protected:
  Integer() {}
  virtual ~Integer() {}
  T value_;
};

template <class T>
class SignedInteger : public Integer<T> { };

template <class T>
class UnsignedInteger : public Integer<T> { };

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

// The list of unsigned types we want to test.
typedef
Types<
    unsigned char,
    unsigned short,
    unsigned int,
    unsigned long,
    unsigned long long>
    test_unsigned_types;

// The list of signed types we want to test.
typedef
Types<signed char, short, int, long, long long> test_signed_types;

// workaround for the TYPED_TEST_SUITE bug #2316
#ifdef TYPED_TEST_SUITE
#include <gtest/internal/gtest-internal.h>
TYPED_TEST_SUITE(Integer, test_types, testing::internal::DefaultNameGenerator);
TYPED_TEST_SUITE(SignedInteger, test_signed_types, testing::internal::DefaultNameGenerator);
TYPED_TEST_SUITE(UnsignedInteger, test_unsigned_types, testing::internal::DefaultNameGenerator);
#else
TYPED_TEST_CASE(Integer, test_types);
TYPED_TEST_CASE(SignedInteger, test_signed_types);
TYPED_TEST_CASE(UnsignedInteger, test_unsigned_types);
#endif

TYPED_TEST(Integer, Exceptions) {
  datatype::Datatype dtype;
  EXPECT_THROW((datatype::Integer(dtype)), std::runtime_error);

  auto ft = datatype::create<double>();
  EXPECT_THROW((datatype::Integer(ft)), std::runtime_error);
}

TYPED_TEST(Integer, General) {
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

TYPED_TEST(SignedInteger, Signed) {
  auto t = datatype::create<decltype(this->value_)>();

  ASSERT_EQ(t.is_signed(), true);
  t.make_signed(true);
  ASSERT_EQ(t.is_signed(), true);
  t.make_signed(false);
  ASSERT_EQ(t.is_signed(), false);
}

TYPED_TEST(UnsignedInteger, Signed) {
  auto t = datatype::create<decltype(this->value_)>();

  ASSERT_EQ(t.is_signed(), false);
  t.make_signed(true);
  ASSERT_EQ(t.is_signed(), true);
  t.make_signed(false);
  ASSERT_EQ(t.is_signed(), false);
}

TYPED_TEST(Integer, Precision) {
  auto t = datatype::create<decltype(this->value_)>();
  ASSERT_EQ(t.precision(), t.size()*8lu);
  t.precision(16lu);
  ASSERT_EQ(t.precision(), 16lu);
  t.precision(8lu);
  ASSERT_EQ(t.precision(), 8lu);
}

TYPED_TEST(Integer, Order) {
  auto t = datatype::create<decltype(this->value_)>();
  EXPECT_TRUE (t.order() == datatype::Order::LE ||
	       t.order() == datatype::Order::BE ||
	       t.order() == datatype::Order::VAX)
    << "Where the order value: "   << t.order()
    << " equals neither: " << datatype::Order::LE
    << " nor: "               << datatype::Order::BE
    << " nor: "               << datatype::Order::VAX << ".";
  t.order(datatype::Order::BE);
  ASSERT_EQ(t.order(), datatype::Order::BE);
  t.order(datatype::Order::LE);
  ASSERT_EQ(t.order(), datatype::Order::LE);
}

TYPED_TEST(Integer, Offset) {
  auto t = datatype::create<decltype(this->value_)>();
  ASSERT_EQ(t.offset(), 0lu);
  t.offset(1);
  ASSERT_EQ(t.offset(), 1lu);
  t.offset(2);
  ASSERT_EQ(t.offset(), 2lu);
}

TYPED_TEST(Integer, Pad) {
  std::vector<datatype::Pad> pad00({datatype::Pad::ZERO, datatype::Pad::ZERO});
  std::vector<datatype::Pad> pad01({datatype::Pad::ZERO, datatype::Pad::ONE});
  std::vector<datatype::Pad> pad1B({datatype::Pad::ONE, datatype::Pad::BACKGROUND});
  auto t = datatype::create<decltype(this->value_)>();
  EXPECT_EQ (t.pad() , pad00);
  t.pad(datatype::Pad::ZERO, datatype::Pad::ONE);
  ASSERT_EQ(t.pad(), pad01);
  t.pad(datatype::Pad::ONE, datatype::Pad::BACKGROUND);
  ASSERT_EQ(t.pad(), pad1B);
}
