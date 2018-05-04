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
// Created on: Aug 25, 2017
//

#include <gtest/gtest.h>
#include <h5cpp/dataspace/simple.hpp>
#include <h5cpp/dataspace/hyperslab.hpp>

using namespace hdf5;

TEST(HyperslabSimple, DefaultConsructor) {
  dataspace::Hyperslab h;
  EXPECT_EQ(h.rank(), 0ul);
  EXPECT_THROW(h.offset(), std::runtime_error);
  EXPECT_THROW(h.block(), std::runtime_error);
  EXPECT_THROW(h.count(), std::runtime_error);
  EXPECT_THROW(h.stride(), std::runtime_error);

  dataspace::Hyperslab h1(1);
  EXPECT_EQ(h1.rank(), 1ul);

  dataspace::Hyperslab h2(2);
  EXPECT_EQ(h2.rank(), 2ul);
}

TEST(HyperslabSimple, Offset) {
  dataspace::Hyperslab h(2);
  EXPECT_EQ(h.rank(), 2ul);
  EXPECT_EQ(h.offset()[0], 0ul);
  h.offset(0, 3);
  EXPECT_EQ(h.offset()[0], 3ul);
  h.offset({3, 4});
  EXPECT_EQ(h.offset()[1], 4ul);
  EXPECT_THROW(h.offset(2, 0), std::runtime_error);
  EXPECT_THROW(h.offset({1}), std::runtime_error);
}

TEST(HyperslabSimple, Block) {
  dataspace::Hyperslab h(2);
  EXPECT_EQ(h.rank(), 2ul);
  EXPECT_EQ(h.block()[0], 0ul);
  h.block(0, 3);
  EXPECT_EQ(h.block()[0], 3ul);
  h.block({3, 4});
  EXPECT_EQ(h.block()[1], 4ul);
  EXPECT_THROW(h.block(2, 0), std::runtime_error);
  EXPECT_THROW(h.block({1}), std::runtime_error);
}

TEST(HyperslabSimple, Count) {
  dataspace::Hyperslab h(2);
  EXPECT_EQ(h.rank(), 2ul);
  EXPECT_EQ(h.count()[0], 0ul);
  h.count(0, 3);
  EXPECT_EQ(h.count()[0], 3ul);
  h.count({3, 4});
  EXPECT_EQ(h.count()[1], 4ul);
  EXPECT_THROW(h.count(2, 0), std::runtime_error);
  EXPECT_THROW(h.count({1}), std::runtime_error);
}

TEST(HyperslabSimple, Stride) {
  dataspace::Hyperslab h(2);
  EXPECT_EQ(h.rank(), 2ul);
  EXPECT_EQ(h.stride()[0], 1ul);
  h.stride(0, 3);
  EXPECT_EQ(h.stride()[0], 3ul);
  h.stride({3, 4});
  EXPECT_EQ(h.stride()[1], 4ul);
  EXPECT_THROW(h.stride(2, 0), std::runtime_error);
  EXPECT_THROW(h.stride({1}), std::runtime_error);
}

