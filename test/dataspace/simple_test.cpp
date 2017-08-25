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
#define BOOST_TEST_MODULE testing simple dataspace implementation
#include <boost/test/unit_test.hpp>
#include <h5cpp/dataspace/simple.hpp>

using namespace hdf5;

BOOST_AUTO_TEST_SUITE(Simple_test)

BOOST_AUTO_TEST_CASE(test_default_construction)
{
  dataspace::Simple space;
  BOOST_CHECK_EQUAL(space.size(),0);
  BOOST_CHECK_EQUAL(space.rank(),0);
  BOOST_CHECK(space.type()==dataspace::Type::SIMPLE);
  BOOST_CHECK(space.current_dimensions().empty());
  BOOST_CHECK(space.maximum_dimensions().empty());
}

BOOST_AUTO_TEST_CASE(test_construction_only_current)
{
  Dimensions s = {10,20,30};
  dataspace::Simple space(s);
  BOOST_CHECK_EQUAL(space.size(),10*20*30);
  BOOST_CHECK_EQUAL(space.rank(),3);

  Dimensions c = space.current_dimensions();
  Dimensions m = space.maximum_dimensions();
  BOOST_CHECK_EQUAL_COLLECTIONS(c.begin(),c.end(),s.begin(),s.end());
  BOOST_CHECK_EQUAL_COLLECTIONS(c.begin(),c.end(),m.begin(),m.end());
}

BOOST_AUTO_TEST_SUITE_END()
