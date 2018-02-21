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
// Created on: Nov 13, 2017
//

#include <gtest/gtest.h>

#include <h5cpp/hdf5.hpp>

using namespace hdf5;

class DataspaceViewTest : public testing::Test {
 public:
  dataspace::Simple space;
  dataspace::SelectionList selections;
  dataspace::Hyperslab slab;

  DataspaceViewTest() :
      space(),
      selections(),
      slab() {

    using dataspace::Selection;
    using dataspace::SelectionOperation;
    using dataspace::SelectionList;
    using dataspace::Hyperslab;

    space = dataspace::Simple({1024, 512});
    slab = Hyperslab{{300, 300}, {100, 100}};

    selections = SelectionList{
        {SelectionOperation::SET, Selection::SharedPointer(new Hyperslab({0, 0}, {100, 100}))},
        {SelectionOperation::OR, Selection::SharedPointer(new Hyperslab({200, 200}, {100, 100}))}
    };
  }
};

TEST_F(DataspaceViewTest, test_default_construction) {
  dataspace::View view;
  EXPECT_THROW(view.size(), std::runtime_error);
  EXPECT_THROW(view(dataspace::Hyperslab{{0, 0}, {10, 10}}), std::runtime_error);
  EXPECT_THROW(view(selections), std::runtime_error);
}

TEST_F(DataspaceViewTest, test_list_construction) {
  dataspace::View view{space, selections};
  EXPECT_EQ(view.size(), 2ul * 100ul * 100ul);
  EXPECT_EQ(space.size(), 1024l * 512l);
}

TEST_F(DataspaceViewTest, test_reseting_selections) {
  dataspace::View view(space);
  EXPECT_EQ(view.size(), space.size());

  EXPECT_NO_THROW(view(slab));
  EXPECT_EQ(view.size(), 100ul * 100ul);

  EXPECT_NO_THROW(view(selections));
  EXPECT_EQ(view.size(), 2ul * 100ul * 100ul);
}
