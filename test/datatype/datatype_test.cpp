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
//    Eugen Wintersberger <eugen.wintersberger@desy.de>
//    Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 19, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/datatype/datatype.hpp>

using namespace hdf5;
using namespace hdf5::datatype;

TEST(Datatype, ConstructCopy)
{
  Datatype a(ObjectHandle(H5Tcopy(H5T_NATIVE_INT)));
  EXPECT_TRUE(a.get_class()==Class::INTEGER);

  auto b = Datatype(ObjectHandle(H5Tcopy(H5T_NATIVE_INT)));
  EXPECT_TRUE(b.get_class()==Class::INTEGER);

  Datatype c = b = a;
  EXPECT_TRUE(c.get_class()==Class::INTEGER);
  EXPECT_NE(static_cast<hid_t>(a), static_cast<hid_t>(b));
  EXPECT_NE(static_cast<hid_t>(b), static_cast<hid_t>(c));
  EXPECT_NE(static_cast<hid_t>(a), static_cast<hid_t>(c));

  Datatype d(b);
  EXPECT_TRUE(d.get_class()==Class::INTEGER);
  EXPECT_NE(static_cast<hid_t>(d), static_cast<hid_t>(b));

  Datatype x;
  Datatype y;
  EXPECT_THROW(y=x, std::runtime_error);
  EXPECT_THROW(y=Datatype(x), std::runtime_error);
}

TEST(Datatype, Comparators)
{
  Datatype a(ObjectHandle(H5Tcopy(H5T_NATIVE_INT)));
  auto b = a;
  EXPECT_NE(static_cast<hid_t>(a), static_cast<hid_t>(b));
  EXPECT_EQ(a, b);
  b = Datatype(ObjectHandle(H5Tcopy(H5T_NATIVE_FLOAT)));
  EXPECT_NE(a, b);

  Datatype c;
  EXPECT_THROW((a == c), std::runtime_error);
}

TEST(Datatype, Classes)
{
  Datatype a;
//  EXPECT_TRUE(a.get_class()==Class::NONE);
  EXPECT_THROW(a.super(), std::runtime_error);
  EXPECT_THROW(a.has_class(Class::INTEGER), std::runtime_error);
  EXPECT_THROW(a.native_type(), std::runtime_error);
  EXPECT_THROW(a.size(), std::runtime_error);
  EXPECT_THROW(a.set_size(1);, std::runtime_error);

  a = Datatype(ObjectHandle(H5Tcopy(H5T_NATIVE_INT)));
  EXPECT_EQ(a.get_class(), Class::INTEGER);
  EXPECT_EQ(a.native_type(), a);

  a = Datatype(ObjectHandle(H5Tcopy(H5T_NATIVE_FLOAT)));
  EXPECT_EQ(a.get_class(), Class::FLOAT);

  a = Datatype(ObjectHandle(H5Tcreate(H5T_STRING,1)));
  EXPECT_EQ(a.get_class(), Class::STRING);

  a = Datatype(ObjectHandle(H5Tcreate(H5T_COMPOUND,8)));
  EXPECT_EQ(a.get_class(), Class::COMPOUND);
  EXPECT_THROW(a.super(), std::runtime_error);
  H5Tinsert(static_cast<hid_t>(a),"hello",0,H5T_NATIVE_INT);
  EXPECT_TRUE(a.has_class(Class::INTEGER));
  EXPECT_FALSE(a.has_class(Class::FLOAT));

  a = Datatype(ObjectHandle(H5Tcreate(H5T_OPAQUE,1)));
  EXPECT_EQ(a.get_class(), Class::OPAQUE);

  a = Datatype(ObjectHandle(H5Tcreate(H5T_ENUM,1)));
  EXPECT_EQ(a.get_class(), Class::ENUM);
  auto b = a.super();
  EXPECT_EQ(b.get_class(), Class::INTEGER);


  a = Datatype(ObjectHandle(H5Tvlen_create(H5T_NATIVE_INT)));
  EXPECT_EQ(a.get_class(), Class::VARLENGTH);

//  a = Datatype(ObjectHandle(H5Tcopy(H5T_NATIVE_HBOOL)));
//  a = Datatype(ObjectHandle((H5T_BITFIELD)));
//  a = Datatype(ObjectHandle(H5Tcopy(H5T_BITFIELD)));
//  EXPECT_TRUE(a.native_type().get_class()==Class::BITFIELD);

//  a = Datatype(ObjectHandle(H5Tcopy(H5T_REFERENCE)));
//  EXPECT_TRUE(a.get_class()==Class::REFERENCE);

//  a = Datatype(ObjectHandle(H5Tcreate(static_cast<H5T_class_t>(Class::TIME),1)));
//  EXPECT_TRUE(a.get_class()==Class::TIME);

}

TEST(Datatype, Size)
{
  auto a = Datatype(ObjectHandle(H5Tcreate(H5T_COMPOUND,2)));
  ASSERT_EQ(a.size(), 2);
  a.set_size(4);
  ASSERT_EQ(a.size(), 4);
}
