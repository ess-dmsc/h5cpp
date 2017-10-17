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
// Created on: Aug 25, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing simple hyperslab operations
#include <boost/test/unit_test.hpp>
#include <h5cpp/dataspace/simple.hpp>
#include <h5cpp/dataspace/selection.hpp>

using namespace hdf5;

BOOST_AUTO_TEST_SUITE(HyperslabSimple_test)

BOOST_AUTO_TEST_CASE(test_case_1)
{
  dataspace::Simple space({10,20});
  BOOST_CHECK_EQUAL(space.rank(),2);
  BOOST_CHECK_EQUAL(space.size(),200);
  dataspace::Hyperslab slab({1,1},{1,1},{1,1},{5,5});
  space.selection(dataspace::SelectionOperation::SET,slab);
  BOOST_CHECK_EQUAL(space.selection.size(),25);
  BOOST_CHECK_EQUAL(space.selection.type(),dataspace::SelectionType::HYPERSLAB);

  BOOST_CHECK_NO_THROW(space.selection.all());
  BOOST_CHECK_EQUAL(space.selection.type(),dataspace::SelectionType::ALL);
}

BOOST_AUTO_TEST_CASE(test_case_2)
{
  dataspace::Simple space({10,1024,1024});
  BOOST_CHECK_EQUAL(space.selection.type(),dataspace::SelectionType::ALL);

  dataspace::Hyperslab frame({0,0,0},{1,1,1},{1,1,1},{1,1024,1024});
  BOOST_CHECK_NO_THROW(space.selection(dataspace::SelectionOperation::SET,frame));
  frame.start(0,9);
  BOOST_CHECK_NO_THROW(space.selection(dataspace::SelectionOperation::OR,frame));
  BOOST_CHECK_EQUAL(space.selection.size(),2*1024*1024);

}

BOOST_AUTO_TEST_SUITE_END()
