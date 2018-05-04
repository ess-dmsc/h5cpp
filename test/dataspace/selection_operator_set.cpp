//
// (c) Copyright 2017 DESY,ESS
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
// Authors:
//   Eugen Wintersberger <eugen.wintersberger@desy.de>
//   Martin Shetty <martin.shetty@esss.se>
// Created on: Nov 13, 2017
//
#include <gtest/gtest.h>

#include <h5cpp/hdf5.hpp>

using namespace hdf5::dataspace;

class SelectionOpsSetTest : public testing::Test {
 public:
  Simple space;

  SelectionOpsSetTest() {
    space = Simple{{1024, 512}};
  }

};

TEST_F(SelectionOpsSetTest, simple_set) {
  Simple new_space = space || Hyperslab{{0, 0}, {100, 200}};
  EXPECT_EQ(new_space.size(), space.size());
  EXPECT_EQ(new_space.selection.size(), 100ul * 200ul);
}

TEST_F(SelectionOpsSetTest, set_from_list) {
  SelectionList selections{
      {SelectionOperation::SET, Selection::SharedPointer(new Hyperslab{{0, 0}, {100, 200}})},
      {SelectionOperation::OR, Selection::SharedPointer(new Hyperslab{{101, 201}, {100, 200}})}
  };

  Simple new_space = space || selections;
  EXPECT_EQ(new_space.size(), space.size());
  EXPECT_EQ(new_space.selection.size(), 2ul * 100ul * 200ul);
}
