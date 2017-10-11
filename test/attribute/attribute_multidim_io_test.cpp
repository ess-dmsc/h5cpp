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
// Created on: Oct 5, 2017
//
#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>
#include <cstdint>
#include <vector>
#include <array>

#include "attribute_test_fixtures.hpp"

using namespace hdf5;

BOOST_AUTO_TEST_SUITE(AttributeTest)

BOOST_FIXTURE_TEST_SUITE(MultidimIOTest,AttributeFixture)

BOOST_AUTO_TEST_CASE(test_uint8_vector)
{
  std::vector<std::uint8_t> write_data{1,2,3};
  std::vector<std::uint8_t> read_data(write_data.size());

  attribute::Attribute a = root_group.attributes.create<std::uint8_t>("data",{3});
  a.write(write_data);
  a.read(read_data);
  BOOST_CHECK_EQUAL_COLLECTIONS(write_data.begin(),write_data.end(),
                                read_data.begin(),read_data.end());
}

BOOST_AUTO_TEST_CASE(test_uint8_array)
{
  std::array<std::uint8_t,3> write_data{1,2,3};
  std::array<std::uint8_t,3> read_data;

  attribute::Attribute a = root_group.attributes.create<std::uint8_t>("data",{3});
  a.write(write_data);
  a.read(read_data);
  BOOST_CHECK_EQUAL_COLLECTIONS(write_data.begin(),write_data.end(),
                                read_data.begin(),read_data.end());
}

BOOST_AUTO_TEST_SUITE_END()


BOOST_AUTO_TEST_SUITE_END()