TEST(HyperslabSimple, ConvenienceConsructors) {
  dataspace::Hyperslab h1({1, 2}, {3, 4}, {5, 6}, {7, 8});
  EXPECT_EQ(h1.rank(), 2ul);
  EXPECT_EQ(h1.offset()[0], 1ul);
  EXPECT_EQ(h1.offset()[1], 2ul);
  EXPECT_EQ(h1.block()[0], 3ul);
  EXPECT_EQ(h1.block()[1], 4ul);
  EXPECT_EQ(h1.count()[0], 5ul);
  EXPECT_EQ(h1.count()[1], 6ul);
  EXPECT_EQ(h1.stride()[0], 7ul);
  EXPECT_EQ(h1.stride()[1], 8ul);

  dataspace::Hyperslab h2({1, 2}, {3, 4}, {5, 6});
  EXPECT_EQ(h2.rank(), 2ul);
  EXPECT_EQ(h2.offset()[0], 1ul);
  EXPECT_EQ(h2.offset()[1], 2ul);
  EXPECT_EQ(h2.block()[0], 1ul); //default
  EXPECT_EQ(h2.block()[1], 1ul); //default
  EXPECT_EQ(h2.count()[0], 3ul);
  EXPECT_EQ(h2.count()[1], 4ul);
  EXPECT_EQ(h2.stride()[0], 5ul);
  EXPECT_EQ(h2.stride()[1], 6ul);

  dataspace::Hyperslab h3({1, 2}, {3, 4});
  EXPECT_EQ(h3.rank(), 2ul);
  EXPECT_EQ(h3.offset()[0], 1ul);
  EXPECT_EQ(h3.offset()[1], 2ul);
  EXPECT_EQ(h3.block()[0], 3ul);
  EXPECT_EQ(h3.block()[1], 4ul);
  EXPECT_EQ(h3.count()[0], 1ul); //default
  EXPECT_EQ(h3.count()[1], 1ul); //default
  EXPECT_EQ(h3.stride()[0], 1ul); //default
  EXPECT_EQ(h3.stride()[1], 1ul); //default
}

TEST(HyperslabSimple, test_case_1) {
  dataspace::Simple space({10, 20});
  EXPECT_EQ(space.rank(), 2);
  EXPECT_EQ(space.size(), 200);
  dataspace::Hyperslab slab({1, 1}, {5, 5}, {1, 1}, {1, 1});
  space.selection(dataspace::SelectionOperation::SET, slab);
  EXPECT_EQ(space.selection.size(), 25ul);
  EXPECT_EQ(space.selection.type(), dataspace::SelectionType::HYPERSLAB);

  EXPECT_NO_THROW(space.selection.all());
  EXPECT_EQ(space.selection.type(), dataspace::SelectionType::ALL);
}

TEST(HyperslabSimple, test_case_2) {
  dataspace::Simple space({10, 1024, 1024});
  EXPECT_EQ(space.selection.type(), dataspace::SelectionType::ALL);

  dataspace::Hyperslab frame({0, 0, 0}, {1, 1024, 1024}, {1, 1, 1}, {1, 1, 1});
  EXPECT_NO_THROW(space.selection(dataspace::SelectionOperation::SET, frame));
  frame.offset(0, 9);
  EXPECT_NO_THROW(space.selection(dataspace::SelectionOperation::OR, frame));
  EXPECT_EQ(space.selection.size(), 2ul * 1024ul * 1024ul);

}

TEST(HyperslabSimple, test_roi_construction) {
  dataspace::Simple space({10, 1024});
  dataspace::Hyperslab slice{{0, 0}, {1, 1024}};
  space.selection(dataspace::SelectionOperation::SET, slice);
  EXPECT_EQ(space.selection.size(), 1024ul);
}

TEST(HyperslabSimple, test_scatter_construction) {
  dataspace::Simple space{{20, 1024}};
  dataspace::Hyperslab selection{{1, 1}, {3, 10}, {2, 4}};
  space.selection(dataspace::SelectionOperation::SET, selection);
  EXPECT_EQ(space.selection.size(), 30ul);
}

TEST(HyperslabSimple, test_dataspace_copy_with_selection) {
  dataspace::Simple space{{20, 1024}};
  dataspace::Hyperslab selection{{1, 1}, {3, 10}, {2, 4}};
  space.selection(dataspace::SelectionOperation::SET, selection);
  EXPECT_EQ(space.selection.size(), 30ul);

  dataspace::Simple new_space(space);
  EXPECT_EQ(new_space.selection.size(), 30ul);
}

TEST(HyperslabSimple, BadSelection) {
  dataspace::Simple space{{20, 1024}};
  dataspace::Hyperslab selection{{1, 1}, {3, 10}, {2, 4}};
  ObjectHandle(static_cast<hid_t>(space)).close();
  EXPECT_THROW(selection.apply(space, dataspace::SelectionOperation::SET), std::runtime_error);
}
