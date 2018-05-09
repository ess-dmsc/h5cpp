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
// Created on: May 5, 2018
//

#include <gtest/gtest.h>
#include "../h5cpp_test_helpers.hpp"

using namespace hdf5;

TEST(Descriptor, extract_data)
{
  provoke_h5_error();
  auto stack = error::Singleton::instance().extract_stack();
  EXPECT_GT(stack.contents().size(), 0);
  auto d = stack.contents().front();

  EXPECT_GT(d.line, 10);
  EXPECT_EQ(d.function, "H5Iget_ref");
  EXPECT_NE(d.file.find("H5I.c"), std::string::npos);
  EXPECT_EQ(d.description, "can't get ID ref count");
}

TEST(Descriptor, extract_strings)
{
  provoke_h5_error();
  auto stack = error::Singleton::instance().extract_stack();
  EXPECT_GT(stack.contents().size(), 0);
  auto d = stack.contents().front();

  d.extract_strings();
  EXPECT_EQ(d.major, "Object atom");
  EXPECT_EQ(d.minor, "Can't get value");
}

TEST(Descriptor, stream)
{
  hdf5::ObjectHandle invalid_handle;
  H5Iget_ref(static_cast<hid_t>(invalid_handle));
  auto d = error::Singleton::instance().extract_stack().contents().front();

  std::stringstream ss;
  ss << d;
  EXPECT_NE(ss.str().find(d.description), std::string::npos);
}

// To ensure no-throw, C-string pointers must be null-initialized
// Talk to HDF5 group to see if they could make this happen
TEST(Descriptor, illegal)
{
  H5E_error2_t descr;
  descr.file_name = nullptr;
  descr.func_name = nullptr;
  descr.desc = nullptr;
  EXPECT_NO_THROW(error::Descriptor f(descr));
  error::Descriptor f(descr);

  // This also generates errors on the error stack!!! Insane!
  EXPECT_NO_THROW(f.extract_strings());

  error::Singleton::instance().clear_stack();
}
