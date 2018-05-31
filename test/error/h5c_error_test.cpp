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

TEST(H5CError, empty)
{
  auto stack = error::Singleton::instance().extract_stack();
  EXPECT_TRUE(stack.empty());
}

TEST(H5CError, extract_stack)
{
  provoke_h5_error();
  auto stack = error::Singleton::instance().extract_stack();
  EXPECT_EQ(stack.contents().size(), 2);
  for (auto d : stack.contents())
  {
    EXPECT_GT(d.description.size(), 2);
    EXPECT_NE(d.function.find("H5"), std::string::npos) << d;
  }
}

TEST(H5CError, what)
{
  provoke_h5_error();
  auto stack = error::Singleton::instance().extract_stack();
  std::stringstream ss;
  ss << stack.what();
  for (auto d : stack.contents())
  {
    std::stringstream ss2;
    ss2 << d;
    EXPECT_NE(ss.str().find(ss2.str()), std::string::npos);
  }
}
