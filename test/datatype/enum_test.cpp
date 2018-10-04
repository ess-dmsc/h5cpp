//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5cpp.
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
// Created on: May 14, 2018
//
#include <gtest/gtest.h>
#include <h5cpp/datatype/enum.hpp>
#include <h5cpp/datatype/ebool.hpp>
#include <h5cpp/datatype/factory.hpp>
#include "../fixture.hpp"

struct Enum : public BasicFixture
{};

enum WeakFruit : uint16_t { Apple = 0, Pear = 1, Orange = 2};
enum class StrongFruit : uint16_t { Pineapple = 0, Jackfruit = 1, Durian = 2};
enum FakeBool : int8_t { TRUE = 0, FALSE = 1};

namespace hdf5 {
namespace datatype {

template<>
class TypeTrait<WeakFruit> {
 public:
  using TypeClass = Enum;

  static TypeClass create(const WeakFruit & = WeakFruit()) {
    auto type = datatype::Enum::create(WeakFruit());
    type.insert("Apple", WeakFruit::Apple);
    type.insert("Pear", WeakFruit::Pear);
    type.insert("Orange", WeakFruit::Orange);
    return type;
  }
};

template<>
class TypeTrait<StrongFruit> {
 public:
  using TypeClass = Enum;

  static TypeClass create(const StrongFruit & = StrongFruit()) {
    auto type = datatype::Enum::create(StrongFruit());
    type.insert("Pineapple", StrongFruit::Pineapple);
    type.insert("Jackfruit", StrongFruit::Jackfruit);
    type.insert("Durian", StrongFruit::Durian);
    return type;
  }
};

template<>
class TypeTrait<FakeBool> {
 public:
  using TypeClass = Enum;

  static TypeClass create(const FakeBool & = FakeBool()) {
    auto type = datatype::Enum::create(FakeBool());
    type.insert("TRUE", FakeBool::TRUE);
    type.insert("FALSE", FakeBool::FALSE);
    return type;
  }
};

}
}


using namespace hdf5;

TEST_F(Enum, DefaultConstruction) {
  datatype::Enum type;
  EXPECT_FALSE(type.is_valid());
  EXPECT_EQ(type.get_class(), datatype::Class::NONE);
}

TEST_F(Enum, Exceptions) {
  auto ft = datatype::create<double>();
  EXPECT_THROW((datatype::Enum(ft)), std::runtime_error);
  EXPECT_THROW((datatype::Enum::create_underlying(datatype::Datatype())), std::runtime_error);
}

TEST_F(Enum, IntConstruction) {
  auto base_type = datatype::create<int>();
  auto type = datatype::Enum::create_underlying(base_type);
  EXPECT_TRUE(type.is_valid());
  EXPECT_EQ(type.get_class(), datatype::Class::ENUM);
  EXPECT_EQ(type.number_of_values(), 0);

  ObjectHandle(static_cast<hid_t>(type)).close();
  EXPECT_THROW((type.number_of_values()), std::runtime_error);
}

TEST_F(Enum, Insert) {
  auto type = datatype::Enum::create_underlying(datatype::create<int>());

  int val1 = 1;
  type.insert_underlying("val1", val1);
  EXPECT_EQ(type.number_of_values(), 1);

  // duplicate value
  EXPECT_THROW((type.insert_underlying("val2", val1)), std::runtime_error);
}

TEST_F(Enum, InsertTypeMismatch) {
  auto type = datatype::Enum::create_underlying(datatype::create<int>());

  double val1 = 1;
  EXPECT_THROW((type.insert_underlying("val1", val1)), std::runtime_error);
}

TEST_F(Enum, GetName) {
  auto type = datatype::Enum::create_underlying(datatype::create<int>());
  int val1 = 1;
  type.insert_underlying("val1", val1);
  EXPECT_EQ(type.name(0), "val1");

  EXPECT_THROW((type.name(1)), std::runtime_error);

  ObjectHandle(static_cast<hid_t>(type)).close();
  EXPECT_THROW((type.name(0)), std::runtime_error);
}

TEST_F(Enum, GetValue) {
  auto type = datatype::Enum::create_underlying(datatype::create<int>());
  int val1 = 1;
  type.insert_underlying("val1", val1);

  int val2;
  type.underlying_value(0, val2);
  EXPECT_EQ(val2, val1);

  EXPECT_THROW(type.underlying_value(1, val2), std::runtime_error);
  double val3;
  EXPECT_THROW(type.underlying_value(0, val3), std::runtime_error);
}

TEST_F(Enum, GetValueByName) {
  auto type = datatype::Enum::create_underlying(datatype::create<int>());
  type.insert_underlying("val1", (int)1);

  int val2;
  type.underlying_value("val1", val2);
  EXPECT_EQ(val2, 1);

  EXPECT_THROW(type.underlying_value("val2", val2), std::runtime_error);
  double val3;
  EXPECT_THROW(type.underlying_value("val1", val3), std::runtime_error);
}

