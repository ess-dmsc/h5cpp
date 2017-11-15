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
// Created on: Aug 14, 2017
//

#include <gtest/gtest.h>
#include "object_handle_test.hpp"

ObjectHandleTest::ObjectHandleTest(hdf5::ObjectHandle::Type type):
type_(type)
{
}

ObjectHandleTest::~ObjectHandleTest()
{
}

void ObjectHandleTest::test_copy_construction()
{
  hdf5::ObjectHandle handle(this->create_object());
  EXPECT_TRUE(handle.is_valid());
  EXPECT_EQ(handle.get_type(),get_type());
  EXPECT_EQ(handle.get_reference_count(),1);

  hdf5::ObjectHandle handle2(handle);
  EXPECT_TRUE(handle.is_valid());
  EXPECT_TRUE(handle2.is_valid());
  EXPECT_EQ(handle.get_reference_count(),2);
  EXPECT_EQ(handle2.get_reference_count(),2);

}

void ObjectHandleTest::test_move_construction()
{
  hdf5::ObjectHandle handle(create_object());
  hdf5::ObjectHandle handle2(std::move(handle));
  EXPECT_TRUE(handle2.is_valid());
  EXPECT_EQ(handle2.get_reference_count(),1);
}


void ObjectHandleTest::test_copy_assignment()
{
  hdf5::ObjectHandle handle(create_object());
  hdf5::ObjectHandle handle2;

  handle2 = handle;
  EXPECT_TRUE(handle.is_valid());
  EXPECT_TRUE(handle2.is_valid());
  EXPECT_EQ(handle.get_reference_count(),2);
  EXPECT_EQ(handle2.get_reference_count(),2);
}

void ObjectHandleTest::test_move_assignment()
{
  hdf5::ObjectHandle handle(create_object());
  hdf5::ObjectHandle handle2;

  handle2 = std::move(handle);
  EXPECT_TRUE(!handle.is_valid());
  EXPECT_TRUE(handle2.is_valid());
  EXPECT_EQ(handle2.get_reference_count(),1);
}


hdf5::ObjectHandle::Type ObjectHandleTest::get_type() const
{
  return type_;
}

std::string string_from_type(hdf5::ObjectHandle::Type type)
{
  std::stringstream ss;
  ss<<type;
  return ss.str();
}

