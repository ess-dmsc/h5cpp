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

TEST(Error, auto_on)
{
  fflush(stderr);

  hdf5::ObjectHandle handle;
  std::stringstream ss;
  char buf2[bufsize]; std::memset(buf2, 0, sizeof(char) * bufsize);

  error::auto_print(true);
  setbuf(stderr, buf2);
  EXPECT_THROW(handle.get_reference_count(),std::runtime_error);

  ss.str(std::string());
  ss << buf2;
  EXPECT_FALSE(ss.str().empty());

  setbuf(stderr, NULL);
}

TEST(Error, auto_off)
{
  fflush(stderr);

  hdf5::ObjectHandle handle;
  std::stringstream ss;
  char buf1[bufsize]; std::memset(buf1, 0, sizeof(char) * bufsize);

  error::auto_print(false);
  error::clear_stack();
  setbuf(stderr, buf1);
  EXPECT_THROW(handle.get_reference_count(),std::runtime_error);

  ss.str(std::string());
  ss << buf1;
    EXPECT_TRUE(ss.str().empty()) << "post buffer contents:\n" << ss.str();

  setbuf(stderr, NULL);
}
