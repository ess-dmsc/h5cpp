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
// Created on: Sep 11, 2017
//
#include <gtest/gtest.h>
#include <h5cpp/iterator_config.hpp>

using namespace hdf5;

TEST(IterationOrderTest, test_string_representation)
{
  std::stringstream stream;

  stream = std::stringstream();
  stream<<IterationOrder::DECREASING;
  EXPECT_EQ(stream.str(), "DECREASING");

  stream = std::stringstream();
  stream<<IterationOrder::INCREASING;
  EXPECT_EQ(stream.str(), "INCREASING");

  stream = std::stringstream();
  stream<<IterationOrder::NATIVE;
  EXPECT_EQ(stream.str(), "NATIVE");
}

TEST(IterationOrderTest, test_value)
{
  EXPECT_EQ(static_cast<H5_iter_order_t>(IterationOrder::DECREASING),
                    H5_ITER_DEC);
  EXPECT_EQ(static_cast<H5_iter_order_t>(IterationOrder::INCREASING),
                    H5_ITER_INC);
  EXPECT_EQ(static_cast<H5_iter_order_t>(IterationOrder::NATIVE),
                    H5_ITER_NATIVE);
}
