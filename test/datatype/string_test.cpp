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
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 11, 2017
//

#include <gtest/gtest.h>
#include <boost/mpl/list.hpp>
#include <h5cpp/datatype/factory.hpp>
#include <h5cpp/datatype/string.hpp>
#include <h5cpp/attribute/attribute.hpp>
#include <h5cpp/file/file.hpp>
#include <h5cpp/file/functions.hpp>
#include <h5cpp/node/group.hpp>
#include <h5cpp/dataspace/scalar.hpp>
#include "../fixture.hpp"

using namespace hdf5;

//template <class T>
//class String : public testing::Test
//{
// protected:
//  String()
//  {
//    file_ = hdf5::file::create("CompoundTest.h5",hdf5::file::AccessFlags::TRUNCATE);
//    root_group_ = file_.root();
//  }
//  virtual ~String() {}
//  T value_;
//  hdf5::file::File file_;
//  hdf5::node::Group root_group_;
//};

template<class T>
class String : public BasicFixture {
 protected:
  T value_;
};

using testing::Types;

// The list of types we want to test.
typedef
Types<std::string>
//std::wstring,
//std::u16string,
//std::u32string>
    test_types;

TYPED_TEST_CASE(String, test_types);

TEST(String, Constructor) {
  datatype::Datatype dtype;
  EXPECT_THROW((datatype::String(dtype)), std::runtime_error);

  auto ft = datatype::create<double>();
  EXPECT_THROW((datatype::String(ft)), std::runtime_error);
}

TEST(String, Fixed) {
  datatype::String t = datatype::String::fixed(3);
  EXPECT_TRUE(t.get_class() == datatype::Class::STRING);
  EXPECT_FALSE(t.is_variable_length());
  EXPECT_EQ(t.size(), 3ul);

  t.size(5ul);
  EXPECT_EQ(t.size(), 5ul);
  EXPECT_THROW((t.size(0ul)),std::runtime_error);
}

TEST(String, Variable) {
  auto t = datatype::String::variable();
  EXPECT_TRUE(t.get_class() == datatype::Class::STRING);
  EXPECT_EQ(t.size(), H5T_VARIABLE);
  EXPECT_TRUE(t.is_variable_length());

  EXPECT_THROW(t.size(5ul), std::runtime_error);
  ObjectHandle(static_cast<hid_t>(t)).close();
  EXPECT_THROW(t.is_variable_length(), std::runtime_error);
}

TEST(String, Encoding) {
  auto t = datatype::String::fixed(3);
  t.encoding(datatype::CharacterEncoding::ASCII);
  EXPECT_EQ(t.encoding(), datatype::CharacterEncoding::ASCII);

  t.encoding(datatype::CharacterEncoding::UTF8);
  EXPECT_EQ(t.encoding(), datatype::CharacterEncoding::UTF8);

  ObjectHandle(static_cast<hid_t>(t)).close();
  EXPECT_THROW(t.encoding(), std::runtime_error);
  EXPECT_THROW(t.encoding(datatype::CharacterEncoding::UTF8), std::runtime_error);
}

TEST(String, Padding) {
  auto t = datatype::String::fixed(3);
  t.padding(datatype::StringPad::SPACEPAD);
  EXPECT_EQ(t.padding(), datatype::StringPad::SPACEPAD);

  t.padding(datatype::StringPad::NULLTERM);
  EXPECT_EQ(t.padding(), datatype::StringPad::NULLTERM);

  t.padding(datatype::StringPad::NULLPAD);
  EXPECT_EQ(t.padding(), datatype::StringPad::NULLPAD);

  ObjectHandle(static_cast<hid_t>(t)).close();
  EXPECT_THROW(t.padding(), std::runtime_error);
  EXPECT_THROW(t.padding(datatype::StringPad::NULLPAD), std::runtime_error);
}

