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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Aug 25, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/dataspace/simple.hpp>

using namespace hdf5;

TEST(SelectionManager, test_nothing_and_all_selected) {
  dataspace::Simple space({10, 1024});
  EXPECT_EQ(space.size(), 10l * 1024l);
  EXPECT_EQ(space.selection.size(), 10ul * 1024ul);

  space.selection.none();
  EXPECT_EQ(space.size(), 10l * 1024l);
  EXPECT_EQ(space.selection.size(), 0ul);

  space.selection.all();
  EXPECT_EQ(space.size(), 10l * 1024l);
  EXPECT_EQ(space.selection.size(), 10ul * 1024ul);

  ObjectHandle(static_cast<hid_t>(space)).close();
  EXPECT_THROW(space.selection.size(), std::runtime_error);
  EXPECT_THROW(space.selection.none(), std::runtime_error);
  EXPECT_THROW(space.selection.all(), std::runtime_error);
}
