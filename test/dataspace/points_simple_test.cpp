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
#include <h5cpp/dataspace/points.hpp>

using namespace hdf5;

TEST(PointsSimple, DefaultConsructor) {
  dataspace::Points h;
  EXPECT_EQ(h.rank(), 0ul);

  dataspace::Points h1(1);
  EXPECT_EQ(h1.rank(), 1ul);

  dataspace::Points h2(2);
  EXPECT_EQ(h2.rank(), 2ul);
}

TEST(PointsSimple, Add) {
  dataspace::Points h(1);
  EXPECT_EQ(h.points(), 0);
  h.add({2});
  EXPECT_EQ(h.points(), 1);
  h.add({7});
  EXPECT_EQ(h.points(), 2);
}

TEST(PointsSimple, FailAdd) {
  dataspace::Points h(1);
  EXPECT_THROW(h.add({2,3}), std::runtime_error);
}

TEST(PointsSimple, test_case_1) {
  dataspace::Simple space({10, 20});
  EXPECT_EQ(space.rank(), 2);
  EXPECT_EQ(space.size(), 200);
  dataspace::Points points(2);
  points.add({1, 1});
  points.add({5, 5});
  space.selection(dataspace::SelectionOperation::SET, points);
  EXPECT_EQ(space.selection.size(), 2ul);
  EXPECT_EQ(space.selection.type(), dataspace::SelectionType::POINTS);

  EXPECT_NO_THROW(space.selection.all());
  EXPECT_EQ(space.selection.type(), dataspace::SelectionType::ALL);
}

TEST(PointsSimple, test_case_2) {
  dataspace::Simple space({10, 1024, 1024});
  EXPECT_EQ(space.selection.type(), dataspace::SelectionType::ALL);

  dataspace::Points points(2);
  points.add({1, 1});
  points.add({2, 2});
  points.add({3, 3});
  points.add({4, 4});

  // TODO: why does this not throw when rank is not matching?
  EXPECT_NO_THROW(space.selection(dataspace::SelectionOperation::SET, points));
  EXPECT_EQ(space.selection.size(), 4ul);
  EXPECT_EQ(space.selection.type(), dataspace::SelectionType::POINTS);

  dataspace::Points points2(2);
  points2.add({5, 5});
  points2.add({6, 6});

  EXPECT_NO_THROW(space.selection(dataspace::SelectionOperation::APPEND, points2));
  EXPECT_EQ(space.selection.size(), 6ul);
  EXPECT_EQ(space.selection.type(), dataspace::SelectionType::POINTS);
}

TEST(PointsSimple, BadSelection) {
  dataspace::Simple space({10, 1024});
  EXPECT_EQ(space.selection.type(), dataspace::SelectionType::ALL);

  dataspace::Points points(2);
  points.add({1, 1});
  points.add({2, 2});

  EXPECT_THROW(space.selection(dataspace::SelectionOperation::OR, points), std::runtime_error);
}

TEST(PointsSimple, AddSet) {
  dataspace::Simple space({10, 1024});
  EXPECT_EQ(space.selection.type(), dataspace::SelectionType::ALL);

  dataspace::Points points(2);
  points.add_set({{1, 1}, {2, 2}});

  EXPECT_THROW(space.selection(dataspace::SelectionOperation::OR, points), std::runtime_error);
}

TEST(PointsSimple, AddSetError) {
  dataspace::Simple space({10, 1024});
  EXPECT_EQ(space.selection.type(), dataspace::SelectionType::ALL);

  dataspace::Points points(2);
  EXPECT_THROW(points.add_set({{1, 1}, {2, 2, 3}}), std::runtime_error);
}

TEST(PointsSimple, ConvenienceConstructor) {
  dataspace::Simple space({10, 1024});
  EXPECT_EQ(space.selection.type(), dataspace::SelectionType::ALL);

  dataspace::Points points({{1, 1}, {2, 2}});

  EXPECT_EQ(points.rank(), 2);
  EXPECT_EQ(points.points(), 2);
}

TEST(PointsSimple, ConvenienceConstructorError) {
  dataspace::Simple space({10, 1024});
  EXPECT_EQ(space.selection.type(), dataspace::SelectionType::ALL);

  EXPECT_THROW(dataspace::Points({{1, 1}, {2, 2, 3}}), std::runtime_error);
}