TEST_F(Enum, test_weak_enum) {
  auto type = datatype::create<WeakFruit>();
  EXPECT_EQ(type.name(0), "Apple");
  EXPECT_EQ(type.value<WeakFruit>(0), WeakFruit::Apple);
  EXPECT_EQ(type.name(1), "Pear");
  EXPECT_EQ(type.value<WeakFruit>(1), WeakFruit::Pear);
  EXPECT_EQ(type.name(2), "Orange");
  EXPECT_EQ(type.value<WeakFruit>(2), WeakFruit::Orange);

  WeakFruit write_fruit = WeakFruit::Apple;
  WeakFruit read_fruit = WeakFruit::Orange;

  auto a = root_.attributes.create<WeakFruit>("fruit");
  auto edt = datatype::Enum(a.datatype());
  EXPECT_EQ(datatype::is_bool(edt), false);
  a.write(write_fruit);
  a.read(read_fruit);

  EXPECT_EQ(write_fruit, read_fruit);
}

TEST_F(Enum, test_strong_enum) {
  auto type = datatype::create<StrongFruit>();
  EXPECT_EQ(type.name(0), "Pineapple");
  EXPECT_EQ(type.value<StrongFruit>(0), StrongFruit::Pineapple);
  EXPECT_EQ(type.name(1), "Jackfruit");
  EXPECT_EQ(type.value<StrongFruit>(1), StrongFruit::Jackfruit);
  EXPECT_EQ(type.name(2), "Durian");
  EXPECT_EQ(type.value<StrongFruit>(2), StrongFruit::Durian);

  auto write_fruit = StrongFruit::Pineapple;
  auto read_fruit = StrongFruit::Durian;

  auto a = root_.attributes.create<StrongFruit>("fruit");
  auto edt = datatype::Enum(a.datatype());
  EXPECT_EQ(datatype::is_bool(edt), false);
  a.write(write_fruit);
  a.read(read_fruit);

  EXPECT_EQ(write_fruit, read_fruit);
}

TEST_F(Enum, test_ebool_true) {
  auto type = datatype::create<datatype::EBool>();
  EXPECT_EQ(type.name(0), "FALSE");
  EXPECT_EQ(type.value<datatype::EBool>(0), datatype::EBool::FALSE);
  EXPECT_EQ(type.name(1), "TRUE");
  EXPECT_EQ(type.value<datatype::EBool>(1), datatype::EBool::TRUE);

  datatype::EBool write_ebool = datatype::EBool::TRUE;
  datatype::EBool read_ebool = datatype::EBool::FALSE;

  auto a = root_.attributes.create<datatype::EBool>("TRUE");
  auto edt = datatype::Enum(a.datatype());
  EXPECT_EQ(datatype::is_bool(edt), true);
  a.write(write_ebool);
  a.read(read_ebool);

  EXPECT_EQ(write_ebool, read_ebool);
  EXPECT_EQ(1, read_ebool);
  EXPECT_EQ(true, read_ebool);
}

TEST_F(Enum, test_ebool_false) {
  auto type = datatype::create<datatype::EBool>();
  EXPECT_EQ(type.name(0), "FALSE");
  EXPECT_EQ(type.value<datatype::EBool>(0), datatype::EBool::FALSE);
  EXPECT_EQ(type.name(1), "TRUE");
  EXPECT_EQ(type.value<datatype::EBool>(1), datatype::EBool::TRUE);

  datatype::EBool write_ebool = datatype::EBool::FALSE;
  datatype::EBool read_ebool = datatype::EBool::TRUE;

  auto a = root_.attributes.create<datatype::EBool>("FALSE");
  auto edt = datatype::Enum(a.datatype());
  EXPECT_EQ(datatype::is_bool(edt), true);
  a.write(write_ebool);
  a.read(read_ebool);

  EXPECT_EQ(write_ebool, read_ebool);
  EXPECT_EQ(0, read_ebool);
  EXPECT_EQ(false, read_ebool);
}

TEST_F(Enum, test_ebool_array)
{
  auto a = root_.attributes.create<datatype::EBool>("bool_array", {4});
  std::vector<datatype::EBool> buffer(4);
  std::vector<datatype::EBool> buffer2(4);
  std::vector<int> buffer_int(4);

  std::vector<datatype::EBool> ref  = {datatype::EBool::FALSE,
				       datatype::EBool::TRUE,
				       datatype::EBool::TRUE,
				       datatype::EBool::FALSE};
  std::vector<int> ref_int  = {0, 1, 1, 0};

  EXPECT_EQ(a.datatype().get_class(), datatype::Class::ENUM);
  EXPECT_EQ(a.datatype().size(), 1);
  auto edt = datatype::Enum(a.datatype());
  EXPECT_EQ(datatype::is_bool(edt), true);
  a.write(ref);

  a.read(buffer, a.datatype());
  EXPECT_EQ(buffer, ref);

  a.read(buffer2);
  EXPECT_EQ(buffer2, ref);

  a.read(buffer_int);
  EXPECT_EQ(buffer_int, ref_int);
}

TEST_F(Enum, test_fake_bool) {
  auto type = datatype::create<FakeBool>();
  EXPECT_EQ(type.name(1), "FALSE");
  EXPECT_EQ(type.value<FakeBool>(1), FakeBool::FALSE);
  EXPECT_EQ(type.name(0), "TRUE");
  EXPECT_EQ(type.value<FakeBool>(0), FakeBool::TRUE);
  EXPECT_EQ(datatype::is_bool(type), false);
}
