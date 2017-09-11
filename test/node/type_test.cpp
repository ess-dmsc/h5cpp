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
// Created on: Sep 11, 2017
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE testing node::Type enumeration
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include <h5cpp/node/types.hpp>

using boost::test_tools::output_test_stream;
using namespace hdf5;

BOOST_AUTO_TEST_SUITE(Type_test)

BOOST_AUTO_TEST_CASE(test_string_representation)
{
  output_test_stream stream;
  stream<<node::Type::DATASET;
  BOOST_CHECK(stream.is_equal("DATASET"));
  stream<<node::Type::DATATYPE;
  BOOST_CHECK(stream.is_equal("DATATYPE"));
  stream<<node::Type::GROUP;
  BOOST_CHECK(stream.is_equal("GROUP"));
  stream<<node::Type::UNKNOWN;
  BOOST_CHECK(stream.is_equal("UNKNOWN"));
}

BOOST_AUTO_TEST_CASE(test_values)
{
  BOOST_CHECK_EQUAL(static_cast<H5O_type_t>(node::Type::DATASET),
                    H5O_TYPE_DATASET);
  BOOST_CHECK_EQUAL(static_cast<H5O_type_t>(node::Type::UNKNOWN),
                    H5O_TYPE_UNKNOWN);
  BOOST_CHECK_EQUAL(static_cast<H5O_type_t>(node::Type::DATATYPE),
                    H5O_TYPE_NAMED_DATATYPE);
  BOOST_CHECK_EQUAL(static_cast<H5O_type_t>(node::Type::GROUP),
                    H5O_TYPE_GROUP);
}

BOOST_AUTO_TEST_SUITE_END()
