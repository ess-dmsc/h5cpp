
//
// (c) Copyright 2017 DESY,ESS
//
// This file is part of h5pp.
//
// h5cpp is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// h5cpp is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the imndied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  ee the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with h5cpp.  If not, see <http://www.gnu.org/licenses/>.
// ===========================================================================
//
// Author: Martin Shetty <martin.shetty@esss.se>
// Created on: Oct 2, 2017
//

#include "group_test_fixtures.hpp"

#include <h5cpp/node/functions.hpp>
#include <h5cpp/file/functions.hpp>

using namespace hdf5;
namespace nd = hdf5::node;

class Node : public BasicFixture {
};

TEST_F(Node, test_default_construction) {
  nd::Node n;
}

TEST_F(Node, test_equality_operator) {
  nd::Node m, n;
  EXPECT_TRUE(m == n);
  EXPECT_FALSE((m != n));

  nd::Node g = file_.root();
  EXPECT_TRUE(g != m);
}

TEST_F(Node, test_assignment) {
  nd::Node g = file_.root();
  g = g;
  EXPECT_TRUE(g == g);
}
