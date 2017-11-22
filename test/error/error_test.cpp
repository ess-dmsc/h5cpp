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

#include <cstring>
#include <cstdio>

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
  error::auto_print(true);
  EXPECT_THROW(invalid_handle.get_reference_count(),std::runtime_error);
  EXPECT_FALSE(extract_string().empty());
  EXPECT_TRUE(error::auto_print());
}

TEST_F(Error, auto_off)
{
  error::auto_print(false);
  EXPECT_THROW(invalid_handle.get_reference_count(),std::runtime_error);
  EXPECT_TRUE(extract_string().empty()) << "post buffer contents:\n" << ss.str();
  EXPECT_FALSE(error::auto_print());
}

TEST_F(Error, print_string)
{
  EXPECT_THROW(invalid_handle.get_reference_count(),std::runtime_error);
  auto stack1 = error::print_stack();
  auto size1 = stack1.size();
  EXPECT_GT(size1, 0);
//  EXPECT_FALSE(true) << "STACK:\n" << stack1;

  EXPECT_THROW(invalid_handle.get_reference_count(),std::runtime_error);
  auto stack2 = error::print_stack();
  auto size2 = stack2.size();
  EXPECT_GT(size2, 0);
  EXPECT_EQ(size1, size2);
//  EXPECT_FALSE(true) << "STACK2:\n" << stack2;
}