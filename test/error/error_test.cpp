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
// Created on: Oct 25, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/error/error.hpp>
#include "../gtest_print.hpp"

#include <cstring>

using namespace hdf5;

#define bufsize 7000

class Error : public testing::Test
{
  protected:
    virtual void SetUp()
    {
      fflush(stderr);
      std::memset(buf, 0, bufsize);
      setbuf(stderr, buf);
    }

    std::string extract_string()
    {
      ss.str(std::string());
      ss << buf;
      return ss.str();
    }

    virtual void TearDown()
    {
      setbuf(stderr, NULL);
    }

    hdf5::ObjectHandle invalid_handle;
    std::stringstream ss;
    char buf[bufsize];
};

TEST_F(Error, auto_on)
{
  error::Singleton::instance().auto_print(true);
  H5Iget_ref(static_cast<hid_t>(invalid_handle));
  EXPECT_FALSE(extract_string().empty());
  EXPECT_TRUE(error::Singleton::instance().auto_print());
}

TEST_F(Error, auto_off)
{
  error::Singleton::instance().auto_print(false);
  H5Iget_ref(static_cast<hid_t>(invalid_handle));
  EXPECT_TRUE(extract_string().empty()) << "post buffer contents:\n" << ss.str();
  EXPECT_FALSE(error::Singleton::instance().auto_print());
}

TEST_F(Error, print_stack)
{
  error::Singleton::instance().auto_print(false);

  H5Iget_ref(static_cast<hid_t>(invalid_handle));
  auto stack1 = error::Singleton::instance().print_stack();
  auto size1 = stack1.size();
  EXPECT_GT(size1, 0);
//  TEST_COUT << "STACK:\n" << stack1;

  H5Iget_ref(static_cast<hid_t>(invalid_handle));
  auto stack2 = error::Singleton::instance().print_stack();
  auto size2 = stack2.size();
  EXPECT_GT(size2, 0);
  EXPECT_EQ(size1, size2);
//  TEST_COUT << "STACK2:\n" << stack2;
}

TEST_F(Error, extract_stack)
{
  error::Singleton::instance().auto_print(false);

  H5Iget_ref(static_cast<hid_t>(invalid_handle));
  auto stack = error::Singleton::instance().extract_stack();
  EXPECT_EQ(stack.contents.size(), 2);

  for (auto e : stack.contents)
    TEST_COUT << e;
}


TEST_F(Error, exception_generation_print_off)
{
  error::Singleton::instance().auto_print(false);
  EXPECT_FALSE(error::Singleton::instance().auto_print());
  H5Iget_ref(static_cast<hid_t>(invalid_handle));

//  auto stack2 = error::Singleton::instance().print_stack();
//  auto size2 = stack2.size();
//  EXPECT_GT(size2, 0);

  try {
    error::Singleton::instance().throw_with_stack("some_error");
  }
  catch (std::exception& e)
  {
    auto message = error::print_exception(e);
    EXPECT_GT(message.size(), 20);
    TEST_COUT << "\n" << message;
  }
}


TEST_F(Error, exception_generation_print_on)
{
  error::Singleton::instance().auto_print(true);
  EXPECT_TRUE(error::Singleton::instance().auto_print());
  H5Iget_ref(static_cast<hid_t>(invalid_handle));

  try {
    error::Singleton::instance().throw_with_stack("some_error");
  }
  catch (std::exception& e)
  {
    auto message = error::print_exception(e);
    EXPECT_EQ(message, "some_error\n");
//    TEST_COUT << "\n" << message;
  }
}

