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
#include "../h5cpp_test_helpers.hpp"
#include "../gtest_print.hpp"

#include <cstring>

using namespace hdf5;

#define bufsize 7000

class Error : public testing::Test
{
 protected:
  virtual void SetUp()
  {
    // redirect stderr into buf
    fflush(stderr);
    std::memset(buf, 0, bufsize);
    setbuf(stderr, buf);
  }

  std::string extract_string()
  {
    // extract redirected stderr text
    ss.str(std::string());
    ss << buf;
    return ss.str();
  }

  virtual void TearDown()
  {
    // return stderr to normal function
    setbuf(stderr, NULL);
  }

  std::stringstream ss;
  char buf[bufsize];
};

TEST_F(Error, auto_on)
{
  error::Singleton::instance().auto_print(true);
  EXPECT_TRUE(error::Singleton::instance().auto_print());
  provoke_h5_error();
  EXPECT_FALSE(extract_string().empty());
  EXPECT_THROW(provoke_h5cpp_exception(), std::runtime_error);
}

TEST_F(Error, auto_off)
{
  error::Singleton::instance().auto_print(false);
  EXPECT_FALSE(error::Singleton::instance().auto_print());
  provoke_h5_error();
  EXPECT_TRUE(extract_string().empty());
  EXPECT_THROW(provoke_h5cpp_exception(), std::runtime_error);
}

TEST_F(Error, extract_stack)
{
  error::Singleton::instance().auto_print(false);

  provoke_h5_error();
  auto stack = error::Singleton::instance().extract_stack();
  EXPECT_EQ(stack.contents().size(), 2u);
}

TEST_F(Error, clear_stack)
{
  error::Singleton::instance().auto_print(false);

  provoke_h5_error();
  error::Singleton::instance().clear_stack();
  auto stack = error::Singleton::instance().extract_stack();
  EXPECT_TRUE(stack.empty());

  error::Singleton::instance().clear_stack();
  error::Singleton::instance().clear_stack();
}

TEST_F(Error, sequential)
{
  error::Singleton::instance().auto_print(false);

  provoke_h5_error();
  EXPECT_EQ(error::Singleton::instance().extract_stack().contents().size(), 2ul);
  EXPECT_TRUE(error::Singleton::instance().extract_stack().empty());

  provoke_h5_error();
  EXPECT_EQ(error::Singleton::instance().extract_stack().contents().size(), 2ul);
  EXPECT_TRUE(error::Singleton::instance().extract_stack().empty());

  provoke_h5_error();
  EXPECT_EQ(error::Singleton::instance().extract_stack().contents().size(), 2ul);
  EXPECT_TRUE(error::Singleton::instance().extract_stack().empty());
}


TEST_F(Error, exception_generation_print_on)
{
  error::Singleton::instance().auto_print(true);
  try
  {
    provoke_h5cpp_exception();
  }
  catch (std::exception& e)
  {
    auto message = error::print_nested(e);
    EXPECT_EQ(message, "ObjectHandle: could not get reference counter\n");
  }
}

TEST_F(Error, exception_generation_print_off)
{
  error::Singleton::instance().auto_print(false);
  try
  {
    provoke_h5cpp_exception();
  }
  catch (std::exception& e)
  {
    auto message = error::print_nested(e);
    EXPECT_GT(message.size(), 20ul);
#ifdef _MSC_ER
    TEST_COUT << "\n" << message;
#endif
  }
}
