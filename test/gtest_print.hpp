//
// (c) Copyright 2017 DESY, ESS
//
// This file is part of h5cpp.
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
// Created on: Nov 22, 2017
//

#pragma  once

#include <gtest/gtest.h>

namespace testing
{
namespace internal
{
enum LocalGTestColor {
  kDefault,
  kRed,
  kGreen,
  kYellow
};
extern void ColoredPrintf(LocalGTestColor color, const char* fmt, ...);
}
}
#define PRINTF(...)  do { testing::internal::ColoredPrintf(testing::internal::LocalGTestColor::kGreen, "[          ] "); testing::internal::ColoredPrintf(testing::internal::LocalGTestColor::kYellow, __VA_ARGS__); } while(0)

// C++ stream interface
class TestCout : public std::stringstream
{
 public:
  ~TestCout()
  {
    PRINTF("%s\n",str().c_str());
  }
};

#define TEST_COUT  TestCout()
