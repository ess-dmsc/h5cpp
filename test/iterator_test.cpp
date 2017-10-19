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
#include <h5cpp/iterator.hpp>

using namespace hdf5;

TEST(Iterator, constructors)
{
  Iterator a;
  EXPECT_EQ(a.index(), 0);

  Iterator b(3);
  EXPECT_EQ(b.index(), 3);

  Iterator c = b;
  EXPECT_EQ(c.index(), 3);

  Iterator d(b);
  EXPECT_EQ(d.index(), 3);
}

TEST(Iterator, comparators)
{
  EXPECT_EQ(Iterator(2), Iterator(2));

  EXPECT_LT(Iterator(2), Iterator(3));
  EXPECT_LE(Iterator(2), Iterator(3));
  EXPECT_LE(Iterator(2), Iterator(2));

  EXPECT_GT(Iterator(4), Iterator(3));
  EXPECT_GE(Iterator(4), Iterator(3));
  EXPECT_GE(Iterator(2), Iterator(2));
}

TEST(Iterator, increment)
{
  Iterator i(1);

  i += 2;
  ASSERT_EQ(3, i.index());

  ASSERT_EQ(3, (i++).index());
  ASSERT_EQ(4, i.index());

  ASSERT_EQ(5, (++i).index());

  ASSERT_EQ(6, (i + ssize_t(1)).index());
  ASSERT_EQ(6, (ssize_t(1) + i).index());
}

TEST(Iterator, decrement)
{
  Iterator i(7);

  i -= 2;
  ASSERT_EQ(5, i.index());

  ASSERT_EQ(5, (i--).index());
  ASSERT_EQ(4, i.index());

  ASSERT_EQ(3, (--i).index());

  ASSERT_EQ(2, i - Iterator(1));
  ASSERT_EQ(2, (i - ssize_t(1)).index());
}
