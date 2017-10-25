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
#include <thread>
#include <chrono>
#include <cstring>

extern "C"{
#include <cstdio>
}

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
}

TEST_F(Error, auto_off)
{
  error::auto_print(false);
  EXPECT_THROW(invalid_handle.get_reference_count(),std::runtime_error);
  EXPECT_TRUE(extract_string().empty()) << "post buffer contents:\n" << ss.str();
}
