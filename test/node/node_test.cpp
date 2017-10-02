
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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Testing node:Node creation
#include <boost/test/unit_test.hpp>
#include <h5cpp/node/node.hpp>

namespace nd = hdf5::node;

BOOST_AUTO_TEST_SUITE(NodeTest)

  BOOST_AUTO_TEST_CASE(test_default_construction)
  {
    nd::Node n;
  }

  BOOST_AUTO_TEST_CASE(test_equality_operator)
  {
    nd::Node m, n;
    BOOST_CHECK(m == n);
    BOOST_CHECK(!(m != n));
  }
BOOST_AUTO_TEST_SUITE_END()




