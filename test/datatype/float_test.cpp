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
//   Jan Kotanski <jan.kotanski@desy.de>
// Created on: Aug 23, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/datatype/float.hpp>

using namespace hdf5;

template<class T>
class Float : public testing::Test {
 protected:
  Float() {}
  virtual ~Float() {}
  T value_;
};

using testing::Types;

// The list of types we want to test.
typedef
Types<datatype::float16_t, float, double, long double>
    test_types;

// workaround for the TYPED_TEST_SUITE bug #2316
#ifdef TYPED_TEST_SUITE
#include <gtest/internal/gtest-internal.h>
TYPED_TEST_SUITE(Float, test_types, testing::internal::DefaultNameGenerator);
#else
TYPED_TEST_CASE(Float, test_types);
#endif

TYPED_TEST(Float, Exceptions) {
  datatype::Datatype dtype;
  EXPECT_THROW((datatype::Float(dtype)), std::runtime_error);

  auto ft = datatype::create<int>();
  EXPECT_THROW((datatype::Float(ft)), std::runtime_error);
}

TYPED_TEST(Float, General) {
  auto t = datatype::create<decltype(this->value_)>();
  EXPECT_TRUE((std::is_same<decltype(t), datatype::Float>::value));
  EXPECT_TRUE(t.get_class() == datatype::Class::FLOAT);
  EXPECT_EQ(t.size(), sizeof(this->value_));

  //construct from Datatype reference to an existing type
  datatype::Datatype &generic_type = t;
  datatype::Float new_type(generic_type);
  EXPECT_EQ(new_type.get_class(), datatype::Class::FLOAT);

  //cannot construct from an invalid type
  datatype::Datatype default_constructed;
  EXPECT_THROW((datatype::Float(default_constructed)), std::runtime_error);
}

TYPED_TEST(Float, Precision) {
  auto t = datatype::create<decltype(this->value_)>();
  EXPECT_TRUE (t.precision() == t.size()*8 ||
	       t.precision() == 80)
    << "Where the precision value: "   << t.precision()
    << " equals neither: " << t.size()*8
    << " nor: "               << 80 << ".";
  t.precision(80);
  ASSERT_EQ(t.precision(), 80);
}

TYPED_TEST(Float, Order) {
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

TYPED_TEST(Float, Offset) {
  auto t = datatype::create<decltype(this->value_)>();
  ASSERT_EQ(t.offset(), 0);
  t.offset(1);
  ASSERT_EQ(t.offset(), 1);
  t.offset(2);
  ASSERT_EQ(t.offset(), 2);
}

TYPED_TEST(Float, Pad) {
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

TYPED_TEST(Float, Inpad) {
  auto t = datatype::create<decltype(this->value_)>();
  EXPECT_EQ (t.inpad() , datatype::Pad::ZERO);
  t.inpad(datatype::Pad::ONE);
  ASSERT_EQ(t.inpad(), datatype::Pad::ONE);
  t.inpad(datatype::Pad::BACKGROUND);
  ASSERT_EQ(t.inpad(), datatype::Pad::BACKGROUND);
}

TYPED_TEST(Float, Norm) {
  auto t = datatype::create<decltype(this->value_)>();
  EXPECT_TRUE (t.norm() == datatype::Norm::IMPLIED ||
	       t.norm() == datatype::Norm::NONE)
    << "Where the norm value: "   << t.norm()
    << " equals neither: " << datatype::Norm::IMPLIED
    << " nor: "               << datatype::Norm::NONE << ".";
  t.norm(datatype::Norm::MSBSET);
  ASSERT_EQ(t.norm(), datatype::Norm::MSBSET);
  t.norm(datatype::Norm::NONE);
  ASSERT_EQ(t.norm(), datatype::Norm::NONE);
}

TYPED_TEST(Float, EBias) {
  auto t = datatype::create<decltype(this->value_)>();
  EXPECT_TRUE (t.ebias() == 2*t.size()*t.size()*t.size() - 1 ||
	       t.ebias() == 4*t.size()*t.size()*t.size() - 1)
    << "Where the ebias value: "   << t.ebias()
    << " equals neither: " << (2*t.size()*t.size()*t.size() - 1)
    << " nor: "            << (4*t.size()*t.size()*t.size() - 1) << ".";
  t.ebias(63);
  ASSERT_EQ(t.ebias(), 63);
  t.ebias(31);
  ASSERT_EQ(t.ebias(), 31);
}

TYPED_TEST(Float, Fields) {
  std::vector<size_t> fields1({15, 10, 5, 0, 10});
  std::vector<size_t> fields2({14, 9, 5, 0, 9});
  auto t = datatype::create<decltype(this->value_)>();
  EXPECT_EQ (t.fields().size(), 5);
  t.fields(15, 10, 5, 0, 10);
  ASSERT_EQ(t.fields(), fields1);
  t.fields(14, 9, 5, 0, 9);
  ASSERT_EQ(t.fields(), fields2);
}
