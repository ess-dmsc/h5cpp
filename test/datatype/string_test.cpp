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

namespace type = hdf5::datatype;
namespace attr = hdf5::attribute;

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

template <class T>
class String : public BasicFixture
{
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

TEST(String, Constructors)
{
  auto t = type::String::fixed(3);
  EXPECT_TRUE(t.get_class()==type::Class::STRING);
  EXPECT_EQ(t.size(),3);
  EXPECT_FALSE(t.is_variable_length());

  auto t2 = type::String::variable();
  EXPECT_TRUE(t2.get_class()==type::Class::STRING);
  EXPECT_EQ(t2.size(),H5T_VARIABLE);
  EXPECT_TRUE(t2.is_variable_length());
}

TYPED_TEST(String, FixedIO)
{
  auto t = type::String::fixed(5);
  hdf5::dataspace::Scalar ds;

  attr::Attribute a = this->root_.attributes.create("string", t, ds);
  this->value_ = "abc  ";
  a.write(this->value_.c_str(), t);

//  T read1("cba");
//  a.read(read1);
//  EXPECT_EQ(write_string, read1);

//  T read2(6, '\0');
//  a.read(read2);
//  EXPECT_EQ(write_string, read2);
}

TYPED_TEST(String, VariableIO)
{
  auto t = type::create<decltype(this->value_)>();
  hdf5::dataspace::Scalar ds;

  attr::Attribute a = this->root_.attributes.create("string", t, ds);
  this->value_ = "hello world";
  a.write(this->value_);

//  auto read1 = this->value_;
//  a.read(read1);
//  EXPECT_EQ(this->value_, read1);

//  T read2(20, '\0');
//  a.read(read2);
//  EXPECT_EQ(write_string, read2);
}


